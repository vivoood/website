#ifndef INTTOSTR_H
#define INTTOSTR_H
#include <string>
#include <egt_lib/utils/Currency.h>

namespace egt
{
class IntToStr;
class StringFormatResult
{
public:
    StringFormatResult();

    const std::string& GetString() const;
    const std::string& GetStringBeforeNumber() const;
    const std::string& GetStringAfterNumber() const;
    std::string GetOnlyConvertedNumber() const;

    CurrencyType       GetType() const;

    bool               HasDecimalDigits;
    bool               HasThousandSeperator;
    bool               IsCurrencyCodeInsteadName;
    bool               HasCurrencyCode;
    bool               HideDecimalIfZero;
    bool               HideDecimalIfWholeNumber;
    bool               ShowDecimalIfWholePartIsZero;
    unsigned           ZerosAfterDot;
    bool               Superscript;

    CurrencyType       Type;
    std::string        Value;
    std::string        DecimalPoint;
    std::string        CurrencyCodeSeparator;
    std::string        Postfix;
    std::string        Prefix;
    std::string        DecimalDigits;
    std::string        WholeDigits;
    std::string        OnlyFormattedNumber;
    std::string        CurrencyCode;
    bool               IsNegative;

    std::string        StringBeforeNumber;
    std::string        StringAfterNumber;
    std::string        PreparedWholePart;
    std::string        ThousandsSeparator;
private:
    friend class       IntToStr;
};

class IntToStr
{
public:

    IntToStr();

    enum class UnitsCodePosition
    {
        NONE,
        FRONT,
        BACK,
    };

    StringFormatResult GetFormatResult() const;
    void SetFixedPointNumber(signed long long number, long fixedPoint);
    //
    std::string         decimalPoint;
    bool                showDecimalNumbers;
    bool                hideDecimalIfZero;
    bool                hideDecimalIfWholeNumber;
    bool                showDecimalIfWholePartIsZero;
    unsigned            zerosAfterDot;
    bool                superscript;
    std::string         unitsCode;
    std::string         unitsName;
    UnitsCodePosition   unitsCodePosition;
    std::string         unitsCodeSeparator;
    std::string         postfix;
    std::string         prefix;
    unsigned            groupingSize; // if 3 => 3 456 233 234; if 2 => 34 56 23 32 34; if 0 => 3456233234
    std::string         groupsSeparator;
private:
    std::string         PrepareWholePart(StringFormatResult& formatterResult) const;
    std::string         PrepareDecimalPart(StringFormatResult& formatterResult) const;
    void                PrepareCurrencyCode(std::string& result, StringFormatResult& formatterResult) const;

    std::string         m_wholePart;
    std::string         m_decimalPart;
    signed long long    m_wholePartNumber;
    signed long long    m_decimalPartNumber;
    signed long long    m_rawNumber;
    long                m_fixedPoint;
    unsigned            m_decimalDigitsCount;
};

}

#endif // INTTOSTR_H
