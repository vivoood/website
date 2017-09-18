//#include "UniSerializerImpl.h"
//#include "UniTypeTools.h"

//namespace uni
//{
//    namespace serializer_impl
//    {
//        /////////////////////////////////////////////////////////////////////
//        /////////////////////////////////////////////////////////////////////

//        template<typename T>
//        void SerializeNonArrayFundamental(const T* val, uint8_t* buff) noexcept
//        {
//            *buff++ = egt::types::Code<T>::value;
//            const uint8_t* src = reinterpret_cast<const uint8_t*>(val);
//            CopyToBuff<sizeof(T)>(buff, src);
//        }

//        void SerializeArrayHeader(uint8_t* buff, uint8_t typeCode, size_t size) noexcept
//        {
//            // write element type marker
//            *buff = typeCode;

//            // write elements count
//            uint32_t s = static_cast<uint32_t>(size);
//            CopyToBuff<4>(buff+1, reinterpret_cast<const uint8_t*>(&s));
//        }

//        /////////////////////////////////////////////////////////////////////
//        template<typename T>
//        void SerializeArrayFundamental(const T* val, uint8_t* buff, size_t count) noexcept
//        {
//            SerializeArrayHeader(buff, egt::types::Code<T>::value | egt::types::_markArray, count);
//            buff += ::egt::types::_arrayHeaderSize;

//            // write elements
//            const uint8_t* src = reinterpret_cast<const uint8_t*>(val);
//            auto arrayEnd = src + sizeof(T) * count;

//            while(src < arrayEnd)
//            {
//                CopyToBuff<sizeof(T)>(buff, src);
//                src += sizeof (T);
//                buff += sizeof (T);
//            }
//        }

//        /////////////////////////////////////////////////////////////////////
//        /////////////////////////////////////////////////////////////////////
//        /////////////////////////////////////////////////////////////////////

//        UNISTR_DECLARE_ALL_FUNDAMENTALS(void, SerializeNonArrayFundamental, const, *, uint8_t*)
//        UNISTR_DECLARE_ALL_FUNDAMENTALS(void, SerializeArrayFundamental, const, *, uint8_t*, size_t)
//    }
//}
