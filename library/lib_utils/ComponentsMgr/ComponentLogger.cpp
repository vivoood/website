#include "ComponentLogger.h"
#include <iostream>

using namespace egt;

std::function<void(const std::string& str)> ComponentLogger::m_externLogger = nullptr;

ComponentLogger::ComponentLogger()
{
}

ComponentLogger::~ComponentLogger()
{
    std::string str = m_stream.str();
    if (nullptr == ComponentLogger::m_externLogger)
    {
    }
    else
    {
        ComponentLogger::m_externLogger(str);
    }
}

std::stringstream &egt::ComponentLogger::Get()
{
    return m_stream;
}

void ComponentLogger::SetExternLogger(std::function<void (const std::string &)> logger)
{
    ComponentLogger::m_externLogger = logger;
}

