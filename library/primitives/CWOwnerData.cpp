#include "CWOwnerData.h"

#include <iostream>
#include <fstream>
#include <algorithm>

#include "CWHash.h"

void CWFreeOffersData::print()
{
    std::cout << strFrom << std::endl;
    std::cout << strTo << std::endl;
    std::cout << strAirline << std::endl;
    std::cout << strPrice << std::endl;
    std::cout << strInstead << std::endl;
    std::cout << bOneWay << std::endl;
    std::cout << bDirectFlight << std::endl;
    std::cout << strHyperlink << std::endl;
}

void CWOwnerData::print()
{
    if ( mapFreeOffers.size() == 0 )
    {
        std::cout << "Empty - " << "nFreeOffersCnt = " << nFreeOffersCnt << std::endl;
        return;
    }

    std::cout << "nFreeOffersCnt = " << nFreeOffersCnt << std::endl;
    for ( std::map<std::string, CWFreeOffersData>::iterator it = mapFreeOffers.begin(); it != mapFreeOffers.end(); ++it )
        it->second.print();
}

std::ostream& operator<< ( std::ostream& os, const CWFreeOffersData& dt )
{
    os << dt.strFrom << std::endl;
    os << dt.strTo << std::endl;
    os << dt.strAirline << std::endl;
    os << dt.strPrice << std::endl;
    os << dt.strInstead << std::endl;
    os << dt.bOneWay << std::endl;
    os << dt.bDirectFlight << std::endl;
    os << dt.strHyperlink << std::endl;
    return os;
}

std::istream& operator>> ( std::istream& is, CWFreeOffersData& dt )
{
    is >> dt.strFrom;
    is >> dt.strTo;
    is >> dt.strAirline;
    is >> dt.strPrice;
    is >> dt.strInstead;
    is >> dt.bOneWay;
    is >> dt.bDirectFlight;
    is >> dt.strHyperlink;
    return is;
}

std::string CWFreeOffersData::GetHash()
{
    return CWHash::Get ( strFrom + strTo + strAirline + strPrice + strInstead + strHyperlink );
}

void CWOwnerData::SaveFreeOffers()
{
    std::lock_guard<std::mutex> lock ( mtx );
    std::ofstream outfile ( "owner/free_offers" );
    nFreeOffersCnt = mapFreeOffers.size();
    outfile << nFreeOffersCnt << std::endl;
    for ( auto & i : mapFreeOffers )
        outfile << i.second;
    outfile.close();
}

bool CWOwnerData::LoadFreeOffers()
{
    std::lock_guard<std::mutex> lock ( mtx );
    std::ifstream infile ( "owner/free_offers" );
    infile >> nFreeOffersCnt;
    
    mapFreeOffers.clear();
    
    for ( int i = 0; i < nFreeOffersCnt; i++ )
    {
        CWFreeOffersData d;
        infile >> d;
        AddFreeOffer ( d );
    }
    infile.close();

    return nFreeOffersCnt == mapFreeOffers.size();
}

void CWOwnerData::AddFreeOffer ( CWFreeOffersData d )
{
    mapFreeOffers.insert ( std::pair<std::string, CWFreeOffersData> ( d.GetHash(), d ) );
}

bool CWOwnerData::RemoveFreeOffer ( std::string hash )
{
    std::map<std::string, CWFreeOffersData>::iterator it;
    it = mapFreeOffers.find ( hash );
    if ( it == mapFreeOffers.end() )
        return false;

    mapFreeOffers.erase ( it );
    return true;
}

// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 



