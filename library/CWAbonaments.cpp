#include "CWAbonaments.h"

#include <Wt/WText>
#include <Wt/WBreak>
#include <Wt/WPushButton>

#include "CWTable.h"
#include "CWSignals.h"

CWAbonaments::CWAbonaments ( std::string usrhash, std::string strPayload, Wt::WContainerWidget* parent ) : WContainerWidget ( nullptr )
{
    CWTable * pTable = new CWTable();

    pTable->elementAt ( 0, 5 )->addWidget ( new Wt::WText ( "Choose your abonament" ) );

    for ( unsigned int i = 0; i < _abonaments.size(); i++ )
    {
        std::string & val = _abonaments[i];
        if ( val.empty() )
        {
            pTable->elementAt ( 3, i )->addWidget ( new Wt::WText ( "" ) );
        }
        else
        {
            Wt::WPushButton * pBtn = new Wt::WPushButton ( val );
            pTable->elementAt ( 3, i )->addWidget ( pBtn );
            pTable->elementAt ( 3, i )->setContentAlignment ( Wt::AlignCenter );

            pBtn->clicked().connect ( std::bind ( [=]()
            {
                gCWSignals.signal_create_center_column.emit ( usrhash, "PayStation" );
            } ) );
        }
    }

    this->addWidget ( pTable );
}

// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 
