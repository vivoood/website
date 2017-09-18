/*

More information at: http://www.egt-bg.com
*/

#include "NetworkTools.h"

#include <sstream>
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>             /* offsetof */
#include <net/if.h>
#include <net/if.h>
#include <linux/sockios.h>
#include <netinet/in.h>
#if __GLIBC__ >=2 && __GLIBC_MINOR >= 1
#include <netpacket/packet.h>
#include <net/ethernet.h>
#else
#include <asm/types.h>
#include <linux/if_ether.h>
#endif

#include <sys/ioctl.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <net/if.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <resolv.h>
#include <net/route.h>
#include <ifaddrs.h>

#include <ctime>
#include <iostream>

#define ifreq_offsetof(x)  offsetof(struct ifreq, x)
#define IFF_LOWER_UP	0x10000

#ifdef EGT_DEVELOP
const char * NetworkTools::VIRT_INTERFACE = "eth0:1";
#else
const char * NetworkTools::VIRT_INTERFACE = "eth0:1";
#endif

NetworkTools::NetworkTools()
    : egt::default_thread("NetworkTools" )
{

    m_bPingSucces = false;
    m_strPingIp.assign("n/a");
    m_strResult.assign("n/a");
    m_nPingPackets = 0;
}


bool NetworkTools::SetIpAddres(string strIp)
{
    if ( strIp.empty() )
    {
        /// PDEBUG
        return false;
    }

    ///example
    //ifconfig eth0 1.2.3.4 up

    string result("");
    string commandIp("/sbin/ifconfig ");
    commandIp.append(VIRT_INTERFACE).append(" ").append(strIp).append(" netmask 255.255.255.0").append(" up");

    SendComandLine(commandIp,result);

    return true;
}


bool NetworkTools::SetGwAddres(string gateWay) {


    if ( gateWay.empty() )
    {
        /// PDEBUG
        return false;
    }

    string result("");
    SendComandLine("/sbin/ifconfig -a ",result);

    ///example
    //route add default gw 192.168.1.254 eth0


    string commandGw("/sbin/route add default gw ");
    commandGw.append(gateWay).append(" ").append(VIRT_INTERFACE);

    SendComandLine(commandGw,result);
    return true;

}

void NetworkTools::GetInfo(string & strIP,string & strNetMask,string & strGateway,string & strBroadcast)
{

    strIP.clear();
    strNetMask.clear();
    strGateway.clear();
    strBroadcast.clear();

    string commandIp("/sbin/ifconfig ");
    commandIp.append(VIRT_INTERFACE).append("| grep inet | awk -F: '{print $2}' | awk '{print $1}'");
    SendComandLine(commandIp,strIP);
    EraseEndlineSymbol(strIP);

    string commandMask("/sbin/ifconfig ");
    commandMask.append(VIRT_INTERFACE).append("| grep inet | awk -F: '{print $4}' | awk '{print $1}'");
    SendComandLine(commandMask,strNetMask);
    EraseEndlineSymbol(strNetMask);

    string commandBcast("/sbin/ifconfig ");
    commandBcast.append(VIRT_INTERFACE).append("| grep inet | awk -F: '{print $4}' | awk '{print $1}'");
    SendComandLine(commandBcast,strBroadcast);
    EraseEndlineSymbol(strBroadcast);

    string commandGateway("/sbin/ip route show default | grep default | awk {'print $3'}");
    SendComandLine(commandGateway,strGateway);
    EraseEndlineSymbol(strGateway);


    //return true;
}


bool NetworkTools::CheckRuningProcess(string strExeName, string& strPid)
{
    strPid.clear();
    string strComandLine("pidof ");
    strComandLine.append( strExeName );

    if ( SendComandLine( strComandLine, strPid ) )
    {
        return ( ! strPid.empty() );
    }

    return false;
}


vector<string> &NetworkTools::SplitIp(const string &strIp, char delim, vector<string> &strDigits) {
    stringstream ss(strIp);
    string item;
    while(getline(ss, item, delim)) {
       strDigits.push_back(item);
    }
    return strDigits;
}

vector<string> NetworkTools::SplitIp(const string &strIp, char delim) {
   vector<string> vDigits;
   return SplitIp(strIp, delim, vDigits);
}

bool NetworkTools::CheckValideIPv4Format(string strIP)
{
    struct sockaddr_in sa;
    return inet_pton(AF_INET, strIP.c_str(), &(sa.sin_addr)) != 0;
}

bool NetworkTools::CheckValideIPv4(string strIP)
{
    if ( ! CheckValideIPv4Format(strIP) )
    {
        return false;
    }

    const unsigned int cuiMaxDigits = 4;
    int uiLenght = strIP.size();
    if (uiLenght < 7 || uiLenght > 15)
    {
        return false;
    }

    char tail[16];
    tail[0] = 0;

    unsigned int arr[cuiMaxDigits];
    int c = sscanf(strIP.c_str(), "%3u.%3u.%3u.%3u%15s", &arr[0], &arr[1], &arr[2], &arr[3], tail);

    if ( c != cuiMaxDigits || tail[0] )
    {
        return false;
    }

    for (unsigned i = 0; i < cuiMaxDigits - 1; i++)
    {
        if (arr[i] > 255)
        {
            return false;
        }
    }

    if ( ( arr[cuiMaxDigits - 1] == 0 ) || ( arr[cuiMaxDigits - 1] > 254 ) )
    {
        return false;
    }

    return true;
}

bool NetworkTools::CheckValideIPv6(string strIP)
{
    struct sockaddr_in6 sa;
    return inet_pton(AF_INET6, strIP.c_str(), &(sa.sin6_addr)) != 0;
}


