#include "UniMsg.h"
///////////////////////////////////////////////////////////////////////////

namespace egt
{
    ///////////////////////////////////////////////////////////////////////////
    template <>
    iUniStream& operator>> (iUniStream& in, GenericMsg<oUniStream, iUniStream>& msg)
    {
        return in   >> msg.name
                    >> msg.description
                    >> msg.gameId
                    >> GenericMsgPrivateAccess<oUniStream, iUniStream>::GetValues(msg);
    }

    ///////////////////////////////////////////////////////////////////////////
    template <>
    oUniStream& operator<< (oUniStream& out, const GenericMsg<oUniStream, iUniStream>& msg)
    {
        return out  << msg.name
                    << msg.description
                    << msg.gameId
                    << GenericMsgPrivateAccess<oUniStream, iUniStream>::GetValues(msg);
    }

}

