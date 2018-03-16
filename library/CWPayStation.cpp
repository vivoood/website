#include "CWPayStation.h"

#include <Wt/WText>

CWPayStation::CWPayStation ( std::string usrhash, std::string strPayload, Wt::WContainerWidget* parent ) : WContainerWidget ( nullptr )
{
    this->addWidget ( new Wt::WText ("CWPayStation") );
}

