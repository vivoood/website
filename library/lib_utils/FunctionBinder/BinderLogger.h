#ifndef BINDERLOGGER_H
#define BINDERLOGGER_H
#include <string>
#include <sstream>
#include <functional>

namespace egt{
class BinderLogger
{
public:
    BinderLogger();
    ~BinderLogger();
    std::stringstream &Get();
    static void SetExternLogger(std::function<void(const std::string& str)> logger);
private:
    std::stringstream m_stream;
    static std::function<void(const std::string& str)> m_externLogger;
};
}
#endif // BINDERLOGGER_H
