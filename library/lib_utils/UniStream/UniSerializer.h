#ifndef UNISTR_UNI_SERIALIZER_H
#define UNISTR_UNI_SERIALIZER_H

#include <vector>

#include "UniSerializerImpl.h"
#include "UniTypeTools.h"
#include <memory>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <list>


namespace egt
{
    class iUniStream;
	class oUniStream
	{
    public:
        using StorageType = std::vector<uint8_t>;
        struct Inplace
        {
            Inplace(oUniStream &s) : serializer(s){}
            oUniStream& serializer;
        };

        oUniStream();

        //
        oUniStream(oUniStream&&);
        oUniStream(std::vector<uint8_t>&& buff);
        oUniStream& operator=(oUniStream&&);
        //
        oUniStream(const oUniStream&) = delete;
        oUniStream& operator=(const oUniStream&) = delete;

        inline explicit operator bool() const
        {
            return true;
        }

        template<typename T> typename
        std::enable_if
        <
                types::Info<T>::isArray
            ||  types::Info<T>::isFundamental
            ,   oUniStream&
        >::type
        operator<<(const T& var)
        {
            _serialize(var);
            return *this;
        }


        oUniStream& operator<<(const oUniStream& var);
        oUniStream& operator<<(const iUniStream& var);
        oUniStream& operator>>(Inplace&& inplace);

        oUniStream& Serialize() { return *this; }

        template<typename T>
        oUniStream& Serialize(T&& t1)
        {
            (*this) << std::forward<T>(t1);
            return *this;
        }

        ///////////////////////////////////////////////////////////////////////////
        template<typename T, typename ... Types>
        oUniStream& Serialize(T&& t1, Types&& ...  args)
        {
            (*this) << std::forward<T>(t1);
            (*this).Serialize(std::forward<Types>(args)...);
            return *this;
        }

        void Invalidate();
        void Clear();

        std::vector<uint8_t> &GetBuffer();
        inline StorageType &GetStorage() { return GetBuffer(); }
    private:
        //
        std::vector<uint8_t> m_internalBuff;
        std::vector<uint8_t> m_inplacedBufferCopy;
        std::vector<uint8_t>* m_buffPtr = nullptr; // non owning
        size_t m_frontIdx = 0;
        size_t m_endIdx = 0; // not indexable (last idx + 1)
        size_t m_payloadEndIdx = 0;
        //

        struct InplaceMarker{};
        oUniStream(InplaceMarker, oUniStream& host);
        //void _flush

        inline uint8_t* _getInternalMemory(size_t size)
        {
            if((m_endIdx - m_payloadEndIdx) < size)
            {
                if (m_endIdx != m_buffPtr->size())
                {
                    throw "Probably bad using of inplaced streams";
                }
                size_t missing = size - (m_endIdx - m_payloadEndIdx);
                m_buffPtr->resize( m_buffPtr->size() * 2 +  missing);
                m_endIdx = m_buffPtr->size();
            }
            uint8_t* memPtr = m_buffPtr->data() + m_payloadEndIdx;
            m_payloadEndIdx += size;
            return memPtr;
        }
        //
        template<typename T> inline typename
        std::enable_if
        <
                true == types::Info<T>::isFundamental
            &&  false == types::Info<T>::isArray
            ,   void
        >::type
        _serialize(const T& var)
        {
            // Fundamental, NO array
            uint8_t* memPtr = _getInternalMemory(types::Info<T>::typeSerializedSize);
            serializer_impl::SerializeNonArrayFundamental(&var, memPtr);
        }
        //
        template<typename T> inline typename
        std::enable_if
        <
                true == types::Info<T>::isFundamental
            &&  true == types::Info<T>::isArray
            &&  false == std::is_same<T, std::vector<bool>>::value
            ,   void
        >::type
        _serialize(const T& var)
        {
            // Fundamental array
            uint8_t* memPtr = _getInternalMemory(types::ArrayHelper<T>::GetSerializedSize(var));
            size_t arraySize = types::ArrayHelper<T>::GetSize(var);
            serializer_impl::SerializeArrayFundamental(types::ArrayHelper<T>::FrontConst(var), memPtr, arraySize);
        }
        //
        // std::vector<bool> is a shit !
        void _serialize(const std::vector<bool>& var)
        {
            // Fundamental array
            std::vector<uint8_t> copy(var.size());
            size_t idx = 0;
            for (auto b : var)
            {
                copy[idx] = static_cast<uint8_t>(b);
                idx++;
            }
            _serialize(copy);
        }
        //
        template<typename T> inline typename
        std::enable_if
        <
                false == types::Info<T>::isFundamental
            &&  true == types::Info<T>::isArray
            ,   void
        >::type
        _serialize(const T& var)
        {
            // Non fundamental array
            uint8_t* memPtr = _getInternalMemory( types::_arrayHeaderSize );
            size_t arraySize = types::ArrayHelper<T>::GetSize(var);
            serializer_impl::SerializeArrayHeader(memPtr, types::Code<T>::value, arraySize);
            const typename types::ArrayHelper<T>::Type* elPtr = types::ArrayHelper<T>::FrontConst(var);
            auto arrEnd = elPtr + arraySize;
            while(elPtr < arrEnd)
            {
                *this << (*elPtr);
                elPtr++;
            }
        }
	};

    template<typename T1, typename T2>
    oUniStream& operator <<(oUniStream& serializer, const std::pair<T1, T2>& p)
    {
        return serializer << p.first << p.second;
    }

    template<typename KeyType, typename ValueType>
    oUniStream& operator <<(oUniStream& serializer, const std::map<KeyType, ValueType>& m)
    {
        serializer << m.size();
        for (const auto& p : m)
        {
            serializer << p;
        }
        return serializer;
    }

    template<typename KeyType, typename ValueType>
    oUniStream& operator <<(oUniStream& serializer, const std::unordered_map<KeyType, ValueType>& m)
    {
        serializer << m.size();
        for (const auto& p : m)
        {
            serializer << p;
        }
        return serializer;
    }

    template<typename T>
    oUniStream& operator <<(oUniStream& serializer, const std::list<T>& l)
    {
        serializer << l.size();
        for (const auto& e : l)
        {
            serializer << e;
        }
        return serializer;
    }

    template<typename T>
    oUniStream& operator <<(oUniStream& serializer, const std::set<T>& s)
    {
        serializer << s.size();
        for (const auto& e : s)
        {
            serializer << e;
        }
        return serializer;
    }

    template<typename T>
    oUniStream& operator <<(oUniStream& serializer, const std::unordered_set<T>& s)
    {
        serializer << s.size();
        for (const auto& e : s)
        {
            serializer << e;
        }
        return serializer;
    }
    //
    template<typename T> typename
    std::enable_if
    <
            false == types::Info<T>::isArray
        &&  false == types::Info<T>::isFundamental
        ,   oUniStream&
    >::type
    operator<<(oUniStream&, const T& var);
}



#endif // UNISTR_UNI_SERIALIZER_H
