#include "BinderLogger.h"
#include <iostream>

using namespace egt;

std::function<void(const std::string& str)> BinderLogger::m_externLogger = nullptr;

BinderLogger::BinderLogger()
{
}

BinderLogger::~BinderLogger()
{
    std::string str = m_stream.str();
    if (nullptr == BinderLogger::m_externLogger)
    {
    }
    else
    {
        BinderLogger::m_externLogger(str);
    }
}

std::stringstream &egt::BinderLogger::Get()
{
    return m_stream;
}

void BinderLogger::SetExternLogger(std::function<void (const std::string &)> logger)
{
    BinderLogger::m_externLogger = logger;
}

