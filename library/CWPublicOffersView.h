#ifndef CWPUBLICOFFERSVIEW_H
#define CWPUBLICOFFERSVIEW_H

#include <Wt/WContainerWidget>

#include "CWUser.h"

class CWPublicOffersView : public Wt::WContainerWidget
{
private:
    friend class Factory;
    CWPublicOffersView ( std::string usrhash, std::string strPayload, Wt::WContainerWidget* parent = 0 );
    void CreateView ( Wt::WContainerWidget * p, std::vector<OffersData::SOffer> & v );
    
    std::vector<OffersData::SOffer> vOfData;
    unsigned int uiMaxVisibleOffers = 4;
    int nChangeTimeDuration = 2000;
};

#endif //CWPUBLICOFFERSVIEW_H

// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 
