// Signals.h ----------------------------------------------------------------------

#ifndef _EGT_SIGNALS_H_
#define _EGT_SIGNALS_H_

#include <algorithm>
#include <functional>
#include <unordered_map>
#include <vector>

namespace egt{

/**
 Signal class.

 General purpose boost like signal light implementation
*/
template <class... Args>
class Signal
{
public:
    using ConnectionId = unsigned long long;
    using SlotsSignitureType = std::function<void(Args...)>;
    using SlotPair = std::pair<ConnectionId, SlotsSignitureType>;
    using SlotContainerType = std::vector<SlotPair>;

    Signal(){ };

    Signal( const Signal& ) = delete;
    Signal& operator=( const Signal& ) = delete;

    template<class Fn>
    ConnectionId connect(Fn&& fn)
    {
        static ConnectionId id = 0;
        id++;
        m_slots.push_back( SlotPair(id, std::forward<Fn>(fn)) );
        return id;
    }

    void disconnect( const ConnectionId cid ) {
        auto i = m_slots.find(cid);

        if( m_slots.cend() != i ) {
            m_slots.erase(i);
        }
    }

    void operator()( Args... args ) const
    {
        emit( std::forward<Args>(args)... );
    }

    void emit( Args... args ) const
    {
        for( auto& f: m_slots ) {
            f.second(args...);
        }
    }

private:
    SlotContainerType m_slots;
};

} // namespace egt
#endif //_EGT_SIGNALS_H_
