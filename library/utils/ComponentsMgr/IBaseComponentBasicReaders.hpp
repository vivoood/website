#ifndef IBASECOMPONENT_BASIC_READERS_HPP
#define IBASECOMPONENT_BASIC_READERS_HPP


///////////////////////////////////////////////////////////////////////////
template<typename T>
bool IBaseComponent::Read(const pugi::xml_node& xmlNode, const std::string& fieldName, T& result)
{
    const auto& attr = xmlNode.attribute(fieldName.c_str());
    if (attr.empty())
    {
        return false;
    }

    std::string strVal;
    try
    {
        strVal = attr.as_string();
    }
    catch(int& e)
    {
        return false;
    }
    std::stringstream ss ( strVal );
    return ReadFromStream(ss, result);
}

///////////////////////////////////////////////////////////////////////////
template<typename T1, typename T2>
bool IBaseComponent::ReadFromStream(std::stringstream& src, std::pair<T1, T2>& result)
{
    std::stringstream pairStream;
    if (false == ExtractContainer(src, pairStream))
    {
        return false;
    }

    T1 t1;
    T2 t2;
    if ((false == ReadFromStream(pairStream, t1)) || (false == ReadFromStream(pairStream, t2)))
    {
        return false;
    }

    result = std::pair<T1, T2>(t1, t2);
    return true;
}

///////////////////////////////////////////////////////////////////////////
template<typename T>
bool IBaseComponent::ReadFromStream(std::stringstream& src, std::vector<T>& result)
{
    result.clear();
    std::stringstream vectorStream;
    if (false == ExtractContainer(src, vectorStream))
    {
        return false;
    }
    try
    {
        T nextVal; // Have a buffer string
        while (ReadFromStream(vectorStream, nextVal))
        {
            result.push_back(nextVal);
        }
    }
    catch(int& e)
    {
        return false;
    }
    return true;
}

///////////////////////////////////////////////////////////////////////////
template<typename KeyT, typename ValT>
bool IBaseComponent::ReadFromStream(std::stringstream& src, std::map<KeyT, ValT>& result)
{
    result.clear();
    std::stringstream mapStream;
    if (false == ExtractContainer(src, mapStream))
    {
        return false;
    }

    try
    {
        std::pair<KeyT, ValT> p;

        while (ReadFromStream(mapStream, p))
        {
            result.insert(p);
        }
    }
    catch(int& e)
    {
        return false;
    }
    return true;
}


#endif // IBASECOMPONENT_BASIC_READERS_HPP
