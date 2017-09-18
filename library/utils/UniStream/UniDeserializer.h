#ifndef UNISTR_UNI_DESERIALIZER_H
#define UNISTR_UNI_DESERIALIZER_H

#include <vector>

#include "UniDeserializerImpl.h"
#include "UniTypeTools.h"
#include <memory>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <list>

namespace egt
{

    class oUniStream;

    class iUniStream
    {
    public:
        using StorageType = std::vector<uint8_t>;
        struct Inplace
        {
            Inplace(iUniStream &d) : deserializer(d){}
            iUniStream& deserializer;
        };

        iUniStream();
        iUniStream(const std::vector<uint8_t> &buff);
        iUniStream(std::vector<uint8_t> &buff);
        iUniStream(std::vector<uint8_t> &&buff);
        iUniStream(oUniStream &serializer);
        iUniStream(oUniStream &&serializer);

        //
        iUniStream(iUniStream&&);
        iUniStream& operator=(iUniStream&&);
        //
        iUniStream(const iUniStream&) = delete;
        iUniStream& operator=(const iUniStream&) = delete;

        std::vector<uint8_t> GetBuffer() const;

        template<typename T> typename
        std::enable_if
        <
                true == types::Info<T>::isArray
            ||  true == types::Info<T>::isFundamental
            ,   iUniStream&
        >::type
        operator>>(T& var)
        {
            _deserialize(var);
            return *this;
        }

        iUniStream& operator>>(iUniStream& var);
        iUniStream& operator>>(oUniStream& var);
        iUniStream& operator>>(Inplace&& inplace);

        inline explicit operator bool() const
        {
            auto res = m_lastOperationResult;
            if (res == false)
            {
                return false;
            }
            return m_lastOperationResult;
        }

        inline bool IsEmpty() const
        {
            if (m_buffPtr == nullptr)
            {
                return true;
            }
            return m_payloadEndIdx == m_endIdx;
        }

        void Clear();

        template<typename T>
        iUniStream& Deserialize(T& t1)
        {
            *this >> t1;
            return *this;
        }

        template<typename T, typename ... Types>
        iUniStream& Deserialize(T& t1, Types& ...  args)
        {
            Deserialize(t1);
            Deserialize(args...);
            return *this;
        }

    private:
        //
        std::vector<uint8_t> m_internalBuff;
        const std::vector<uint8_t>* m_buffPtr = nullptr; // non owning
        size_t m_frontIdx = 0;
        size_t m_endIdx = 0; // not indexable (last idx + 1)
        size_t m_payloadEndIdx = 0;
        bool m_lastOperationResult = false;
        //

        struct InplaceMarker{};
        iUniStream(InplaceMarker, iUniStream& host);
        //void _flush

