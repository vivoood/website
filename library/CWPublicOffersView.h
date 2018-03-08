#ifndef CWPUBLICOFFERSVIEW_H
#define CWPUBLICOFFERSVIEW_H

#include <Wt/WContainerWidget>

#include "CWUser.h"

class CWPublicOffersView : public Wt::WContainerWidget
{
private:
    friend class Factory;
    CWPublicOffersView ( std::string usrhash, std::string strPayload, Wt::WContainerWidget* parent = 0 );
    void CreateView ( Wt::WContainerWidget * p, std::vector<OffersData::SOffer> & v, unsigned int uiShownElements, bool bClear );
    void GetPayloadHeader ( const std::string & payload, std::string & result );
    void GetPayloadBody ( const std::string & payload, std::string & result );
    void show_free_offers_random();
    void show_best_offers();
    void show_offers_by_continent ( const std::string & continent );
    void show_all_offers();

    std::vector<OffersData::SOffer> vOfData;
    unsigned int uiMaxFreeVisibleOffers = 5;
    unsigned int uiMaxBestVisibleOffers = 5;
    int nChangeTimeDuration = 2000;
    unsigned int uiShownElementsPerInstance = 0;
};

#endif //CWPUBLICOFFERSVIEW_H

// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 

