#include "GenericFunctionBinder.hpp"
#include "AnyStream.hpp"

bool egt::Bindable::IsPaused() const
{
    return m_isPaused;
}

void egt::Bindable::SetPaused(bool paused)
{
    m_isPaused = paused;
}

egt::Bindable::WeakPtr egt::Bindable::GetWeakPtr()
{
    return shared_from_this();
}