        inline const uint8_t* _consumeInternalMemory(size_t size)
        {
            if((m_endIdx - m_payloadEndIdx) < size)
            {
                if (true == m_lastOperationResult)
                {
                    m_lastOperationResult = false;
                    return nullptr;
                }
                throw "bad stream deserialization";
            }
            const uint8_t* memPtr = m_buffPtr->data() + m_payloadEndIdx;
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
        _deserialize(T& var)
        {
            // Fundamental, NO array
            const uint8_t* remoteCodePtr = _consumeInternalMemory(1);
            if (nullptr == remoteCodePtr)
            {
                return;
            }
            uint8_t remoteCode = *remoteCodePtr;
            if ( false == types::CodeParser::IsFundamental(remoteCode) ||
                 true == types::CodeParser::IsArray(remoteCode))
            {
                if (true == m_lastOperationResult)
                {
                    m_lastOperationResult = false;
                    return;
                }
                throw "Reading array or non fundamental type as fundamental.";
            }
            size_t remoteSize = types::CodeParser::TypeSize(remoteCode);
            const uint8_t* dumpPtr = _consumeInternalMemory(remoteSize);
            if (nullptr == dumpPtr)
            {
                return;
            }

            deserializer_impl::DeserializeNonArrayFundamental(&var, remoteCode, dumpPtr);
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
        _deserialize(T& var)
        {
            // Fundamental array
            const uint8_t *headerPtr = _consumeInternalMemory( types::_arrayHeaderSize );
            if (nullptr == headerPtr)
            {
                return;
            }
            uint8_t remoteCode;
            size_t arrayCount;

            deserializer_impl::DeserializeArrayHeader(headerPtr, remoteCode, arrayCount);

            if ( false == types::CodeParser::IsFundamental(remoteCode) ||
                 false == types::CodeParser::IsArray(remoteCode))
            {
                if (true == m_lastOperationResult)
                {
                    m_lastOperationResult = false;
                    return;
                }
                throw "Reading non array or non fundamental type as array of fundamentals.";
            }

            types::ArrayHelper<decltype (var)>::Resize(var, arrayCount);
            auto sz = types::ArrayHelper<decltype (var)>::GetSize(var);
            if (sz != arrayCount)
            {
                if (true == m_lastOperationResult)
                {
                    m_lastOperationResult = false;
                    return;
                }
                throw "Reading wrong size for array.";
            }

            size_t arraySize = arrayCount * types::CodeParser::TypeSize(remoteCode);

            const uint8_t *dumpPtr = _consumeInternalMemory( arraySize );
            if (nullptr == dumpPtr)
            {
                return;
            }
            typename types::ArrayHelper<T>::Type* elPtr = types::ArrayHelper<T>::FrontMutable(var);

            deserializer_impl::DeserializeArrayFundamental(elPtr, remoteCode, dumpPtr, arrayCount);
            
            _clearStringZeroes(var);
        }
        //
        // std::vector<bool> is shit
        void _deserialize(std::vector<bool>& var)
        {
            std::vector<uint8_t> copy;
            _deserialize(copy);
            var.resize(copy.size());
            size_t idx = 0;
            for(auto b : copy)
            {
                var[idx] = static_cast<bool>(b);
                idx++;
            }
        }
        //
        template<typename T> inline typename
        std::enable_if
        <
                false == types::Info<T>::isFundamental
            &&  true == types::Info<T>::isArray
            ,   void
        >::type
        _deserialize(T& var)
        {
            // Non fundamental array
            const uint8_t *headerPtr = _consumeInternalMemory( types::_arrayHeaderSize );
            if (nullptr == headerPtr)
            {
                return;
            }
            uint8_t remoteCode;
            size_t arrayCount;

            deserializer_impl::DeserializeArrayHeader(headerPtr, remoteCode, arrayCount);

            if ( true == types::CodeParser::IsFundamental(remoteCode) ||
                 false == types::CodeParser::IsArray(remoteCode))
            {
                if (true == m_lastOperationResult)
                {
                    m_lastOperationResult = false;
                    return;
                }
                throw "Reading array of non fundamental types as something else.";
            }

            types::ArrayHelper<decltype (var)>::Resize(var, arrayCount);
            auto sz = types::ArrayHelper<decltype (var)>::GetSize(var);
            if (sz != arrayCount)
            {
                if (true == m_lastOperationResult)
                {
                    m_lastOperationResult = false;
                    return;
                }
                throw "Reading non array or non fundamental type as array of fundamentals.";
            }

            typename types::ArrayHelper<T>::Type* elPtr = types::ArrayHelper<T>::FrontMutable(var);
            auto arrEnd = elPtr + arrayCount;
            while(elPtr < arrEnd)
            {
                *this >> (*elPtr);
                elPtr++;
            }
        }
        
        
        template<typename T>
        void _clearStringZeroes(T& var)
        {
            
        }
        
        void _clearStringZeroes(std::string& var)
        {
            while(var.empty() == false && var.back() == 0)
            {
                var.pop_back();
            }
        }
    };


    template<typename T1, typename T2>
    iUniStream& operator >>(iUniStream& deserializer, std::pair<T1, T2>& p)
    {
        return deserializer >> p.first >> p.second;
    }

    template<typename KeyType, typename ValueType>
    iUniStream& operator >>(iUniStream& deserializer, std::map<KeyType, ValueType>& m)
    {
        size_t size = 0;
        if (!(deserializer >> size))
        {
            return deserializer;
        }
        m.clear();
        for (size_t i = 0; i < size; ++i)
        {
            std::pair<KeyType, ValueType> p;
            if (!(deserializer >> p))
            {
                return deserializer;
            }
            m.emplace(std::move(p));
        }
        return deserializer;
    }

    template<typename KeyType, typename ValueType>
    iUniStream& operator >>(iUniStream& deserializer, std::unordered_map<KeyType, ValueType>& m)
    {
        size_t size = 0;
        if (!(deserializer >> size))
        {
            return deserializer;
        }
        m.clear();
        for (size_t i = 0; i < size; ++i)
        {
            std::pair<KeyType, ValueType> p;
            if (!(deserializer >> p))
            {
                return deserializer;
            }
            m.emplace(std::move(p));
        }
        return deserializer;
    }

    template<typename T>
    iUniStream& operator <<(iUniStream& deserializer, std::list<T>& l)
    {
        size_t size = 0;
        if (!(deserializer >> size))
        {
            return deserializer;
        }
        l.clear();
        for (size_t i = 0; i < size; ++i)
        {
            T e;
            if (!(deserializer >> e))
            {
                return deserializer;
            }
            l.emplace_back(std::move(e));
        }
        return deserializer;
    }

    template<typename T>
    iUniStream& operator >>(iUniStream& deserializer, const std::set<T>& s)
    {
        size_t size = 0;
        if (!(deserializer >> size))
        {
            return deserializer;
        }
        s.clear();
        for (size_t i = 0; i < size; ++i)
        {
            T e;
            if (!(deserializer >> e))
            {
                return deserializer;
            }
            s.emplace(std::move(e));
        }
        return deserializer;
    }

    template<typename T>
    iUniStream& operator >>(iUniStream& deserializer, const std::unordered_set<T>& s)
    {
        size_t size = 0;
        if (!(deserializer >> size))
        {
            return deserializer;
        }
        s.clear();
        for (size_t i = 0; i < size; ++i)
        {
            T e;
            if (!(deserializer >> e))
            {
                return deserializer;
            }
            s.emplace(std::move(e));
        }
        return deserializer;
    }
    //
    template<typename T> typename
    std::enable_if
    <
            false == types::Info<T>::isArray
        &&  false == types::Info<T>::isFundamental
        ,   iUniStream&
    >::type
    operator>>(iUniStream&, T& var);
}

#endif // UNISTR_UNI_DESERIALIZER_H
