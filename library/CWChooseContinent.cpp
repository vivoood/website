#include "CWChooseContinent.h"

#include <Wt/WText>
#include <Wt/WPushButton>

#include "CWSignals.h"

CWChooseContinent::CWChooseContinent ( std::string usrhash, std::string strPayload, Wt::WContainerWidget* parent ) : WContainerWidget ( nullptr )
{
    if ( usrhash == "Guest" )
    {
        std::vector<Wt::WPushButton *> vb;
        vb.push_back ( new Wt::WPushButton ( "All" ) );
        vb.push_back ( new Wt::WPushButton ( "Africa" ) );
        vb.push_back ( new Wt::WPushButton ( "Asia" ) );
        vb.push_back ( new Wt::WPushButton ( "Europe" ) );
        vb.push_back ( new Wt::WPushButton ( "North America" ) );
        vb.push_back ( new Wt::WPushButton ( "Australia" ) );
        vb.push_back ( new Wt::WPushButton ( "South America" ) );

        for ( auto & btn : vb )
        {
            btn->clicked().connect ( std::bind ( [=]()
            {
                if ( btn->text().toUTF8() == "All" )
                {
                    gCWSignals.signal_create_center_column.emit ( usrhash, "show_free_offers_random" );
                }
                else
                {
                    gCWSignals.signal_create_center_column.emit ( usrhash, std::string ( "continent:" ) + btn->text().toUTF8() );
                }
            } ) );

            this->addWidget ( btn );
        }
    }
    else
    {
        this->addWidget ( new Wt::WText ( "" ) );
    }
}

// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 
