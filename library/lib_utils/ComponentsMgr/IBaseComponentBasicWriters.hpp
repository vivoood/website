#ifndef IBASECOMPONENT_BASIC_WRITERS_HPP
#define IBASECOMPONENT_BASIC_WRITERS_HPP


///////////////////////////////////////////////////////////////////////////
template<typename T1, typename T2>
bool IBaseComponent::WriteToStream(std::stringstream& dst, const std::pair<T1, T2>& value)
{
    dst << "{ ";

    if (WriteToStream(dst, value.first))
    {
        dst << "  ";
    }
    else
    {
        // ASSERT
    }
    if (WriteToStream(dst, value.second))
    {
        dst << " }";
        return true;
    }
    else
    {
        // ASSERT
        return false;
    }
}

///////////////////////////////////////////////////////////////////////////
template<typename T>
bool IBaseComponent::WriteToStream(std::stringstream& dst, const std::vector<T>& value)
{
    try
    {
        dst << "{ ";
        for (const T& v : value)
        {
            if (false == WriteToStream(dst, v))
            {
                // ASSERT
                return false;
            }
            dst << "  ";
        }
        dst << "}";
    }
    catch(int& e)
    {
        // ASSERT
        return false;
    }
    return true;
}

///////////////////////////////////////////////////////////////////////////
template<typename KeyT, typename ValT>
bool IBaseComponent::WriteToStream(std::stringstream& dst, const std::map<KeyT, ValT>& value)
{
    try
    {
        dst << "{ ";
        for (const std::pair<KeyT, ValT>& p : value)
        {
            if (false == WriteToStream(dst, p))
            {
                // ASSERT
                return false;
            }
            dst << "  ";
        }
        dst << "}";
    }
    catch(int& e)
    {
        // ASSERT
        return false;
    }
    return true;
}

#endif // IBASECOMPONENT_BASIC_WRITERS_HPP
