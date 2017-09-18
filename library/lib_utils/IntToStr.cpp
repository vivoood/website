#include "IntToStr.h"

using namespace egt;

///////////////////////////////////////////////////////
IntToStr::IntToStr()
    :   decimalPoint(".")
    ,   showDecimalNumbers(false)
    ,   hideDecimalIfZero(false)
    ,   hideDecimalIfWholeNumber(false)
    ,   showDecimalIfWholePartIsZero(false)
    ,   zerosAfterDot(2)
    ,   superscript(false)
    ,   unitsCode("")
    ,   unitsName("")
    ,   unitsCodePosition(UnitsCodePosition::NONE)
    ,   unitsCodeSeparator("")
    ,   postfix("")
    ,   prefix("")
    ,   groupingSize(0)
    ,   groupsSeparator(" ")
    ,   m_wholePart("0")
    ,   m_decimalPart("0")
    ,   m_wholePartNumber(0ll)
    ,   m_decimalPartNumber(0ll)
    ,   m_rawNumber(0ll)
    ,   m_fixedPoint(0ll)
    ,   m_decimalDigitsCount(0ll)

{}

void IntToStr::SetFixedPointNumber(signed long long number, long fixedPoint)
{
    signed long long absNumber = std::abs(number);
    bool isNegative = (number < 0);
    m_wholePartNumber = absNumber / fixedPoint;
    m_decimalPartNumber = std::abs(absNumber % fixedPoint);
    m_fixedPoint = fixedPoint;
    m_wholePart = (isNegative) ? "-" : "";
    m_wholePart += std::to_string(m_wholePartNumber);
    m_decimalPart = std::to_string(m_decimalPartNumber);
    m_rawNumber = number;
    m_decimalDigitsCount = 0;
    while( (fixedPoint /= 10) >= 1 ) m_decimalDigitsCount++; // calculate log10(dixedPoint) will give us the count of decimal digits
}

///////////////////////////////////////////////////////

StringFormatResult IntToStr::GetFormatResult() const
{
    StringFormatResult formatterResult;

    std::string strResult;
    strResult += PrepareWholePart(formatterResult);
    strResult += PrepareDecimalPart(formatterResult);
    formatterResult.OnlyFormattedNumber = strResult;

    PrepareCurrencyCode(strResult, formatterResult);
    formatterResult.Prefix = prefix;
    formatterResult.Postfix = postfix;
    formatterResult.StringBeforeNumber = prefix + formatterResult.StringBeforeNumber;
    formatterResult.StringAfterNumber = formatterResult.StringAfterNumber + postfix;
    formatterResult.Value = prefix + strResult + postfix;
    formatterResult.HideDecimalIfZero = hideDecimalIfZero;
    formatterResult.HideDecimalIfWholeNumber = hideDecimalIfWholeNumber;
    formatterResult.ShowDecimalIfWholePartIsZero = showDecimalIfWholePartIsZero;
    formatterResult.ZerosAfterDot = zerosAfterDot;

    return formatterResult;
}

///////////////////////////////////////////////////////
std::string IntToStr::PrepareWholePart(StringFormatResult& formatterResult) const
{
    formatterResult.WholeDigits = m_wholePart;
    formatterResult.ThousandsSeparator = groupsSeparator;
    formatterResult.HasThousandSeperator = (groupingSize == 3);
    formatterResult.IsNegative = false;

    if (m_wholePart.empty())
    {
        return m_wholePart;
    }
    std::string result = m_wholePart;

    // Apply grouping feauture
    if (groupingSize > 0)
    {
        std::string groupedString = "";
        if (result.front() == '-') // handle negatives
        {
            formatterResult.IsNegative = true;
            result = result.substr(1);
        }
        unsigned groupI = (groupingSize - (result.size() % groupingSize)) % groupingSize;
        for (size_t i = 0; i < result.size(); i++)
        {
            if (groupI == groupingSize)
            {
                groupedString += groupsSeparator;
                groupI = 1;
            }
            else
            {
                groupI++;
            }
            groupedString.push_back(result[i]);
        }

        if (formatterResult.IsNegative)
        {
            result = '-' + groupedString;
        }
        else
        {
            result = groupedString;
        }
    }

    formatterResult.PreparedWholePart = result;
    return result;
}

