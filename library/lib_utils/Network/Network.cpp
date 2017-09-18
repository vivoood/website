//
#include "Networks/LocalClient.h"
#include "Networks/LocalServer.h"
#include "Networks/LocalConnection.h"
//
#include <lib_utils/Platform/Platform.h>
#include "Networks/GenericClient.h"
#include "Networks/GenericServer.h"
#include "Networks/GenericConnection.h"
//
#include "Networks/GenericClient.hpp"
#include "Networks/GenericServer.hpp"
#include "Networks/GenericConnection.hpp"
//
#include "Networks/BashClient.h"


namespace egt
{
namespace NetFactory
{
    //
    egt::IConnector::Ptr TcpIpV6Server(int serverPort)
    {
        auto ptr = std::make_shared<GenericServer<Platform::Sockets::IpV6>>();
        ptr->SetServerInfo(serverPort);
        ptr->RunConnector();
        return ptr;
    }
    //
    egt::IConnector::Ptr TcpIpV6Client(const std::string& serverName, int serverPort)
    {
        auto ptr = std::make_shared<GenericClient<Platform::Sockets::IpV6>>();
        ptr->SetServerInfo({serverName, serverPort});
        ptr->RunConnector();
        return ptr;
    }
    //
    egt::IConnector::Ptr UnixDomainSocketServer(const std::string& socketName)
    {
        auto ptr = std::make_shared<GenericServer<Platform::Sockets::Local>>();
        ptr->SetServerInfo(socketName);
        ptr->RunConnector();
        return ptr;
    }
    //
    egt::IConnector::Ptr UnixDomainSocketClient(const std::string& socketName)
    {
        auto ptr = std::make_shared<GenericClient<Platform::Sockets::Local>>();
        ptr->SetServerInfo(socketName);
        ptr->RunConnector();
        return ptr;
    }
    //
    egt::IConnector::Ptr UdpV6Server(const std::string& serverName, int serverPort)
    {
        auto ptr = std::make_shared<GenericClient<Platform::Sockets::UdpV6Writer>>();
        ptr->SetServerInfo({serverName, serverPort});
        ptr->RunConnector();
        return ptr;
    }
    //
    egt::IConnector::Ptr UdpV6Client(const std::string& serverName, int serverPort)
    {
        auto ptr = std::make_shared<GenericClient<Platform::Sockets::UdpV6Reader>>();
        ptr->SetServerInfo({serverName, serverPort});
        ptr->RunConnector();
        return ptr;
    }
    //
    egt::IConnector::Ptr LocalProcessServer()
    {
        auto ptr = std::make_shared<LocalServer>();
        ptr->RunConnector();
        return ptr;
    }
    //
    egt::IConnector::Ptr LocalProcessClient(egt::IConnector::Ptr localProcessServer)
    {
        std::shared_ptr<LocalServer> serverPtr = std::dynamic_pointer_cast<LocalServer>(localProcessServer);
        if (nullptr == serverPtr)
        {
            return nullptr;
        }
        auto ptr = std::make_shared<LocalClient>();
        ptr->SetServer(serverPtr);
        ptr->RunConnector();
        return ptr;
    }
    //
    egt::IConnector::Ptr ExecProcessConnector(const std::string& procName)
    {
        auto ptr = std::make_shared<egt::GenericClient<egt::bash_client::StringLineProxy>>();
        ptr->SetServerInfo(std::string(procName));
        ptr->RunConnector();
        return ptr;
    }
}
}
