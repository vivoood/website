#include "CWOwnerData.h"

#include <iostream>
#include <fstream>
#include <algorithm>

#include "CWHash.h"

namespace
{

std::string ConvertStr ( std::string str, bool tofile )
{
    if ( tofile )
        std::replace ( str.begin(), str.end(), ' ', ':' );
    else
        std::replace ( str.begin(), str.end(), ':', ' ' );

    return str;
}

}

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
    os << ConvertStr ( dt.strFrom, true ) << std::endl;
    os << ConvertStr ( dt.strTo, true ) << std::endl;
    os << ConvertStr ( dt.strAirline, true ) << std::endl;
    os << ConvertStr ( dt.strPrice, true ) << std::endl;
    os << ConvertStr ( dt.strInstead, true ) << std::endl;
    os << dt.bOneWay << std::endl;
    os << dt.bDirectFlight << std::endl;
    os << ConvertStr ( dt.strHyperlink, true ) << std::endl;
    return os;
}

std::istream& operator>> ( std::istream& is, CWFreeOffersData& dt )
{
    is >> dt.strFrom;
    dt.strFrom = ConvertStr ( dt.strFrom, false );

    is >> dt.strTo;
    dt.strTo = ConvertStr ( dt.strTo, false );

    is >> dt.strAirline;
    dt.strAirline = ConvertStr ( dt.strAirline, false );

    is >> dt.strPrice;
    dt.strPrice = ConvertStr ( dt.strPrice, false );

    is >> dt.strInstead;
    dt.strInstead = ConvertStr ( dt.strInstead, false );

    is >> dt.bOneWay;

    is >> dt.bDirectFlight;

    is >> dt.strHyperlink;
    dt.strHyperlink = ConvertStr ( dt.strHyperlink, false );

    return is;
}

std::ostream& operator<< ( std::ostream& os, CWSettingsData& dt )
{
    os << ConvertStr ( dt.strTitle, true ) << std::endl;
    os << ConvertStr ( dt.strSlogan, true ) << std::endl;
    return os;
}

std::istream& operator>> ( std::istream& is, CWSettingsData& dt )
{
    is >> dt.strTitle;
    dt.strTitle = ConvertStr ( dt.strTitle, false );

    is >> dt.strSlogan;
    dt.strSlogan = ConvertStr ( dt.strSlogan, false );

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

void CWOwnerData::SaveSettings()
{
    std::lock_guard<std::mutex> lock ( mtxSett );
    std::ofstream outfile ( "owner/settings" );
    outfile << settingsData;
    outfile.close();
}

bool CWOwnerData::LoadSettings()
{
    std::lock_guard<std::mutex> lock ( mtxSett );
    std::ifstream infile ( "owner/settings" );
    infile >> settingsData;
    infile.close();

    return true;
}

// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 





