/*
Copyright (c) 2012 EGT Ltd.
All rights reserved

More information at: http://www.egt-bg.com
*/

#ifndef NETWORKTOOLS_H
#define NETWORKTOOLS_H

#include <string>
#include <vector>
#include <stdlib.h>

#include "Singleton.h"
#include "SimpleThread.h"


using namespace std;

class NetworkTools : public egt::default_thread, public Singleton<NetworkTools>
{

private:

    /** Virtual network adaptor name */
    static const char * VIRT_INTERFACE;
    
    /** Count of ping packets */
    int m_nPingPackets;
    
    /** Pinged ip */
    string m_strPingIp;
    
    /** Ping result */
    string m_strResult;
    
    /** Ping succses */
    bool m_bPingSucces;
    
    /** CheckPing - Check if there is ping to the IP
     * @param nPackets - packets count
     * @param strIP - pinged IP
     * @param strResult - save the result of ping
     * @return success
     */
    bool CheckPing( int nPackets, string strIP, string & strResult );
    
    /** Erase end line simbol from settings in eth */
    void EraseEndlineSymbol( string & strIp );
    
    vector<string> &SplitIp(const string &strIp, char delim, vector<string> &strDigits);
    
    vector<string> SplitIp(const string &strIp, char delim);
    
public:

    /** Constructor */
    NetworkTools();

    /** Destructor */
    virtual ~ NetworkTools() {}

    /** SetIpAddres - Set ip from string ip
    @return succses
    */
    bool SetIpAddres(string strIp);

    /** SetGwAddres - Set gateway address
    @return succses
    */
    bool SetGwAddres(string gateWay);

    /** GetInfo - return network information: ip , mask  .......
    @param strIp
    @param strNetMask
    @param strGateway
    @param strBroadcast
    */
    void GetInfo(string & strIp,string & strNetMask,string & strGateway,string & strBroadcast);

    /** GetPingSuccses - get ping succses 
    * @return ping succses
    */
    bool GetPingSuccses() { return m_bPingSucces; }
    
    /** GetPingResult - get ping result 
    * @return ping result
    */
    string GetPingResult() { return m_strResult; }
    
    /** CheckPingDiffThread - Check if there is ping to the server in different thread
     * @param nPackets - packets count
     * @param strIP - pinged IP
     */
    void CheckPingDiffThread( int nPackets, string strIP );

    /** CheckPingCurrThread - Check if there is ping to the server in current thread
     * @param nPackets - packets count
     * @param strIP - pinged IP
     */
    bool CheckPingCurrThread( int nPackets, string strIP, string & strResult );
    
    /** CheckRuningProcess -
    * @param strExeName - name of process
    * @return succses
    */
    bool CheckRuningProcess(string strExeName, string & strPid);

    /** Check valide IPv4 format
    @param strIP - current checked ip adress
    @return succses
    */
    bool CheckValideIPv4Format(string strIP);
    
    /** Check valide IP
    @param strIP - current checked ip adress
    @return succses
    */
    bool CheckValideIPv4(string strIP);
    
    /** Check valide IP
    @param strIP - current checked ip adress
    @return succses
    */
    bool CheckValideIPv6(string strIP);

    
    /** Get  IP v6
    @param interface - "eth0"
    @return ip as string
    */
    string GetIPv6(string interface);

    /** Get  MAC address
    @param interface - "eth0" or "eth1"
    @return mac as string
    */
    string GetMacAddr(const string& interface);
    
    /** Convert normal ipv6 to specific multicast adres  
    @param strIp - ip address
    @param strPrefix - prefix "ff05"
    @return success
    */
    bool SpecificMulticastConvert(string& strIp, string strPrefix);
    
    /** SendComandLine -
     * @param result - save the result
     * @return success
     */
    bool SendComandLine(std::string comandLine,std::string& result);

    /** Check cable connection status
    * @param strInterface - current name and number of network card
    * @return success
    */
    bool CableConnectionState( std::string strInterface = "eth0");

    /** Thread function */
    virtual void run();

    static std::string GetEnv( const std::string & var ) {
        const char * val = ::getenv( var.c_str() );
        if ( val == 0 ) {
            return "";
        }
        else {
            return val;
        }
    }

};

#endif // NETWORKADDRES_H
