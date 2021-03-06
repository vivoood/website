#include "CWOwnerQueries.h"

#include <Wt/WText>
#include <Wt/WBreak>
#include <Wt/WTable>
#include <dirent.h>

#include "CWUser.h"
#include "Factory.h"

namespace
{

void GetFilesFromDir ( std::string currDir, std::vector<std::string> & files )
{
    DIR *dp;
    struct dirent *dirp;
    if ( ( dp  = opendir ( currDir.c_str() ) ) == NULL )
    {
        files.push_back ( std::string ( "error_for_open_dir" ) );
        return;
    }

    while ( ( dirp = readdir ( dp ) ) != NULL )
    {
        std::string str ( dirp->d_name );
        if ( str != ".." )
            if ( str != "." )
                if ( ! CWUser::CheckOwner ( str ) )
                    files.push_back ( str );
    }

    closedir ( dp );
}

void SetTableContent ( Wt::WTableCell * pTC, std::string val )
{
    pTC->addWidget ( new Wt::WText ( val ) );
    pTC->setContentAlignment ( Wt::AlignRight );
}

class CWTableAbonaments : public Wt::WContainerWidget
{
public:
    CWTableAbonaments ( CWUser & u )
    {
        std::vector< std::vector< std::string > > v = u.ExportAbonaments ( u );

        Wt::WTable * table = new Wt::WTable();
        table->setHeaderCount ( 1 );
        table->setWidth ( Wt::WLength ( "100%" ) );

        for ( unsigned int i = 0; i < v.size(); ++i )
            for ( unsigned int j = 0; j < v[i].size(); ++j )
                SetTableContent ( table->elementAt ( i, j ), v[i][j] );

        this->setContentAlignment ( Wt::AlignCenter );
        this->addWidget ( new Wt::WBreak() );
        this->addWidget ( new Wt::WText ( u._mail ) );
        this->addWidget ( new Wt::WBreak() );
        this->addWidget ( table );
    }
};

}

CWOwnerQueries::CWOwnerQueries ( IWidgetData * pD, Wt::WContainerWidget* parent ) : WContainerWidget ( parent )
{
    std::vector<std::string> files;
    GetFilesFromDir ( "users", files );

    for ( auto & i : files )
    {
        CWUser u;
        u.load ( i );
        this->addWidget ( new CWTableAbonaments ( u ) );
    }
}

// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 
