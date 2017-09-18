#ifndef UNIOBJECT_H
#define UNIOBJECT_H
#include <vector>
#include "../UniStream/UniStream.h"
#include <functional>
//#include "types_serializers/TypeSerializers.h"

namespace egt
{
class UniObject
{
public:
    static UniObject Create(std::vector<unsigned char>& buff);

    UniObject();
    UniObject(const UniObject& obj); // copy
    UniObject& operator=(const UniObject& obj); // copy assignment

    UniObject(UniObject&& obj); // move
    UniObject& operator=(UniObject&& obj); // move assignment

    template<typename ValueType>
    UniObject(const ValueType& obj); // copy

    template<typename ValueType>
    UniObject(ValueType&& obj); // move

    template<typename ValueType>
    const std::vector<unsigned char>& operator <<(const ValueType& v);

    template<typename ValueType>
    void operator >>(ValueType& v) const;

    bool operator !=(const UniObject& obj) const;
    bool operator ==(const UniObject& obj) const;

    const std::vector<unsigned char>& GetBuffer() const;
    void SetBuffer(std::vector<unsigned char>& buff);
    void SetConstBuffer(const std::vector<unsigned char>& buff);

private:
    std::vector<unsigned char> m_data;
};


egt::oUniStream& operator<< (egt::oUniStream& out, const egt::UniObject& obj);
egt::iUniStream& operator>> (egt::iUniStream& in, egt::UniObject& obj);

}
#include "UniObject.hpp"


typedef egt::UniObject Var;
#endif // UNIOBJECT_H
