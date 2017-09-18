#include "SerializeTools.h"
//#include "pugixml.hpp"
#include <algorithm>
#include <iostream>
#include <fstream>
using namespace egt;

/////////////////////////////////////////////////////////////////////////////
bool SerializeTools::BeautifyComponentsXml(const std::string& fileName,
                                           std::function<ComponentMgrPtr(const std::string& mgrName)> mgrFactory)
{
    auto allMangersNames = ComponentMgr::FindAllManagersInFile(fileName);

    std::vector<ComponentMgrPtr> allManagers;
    for (const auto& mgrName : allMangersNames)
    {
        auto mgr = mgrFactory(mgrName);
        if (nullptr != mgr)
        {
            allManagers.push_back(mgr);
        }
    }

    std::sort(allManagers.begin(), allManagers.end(), [](ComponentMgrPtr mgr1, ComponentMgrPtr mgr2) {
        return mgr1->GetName() < mgr2->GetName();
    });

    // clear the file
    std::ofstream(fileName).close();
    for (const auto& mgr : allManagers)
    {
        mgr->Serialize(fileName);
    }

    return true;
}

/////////////////////////////////////////////////////////////////////////////
bool SerializeTools::AddToComponentMgr(const std::string& fileName, ComponentMgrPtr newMgr,
                                              std::function<ComponentMgrPtr(const std::string& mgrName)> mgrFactory)
{
    auto allMangersNames = ComponentMgr::FindAllManagersInFile(fileName);

    std::vector<ComponentMgrPtr> allManagers;
    bool newMgrReady = false;
    for (const auto& mgrName : allMangersNames)
    {
        auto orgMgr = mgrFactory(mgrName);
        if (orgMgr->GetName() == newMgr->GetName())
        {
            orgMgr = ComponentMgr::Merge(orgMgr, newMgr, newMgr->GetName());
            newMgrReady = true;
        }
        if (nullptr != orgMgr)
        {
            allManagers.push_back(orgMgr);
        }
    }
    if (false == newMgrReady)
    {
        allManagers.push_back(newMgr);
    }

    std::sort(allManagers.begin(), allManagers.end(), [](ComponentMgrPtr mgr1, ComponentMgrPtr mgr2) {
        return mgr1->GetName() < mgr2->GetName();
    });

    // clear the file
    std::ofstream(fileName).close();
    for (const auto& mgr : allManagers)
    {
        mgr->Serialize(fileName);
    }

    return true;
}


/////////////////////////////////////////////////////////////////////////////
bool SerializeTools::ReplaceComponentMgr(const std::string& fileName, ComponentMgrPtr newMgr,
                                              std::function<ComponentMgrPtr(const std::string& mgrName)> mgrFactory)
{
    auto allMangersNames = ComponentMgr::FindAllManagersInFile(fileName);

    std::vector<ComponentMgrPtr> allManagers;
    for (const auto& mgrName : allMangersNames)
    {
        auto orgMgr = mgrFactory(mgrName);
        if (orgMgr->GetName() == newMgr->GetName())
        {
            continue;
        }
        if (nullptr != orgMgr)
        {
            allManagers.push_back(orgMgr);
        }
    }
    allManagers.push_back(newMgr);

    std::sort(allManagers.begin(), allManagers.end(), [](ComponentMgrPtr mgr1, ComponentMgrPtr mgr2) {
        return mgr1->GetName() < mgr2->GetName();
    });

    // clear the file
    std::ofstream(fileName).close();
    for (const auto& mgr : allManagers)
    {
        mgr->Serialize(fileName);
    }

    return true;
}
