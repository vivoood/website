#include <lib_utils/UniStream/UniStream.h>
#include "StorageMgrCommon.h"

namespace egt
{

///////////////////////////////////////////////////////////////////////////
template<>
oUniStream& operator<< (oUniStream& out, const RemoteStorage::WriteRequest& request)
{
    out << request.dataKey << request.offset << request.gameId << request.isGameParam << request.data;
    return out;
}

///////////////////////////////////////////////////////////////////////////
template<>
iUniStream& operator>> (iUniStream& in, RemoteStorage::WriteRequest& request)
{
    in >> request.dataKey >> request.offset >> request.gameId >> request.isGameParam >> request.data;
    return in;
}

///////////////////////////////////////////////////////////////////////////
template<>
oUniStream& operator<< (oUniStream& out, const RemoteStorage::ReadRequest& request)
{
    out << request.dataKey << request.gameId << request.isGameParam;
    return out;
}

///////////////////////////////////////////////////////////////////////////
template<>
iUniStream& operator>> (iUniStream& in, RemoteStorage::ReadRequest& request)
{
    in >> request.dataKey >> request.gameId >> request.isGameParam;
    return in;
}

///////////////////////////////////////////////////////////////////////////
template<>
oUniStream& operator<< (oUniStream& out, const RemoteStorage::ReadResult& request)
{
    out << request.isOk << request.isSetupOnce << request.dataKey << request.gameId << request.data;
    return out;
}

///////////////////////////////////////////////////////////////////////////
template<>
iUniStream& operator>> (iUniStream& in, RemoteStorage::ReadResult& request)
{
    in >> request.isOk >> request.isSetupOnce >> request.dataKey >> request.gameId >> request.data;
    return in;
}

}

