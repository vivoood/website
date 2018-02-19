#include "LWConstants.h"

LWConstants::LWConstants()
{
    std::vector<WidgetData::STableData> vTableRow;
    WidgetData::STableData dTable;

    /** *************************************** */
    dTable.strWidgetName = "CWOwnerSettings";
    dTable.strWidgetData = "empty";

    vTableRow.clear();
    vTableRow.push_back ( dTable );
    m_Table.vTable.push_back ( vTableRow );
    /** *************************************** */

    /** *************************************** */
    dTable.strWidgetName = "CWOwnerQueries";
    dTable.strWidgetData = "empty";

    vTableRow.clear();
    vTableRow.push_back ( dTable );
    m_Table.vTable.push_back ( vTableRow );
    /** *************************************** */

    /** *************************************** */
    dTable.strWidgetName = "CWOwnerSettings";
    dTable.strWidgetData = "empty";

    vTableRow.clear();
    vTableRow.push_back ( dTable );
    m_Table.vTable.push_back ( vTableRow );
    /** *************************************** */

    /** *************************************** */
    dTable.strWidgetName = "CWPublicOffers";
    dTable.strWidgetData = "SOffersRight";

    vTableRow.clear();
    vTableRow.push_back ( dTable );
    m_Table.vTable.push_back ( vTableRow );
    /** *************************************** */

    m_mapData.insert ( std::pair<std::string, IWidgetData*> ( "STable", &m_Table ) );
}

#include "Debug.h"

IWidgetData * LWConstants::GetData ( std::string str, std::string strHash )
{
    std::map<std::string, IWidgetData*>::iterator it;
    it = m_mapData.find ( str );
    if ( it != m_mapData.end() )
    {
        ( *it ).second->strHash = strHash;
        return ( *it ).second;
    }

    if ( str == "empty" )
        return nullptr;

    Debug::print_backtrace ( strHash );
    return nullptr;
}

// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 

