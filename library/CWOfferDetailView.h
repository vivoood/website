#ifndef CWOFFERDETAILVIEW_H
#define CWOFFERDETAILVIEW_H

#include <Wt/WContainerWidget>

#include "CWUser.h"

class CWOfferDetailView : public Wt::WContainerWidget
{
public:
    CWOfferDetailView ( std::string usrhash, std::string strPayload, OffersData::SOffer & offr, Wt::WContainerWidget* parent = 0 );
    CWOfferDetailView ( std::string usrhash, std::string strPayload, Wt::WContainerWidget* parent = 0 );
};

#endif //CWOFFERDETAILVIEW_H

// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 
