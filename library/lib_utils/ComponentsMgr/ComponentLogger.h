#ifndef COMPONENTLOGGER_H
#define COMPONENTLOGGER_H
#include <string>
#include <sstream>
#include <functional>

namespace egt{
class ComponentLogger
{
public:
    ComponentLogger();
    ~ComponentLogger();
    std::stringstream &Get();
    static void SetExternLogger(std::function<void(const std::string& str)> logger);
private:
    std::stringstream m_stream;
    static std::function<void(const std::string& str)> m_externLogger;
};
}
#endif // COMPONENTLOGGER_H
