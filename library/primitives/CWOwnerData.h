#ifndef CWOWNERDATA_H
#define CWOWNERDATA_H

#include <string>
#include <map>
#include <mutex>

class CWFreeOffersData
{
    friend class CWOwnerData;
public:
    std::string strFrom = "n/a";
    std::string strTo = "n/a";
    std::string strAirline = "n/a";
    std::string strPrice = "n/a";
    std::string strInstead = "n/a";
    bool bOneWay = false;
    bool bDirectFlight = false;
    std::string strHyperlink = "n/a";
    std::string GetHash();
    void print();
private:
    friend std::ostream& operator<< ( std::ostream& os, const CWFreeOffersData& dt );
    friend std::istream& operator>> ( std::istream& is, CWFreeOffersData& dt );
};

class CWOwnerData
{
public:

    void SaveFreeOffers ();
    bool LoadFreeOffers ();
    void AddFreeOffer ( CWFreeOffersData d );
    bool RemoveFreeOffer ( std::string hash );
    int nFreeOffersCnt = 0;
    void print();

    std::map<std::string, CWFreeOffersData> mapFreeOffers;
private:
    std::mutex mtx;
};

#endif // CWOWNERDATA_H
// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 
