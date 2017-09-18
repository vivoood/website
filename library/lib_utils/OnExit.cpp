#include "OnExit.h"

OnExit::OnExit( std::function<void()> onExit )
    : m_onExit(onExit)
{}

OnExit::~OnExit()
{
    m_onExit();
}
