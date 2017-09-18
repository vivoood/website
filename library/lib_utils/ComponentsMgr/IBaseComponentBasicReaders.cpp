#include "IBaseComponent.h"
#include <sstream>
#include "pugixml.hpp"
#include "../BaseComponents/System/ComponentsFactory.h"
#include "../XmlParsers/XmlTools.h"
#include <algorithm>

using namespace egt;

#define exception int

///////////////////////////////////////////////////////////////////////////
bool IBaseComponent::ReadFromStream(std::stringstream& src, unsigned long long& result)
{
    try
    {
        bool parseResult = (src >> result) ? true : false;
        return parseResult;
    }
    catch(exception& e)
    {
        return false;
    }

    return false;
}

///////////////////////////////////////////////////////////////////////////
bool IBaseComponent::ReadFromStream(std::stringstream& src, signed long long& result)
{
    try
    {
        bool parseResult = (src >> result) ? true : false;
        return parseResult;
    }
    catch(exception& e)
    {
        return false;
    }

    return false;
}

///////////////////////////////////////////////////////////////////////////
bool IBaseComponent::ReadFromStream(std::stringstream& src, unsigned long& result)
{
    try
    {
        bool parseResult = (src >> result) ? true : false;
        return parseResult;
    }
    catch(exception& e)
    {
        return false;
    }

    return false;
}

///////////////////////////////////////////////////////////////////////////
bool IBaseComponent::ReadFromStream(std::stringstream& src, signed long& result)
{
    try
    {
        bool parseResult = (src >> result) ? true : false;
        return parseResult;
    }
    catch(exception& e)
    {
        return false;
    }

    return false;
}

///////////////////////////////////////////////////////////////////////////
bool IBaseComponent::ReadFromStream(std::stringstream& src, unsigned short& result)
{
    unsigned long res;
    bool success = ReadFromStream(src, res);
    result = (unsigned short)res;
    return success;
}

///////////////////////////////////////////////////////////////////////////
bool IBaseComponent::ReadFromStream(std::stringstream& src, signed short& result)
{
    signed long res;
    bool success = ReadFromStream(src, res);
    result = (signed short)res;
    return success;
}

///////////////////////////////////////////////////////////////////////////
bool IBaseComponent::ReadFromStream(std::stringstream& src, unsigned char& result)
{
    unsigned long res;
    bool success = ReadFromStream(src, res);
    result = (unsigned char)res;
    return success;
}

///////////////////////////////////////////////////////////////////////////
bool IBaseComponent::ReadFromStream(std::stringstream& src, signed char& result)
{
    signed long res;
    bool success = ReadFromStream(src, res);
    result = (signed char)res;
    return success;
}

///////////////////////////////////////////////////////////////////////////
bool IBaseComponent::ReadFromStream(std::stringstream& src, unsigned& result)
{
    unsigned long res;
    bool success = ReadFromStream(src, res);
    result = (unsigned)res;
    return success;
}

///////////////////////////////////////////////////////////////////////////
bool IBaseComponent::ReadFromStream(std::stringstream& src, signed& result)
{
    signed long res;
    bool success = ReadFromStream(src, res);
    result = (signed)res;
    return success;
}

///////////////////////////////////////////////////////////////////////////
bool IBaseComponent::ReadFromStream(std::stringstream& src, char& result)
{
    // 'unsigned char' and 'char' are two different C types.
    // 'char' is not guaranteed to have only 8 bits.
    unsigned long res;
    bool success = ReadFromStream(src, res);
    result = (char)res;
    return success;
}

///////////////////////////////////////////////////////////////////////////
bool IBaseComponent::ReadFromStream(std::stringstream& src, float& result)
{
    try
    {
        bool parseResult = (src >> result) ? true : false;
        return parseResult;
    }
    catch(exception& e)
    {
        return false;
    }

    return false;
}

///////////////////////////////////////////////////////////////////////////
bool IBaseComponent::ReadFromStream(std::stringstream& src, double& result)
{
    try
    {
        bool parseResult = (src >> result) ? true : false;
        return parseResult;
    }
    catch(exception& e)
    {
        return false;
    }

    return false;
}

///////////////////////////////////////////////////////////////////////////
bool IBaseComponent::ReadFromStream(std::stringstream& src, std::string& result)
{
    try
    {
        std::string rawString;
        result.clear();
        bool parseResult = (src >> rawString) ? true: false;
        if (false == parseResult)
        {
            return false;
        }
        if(rawString.empty())
        {
            return true;
        }
        if ((rawString.size() >= 2) && (rawString.front() == '^'))
        {
            // Take string between ^xx xx xxss^.
            auto endStrPos = rawString.find("^", 1);
            if (endStrPos == std::string::npos)
            {
                return false;
            }
            result = rawString.substr(1, endStrPos - 1);
            return parseResult;
        }

        for (size_t i = 0; i < rawString.size(); i++)
        {
            // replace "__" with ' '
            if ((i < rawString.size() - 1) && (rawString[i] == '_' && rawString[i+1] == '_'))
            {
                result.push_back(' ');
                i++;
            }
            else
            {
                result.push_back(rawString[i]);
            }
        }
        return parseResult;
    }
    catch(exception& e)
    {
    }

    return false;
}

///////////////////////////////////////////////////////////////////////////
bool IBaseComponent::ReadFromStream(std::stringstream& src, bool& result)
{
    try
    {
        std::string boolStr;
        bool parseResult = (src >> boolStr) ? true: false;
        if (false == parseResult)
        {
            return false;
        }
        std::transform(boolStr.begin(), boolStr.end(), boolStr.begin(), ::tolower);
        if (boolStr == std::string("true"))
        {
            result = true;
            return true;
        }
        else if (boolStr == std::string("false"))
        {
            result = false;
            return true;
        }

        return false;
    }
    catch(exception& e)
    {
        return false;
    }

    return false;
}

bool IBaseComponent::ReadFromStream(std::stringstream& src, UniObject& result)
{
    COMP_MGR_LOG << "Cant deserialize UniObject from stringstream";
    COMP_ASSERT("Cant deserialize UniObject from stringstream");
    return false;
}
