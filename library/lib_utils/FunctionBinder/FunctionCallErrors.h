#ifndef FUNCTIONCALLERRORS_H
#define FUNCTIONCALLERRORS_H


namespace egt{

enum class FunctionCallError
{
    NoError,
    Unknown
};

template<typename T>
struct FunctionCallResult
{
    FunctionCallResult() = default;
    FunctionCallResult(FunctionCallError error) : m_error(error) {}
    FunctionCallResult(FunctionCallError error, T&& value) : m_error(error), m_value(std::move(value)) {}
    FunctionCallResult(FunctionCallError error, const T& value) : m_error(error), m_value(value) {}

    FunctionCallError GetError() const { return m_error; }
    const T& GetValue() const  { return m_value; }
private:
    FunctionCallError m_error = FunctionCallError::Unknown;
    T m_value = T();
};

template<>
struct FunctionCallResult<void>
{
    FunctionCallResult() = default;
    FunctionCallResult(FunctionCallError error) : m_error(error) {}

    FunctionCallError GetError() const { return m_error; }
    void GetValue() const;
private:
    FunctionCallError m_error = FunctionCallError::Unknown;
};
}
#endif // FUNCTIONCALLERRORS_H