///////////////////////////////////////////////////////
std::string IntToStr::PrepareDecimalPart(StringFormatResult& formatterResult) const
{
    bool bIgnoreDecimalRule = false;
    if ( 0 == m_wholePartNumber && true == showDecimalIfWholePartIsZero )
    {
        bIgnoreDecimalRule = true;//overwrite decimal rule and show point value
    }

    if( false == bIgnoreDecimalRule && false == showDecimalNumbers )
    {
        return {};
    }

    if( true == hideDecimalIfZero && m_rawNumber == 0  )
    {
        return {};
    }

    if( true == hideDecimalIfWholeNumber && m_decimalPartNumber == 0  )
    {
        return {};
    }

    std::string decDigits = m_decimalPart.substr(0, m_decimalDigitsCount);
    size_t diff = m_decimalDigitsCount - decDigits.size();
    decDigits.insert(decDigits.begin(), diff, '0');

    while ((decDigits.size() > zerosAfterDot) && (decDigits.back() == '0' ))
    {
        // if we have more than 2 digits we want to clear zeroes
        decDigits.pop_back();
    }

    std::string result = decimalPoint + decDigits;

    formatterResult.DecimalDigits = decDigits;
    formatterResult.HasDecimalDigits = true;
    formatterResult.DecimalPoint = decimalPoint;
    formatterResult.Superscript = superscript;

    return result;
}

///////////////////////////////////////////////////////
void IntToStr::PrepareCurrencyCode(std::string& result, StringFormatResult& formatterResult) const
{
    if (UnitsCodePosition::BACK == unitsCodePosition)
    {
        result += unitsCodeSeparator + unitsName;
        formatterResult.HasCurrencyCode = true;
        formatterResult.IsCurrencyCodeInsteadName = false;
        formatterResult.CurrencyCodeSeparator = unitsCodeSeparator;
        formatterResult.CurrencyCode = unitsName;
        formatterResult.StringAfterNumber = unitsCodeSeparator + unitsName;
    }
    else if (UnitsCodePosition::FRONT == unitsCodePosition)
    {
        result = unitsCode + unitsCodeSeparator + result;
        formatterResult.HasCurrencyCode = true;
        formatterResult.IsCurrencyCodeInsteadName = true;
        formatterResult.CurrencyCodeSeparator = unitsCodeSeparator;
        formatterResult.CurrencyCode = unitsCode;
        formatterResult.StringBeforeNumber = unitsCode + unitsCodeSeparator;
    }
    else
    {
        formatterResult.HasCurrencyCode = false;
    }
}



///////////////////////////////////////////////////////
///////////////////////////////////////////////////////
///////////////////////////////////////////////////////

StringFormatResult::StringFormatResult()
    : HasDecimalDigits(false)
    , HasThousandSeperator(false)
    , IsCurrencyCodeInsteadName(false)
    , HasCurrencyCode(false)
    , HideDecimalIfZero(true)
    , HideDecimalIfWholeNumber(true)
    , ShowDecimalIfWholePartIsZero(false)
    , ZerosAfterDot(2)
    , Superscript(false)
    , Type(CurrencyType::MONEY)
    , Value("")
    , DecimalPoint("")
    , CurrencyCodeSeparator("")
    , Postfix("")
    , Prefix("")
    , DecimalDigits("")
    , WholeDigits("")
    , CurrencyCode("")
    , IsNegative(false)
    , ThousandsSeparator("")
{}


const std::string& StringFormatResult::GetStringBeforeNumber() const
{
    return StringBeforeNumber;
}

const std::string& StringFormatResult::GetStringAfterNumber() const
{
    return StringAfterNumber;
}

const std::string& StringFormatResult::GetString() const
{
    return Value;
}

std::string StringFormatResult::GetOnlyConvertedNumber() const
{
    return OnlyFormattedNumber;
}

CurrencyType StringFormatResult::GetType() const
{
    return Type;
}

