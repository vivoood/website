#ifndef __EGT_NETWORK_IMPL_H
#define __EGT_NETWORK_IMPL_H
//
#include "NetworkBase/IConnector.h"
#include "NetworkBase/IConnection.h"
#include "Messengers/Messenger.h"
//
#include <lib_utils/Platform/Platform.h>

namespace egt
{
namespace NetFactory
{
    egt::IConnector::Ptr TcpIpV6Server(int serverPort);
    egt::IConnector::Ptr TcpIpV6Client(const std::string& serverName, int serverPort);
    //
    egt::IConnector::Ptr UnixDomainSocketServer(const std::string& socketName);
    egt::IConnector::Ptr UnixDomainSocketClient(const std::string& socketName);
    //
    egt::IConnector::Ptr UdpV6Server(const std::string& serverName, int serverPort);
    egt::IConnector::Ptr UdpV6Client(const std::string& serverName, int serverPort);
    //
    egt::IConnector::Ptr LocalProcessServer();
    egt::IConnector::Ptr LocalProcessClient(egt::IConnector::Ptr localProcessServer);
    //
    egt::IConnector::Ptr ExecProcessConnector(const std::string& procName);
}
}


#endif // __EGT_NETWORK_IMPL_H
