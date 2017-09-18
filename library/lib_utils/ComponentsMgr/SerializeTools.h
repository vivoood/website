#ifndef SERIALIZETOOLS_H
#define SERIALIZETOOLS_H
#include "ComponentsMgr.h"
#include <functional>
#include <string>

namespace egt {

class SerializeTools
{
public:
    template<typename ComponentFactory>
    static bool BeautifyComponentsXml(const std::string& fileName)
    {
        bool isOk = BeautifyComponentsXml(fileName,
                [&](const std::string& mgrName)->ComponentMgrPtr
                {
                    return ComponentMgr::CreateFromFile<ComponentFactory>(fileName, mgrName);
                });
        return isOk;
    }

    // Merge mgr to existing component manager in xml file
    template<typename ComponentFactory>
    static bool AddToComponentMgr(const std::string& fileName, ComponentMgrPtr newMgr)
    {
        bool isOk = AddToComponentMgr(fileName, newMgr,
                [&](const std::string& mgrName)->ComponentMgrPtr
                {
                    return ComponentMgr::CreateFromFile<ComponentFactory>(fileName, mgrName);
                });
        return isOk;
    }

    // Merge mgr to existing component manager in xml file
    template<typename ComponentFactory>
    static bool ReplaceComponentMgr(const std::string& fileName, ComponentMgrPtr newMgr)
    {
        bool isOk = ReplaceComponentMgr(fileName, newMgr,
                [&](const std::string& mgrName)->ComponentMgrPtr
                {
                    return ComponentMgr::CreateFromFile<ComponentFactory>(fileName, mgrName);
                });
        return isOk;
    }

private:
    SerializeTools();

    static bool BeautifyComponentsXml(const std::string& fileName,
                                      std::function<ComponentMgrPtr(const std::string& mgrName)> mgrFactory);

    static bool AddToComponentMgr(const std::string& fileName, ComponentMgrPtr newMgr,
                                  std::function<ComponentMgrPtr(const std::string& mgrName)> mgrFactory);

    static bool ReplaceComponentMgr(const std::string& fileName, ComponentMgrPtr newMgr,
                                  std::function<ComponentMgrPtr(const std::string& mgrName)> mgrFactory);
};

}

#endif // SERIALIZETOOLS_H
