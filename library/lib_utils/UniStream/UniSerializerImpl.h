#ifndef UNISTR_UNI_SERIALIZER_IMPL_H
#define UNISTR_UNI_SERIALIZER_IMPL_H

#include <cstdint>
#include <cstddef>

namespace egt
{
    namespace serializer_impl
    {
        //
        template<typename T>
        void SerializeNonArrayFundamental(const T* val, uint8_t* buff) noexcept;
        //
        template<typename T>
        void SerializeArrayFundamental(const T* val, uint8_t* buff, size_t count) noexcept;
        //
        void SerializeArrayHeader(uint8_t* buff, uint8_t typeCode, size_t size) noexcept;
    }
}
#include "UniSerializerImpl.hpp"
#endif //UNISTR_UNI_SERIALIZER_IMPL_H