string NetworkTools::GetIPv6(string interface )
{
    
    struct ifaddrs * ifAddrStruct=NULL;
    struct ifaddrs * ifa=NULL;
    void * tmpAddrPtr=NULL;      
    getifaddrs(&ifAddrStruct);
    string strIp("");
    
    
    for (ifa = ifAddrStruct; ifa != NULL; ifa = ifa->ifa_next) {

      if (ifa->ifa_addr->sa_family==AF_INET6 && ifa->ifa_name == interface ) { // check it is IP6
            // is a valid IP6 Address
            tmpAddrPtr=&((struct sockaddr_in6 *)ifa->ifa_addr)->sin6_addr;
            char addressBuffer[INET6_ADDRSTRLEN];
            inet_ntop(AF_INET6, tmpAddrPtr, addressBuffer, INET6_ADDRSTRLEN);
            strIp.assign(addressBuffer);
            break;
        } 
    }
    if (ifAddrStruct!=NULL) 
        freeifaddrs(ifAddrStruct);//remember to free ifAddrStruct
   
  
  
    
    return strIp;
}

string NetworkTools::GetMacAddr(const string& interface)
{
    std::string mac;
    struct ifreq buffer;

    int s_fd = socket(PF_INET, SOCK_DGRAM, 0);
    memset(&buffer, 0, sizeof(buffer));
    strcpy(buffer.ifr_name, interface.c_str());
    ioctl(s_fd, SIOCGIFHWADDR, &buffer);
    close(s_fd);

    for (int i = 0; i < 6; ++i)
    {
        char buf[4] = {0};
        sprintf(buf, "%.2X:", (unsigned char)buffer.ifr_hwaddr.sa_data[i]);
        mac += std::string(buf);
    }

    // remove last ":"
    if (!mac.empty())
    {
        mac.pop_back();
    }
    return mac;
}

bool NetworkTools::SpecificMulticastConvert(string& strIp, string strPrefix)
{
    /** Check valid IPv6 */
    if ( ! CheckValideIPv6(strIp) )
    {
	strIp.assign("Not valid IPv6");
        return false;
    }

    strIp.replace( 0, strIp.find_first_of(":"), strPrefix );
    return true;
}


bool NetworkTools::CheckPing(int nPackets, string strIP, string& strResult)
{
  
    
    if ( strIP.empty() )
    {
        strResult.assign(" Empty IP!");
        return false;
    }


    if (!CheckValideIPv4(strIP) && !CheckValideIPv6(strIP))
    {
      strResult.assign(" Not valid IP!");
      return false;
    }

    strResult.clear();

    stringstream ss;
    
    if (CheckValideIPv4(strIP))
    {
      ss << "ping -c " << nPackets << " -q -w 1 " << strIP;    
    }
    
    if(CheckValideIPv6(strIP))
    {
      ss << "ping6 -c " << nPackets << " -q -w 1 " << strIP;
    }
    
    string strCommandLine( ss.str() );

    if ( ! SendComandLine( strCommandLine, strResult ) )
    {
        strResult.assign(" No ping command!");
        return false;
    }


    string strCompare("% packet loss");
    int nFirstPos = strResult.find("% packet loss",0,strCompare.size());
    if (nFirstPos < 0)
    {
        strResult.assign("unrecognized ping result");
        return false;
    }
    
    int nLenght = strResult.find_last_of(",", nFirstPos);
    strResult.assign(strResult.substr(nLenght+2,(nFirstPos-nLenght-2)));
    strResult.append(strCompare);
    
    if ( strResult.compare( "0% packet loss" ) != 0 )
    {
	return false;
    }

    return true;
}

void NetworkTools::EraseEndlineSymbol(string& strIp)
{
    if ( strIp.empty() == true )
    {
        return;
    }

    strIp.erase(std::remove(strIp.begin(), strIp.end(), '\n'), strIp.end());
}

void NetworkTools::CheckPingDiffThread( int nPackets, string strIP )
{
    if (is_run())
    {
        return;
    }

    m_nPingPackets = nPackets;
    m_strPingIp.assign(strIP);
    m_strResult.assign("n/a");
    m_bPingSucces = false;

    request_to_run();
}

bool NetworkTools::CheckPingCurrThread(int nPackets, string strIP, string & strResult)
{
    m_nPingPackets = nPackets;
    m_strPingIp.assign(strIP);
    m_strResult.assign("n/a");
    m_bPingSucces = false;

    m_bPingSucces = CheckPing(m_nPingPackets, m_strPingIp, m_strResult);
    strResult.assign(m_strResult);
    return m_bPingSucces;
}

bool NetworkTools::SendComandLine(string comandLine, string& result)
{
    result.clear();
    FILE *p = popen(comandLine.c_str(), "r");
    if (!p)
    {
        perror("popen failed");
        return false;
    }

    char buffer[256] = { 0 };
    while ( fgets(buffer, sizeof(buffer), p) )
    {
        result.append( buffer );
    }

    pclose(p);

    return true;
}

bool NetworkTools::CableConnectionState(string strInterface)
{
    
    struct ifreq ifr;
    bool up_and_running = false ;

    memset( &ifr, 0, sizeof(ifr) );
    strcpy( ifr.ifr_name, strInterface.c_str() );


    int dummy_fd = socket( AF_INET, SOCK_DGRAM, 0 );

    if( ioctl( dummy_fd, SIOCGIFFLAGS, &ifr ) != -1 )
    {
	up_and_running = (ifr.ifr_flags & ( IFF_UP | IFF_RUNNING )) == ( IFF_UP | IFF_RUNNING );
    }
    else
    {
	// error
    }

    close(dummy_fd);
    return up_and_running;
  
}

void NetworkTools::run()
{
    m_bPingSucces = CheckPing(m_nPingPackets, m_strPingIp, m_strResult);
    request_to_run(false);
}
