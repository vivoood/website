#include "BindableObject.h"
#include "BinderLogger.h"
#define BO_LOG (egt::BinderLogger().Get())
#define BO_ASSERT(msg) throw msg

///////////////////////////////////////////////////////////////////////////
BindableObject::BindableObject()
    : m_inited(false)
    , m_isPaused(false)
    , m_lastPauseStart(0ull)
    , m_lastPauseDuration(0ull)
{}

///////////////////////////////////////////////////////////////////////////
BindableObject::~BindableObject(){}

///////////////////////////////////////////////////////////////////////////
void BindableObject::OnObjectPause(){}

///////////////////////////////////////////////////////////////////////////
void BindableObject::OnObjectResume(){}

///////////////////////////////////////////////////////////////////////////
std::weak_ptr<BindableObject> BindableObject::GetIsAliveMarker() const
{
    std::weak_ptr<BindableObject> result;
    if (false == m_inited)
    {
        BO_LOG << "Trying to get marker from dead or not inited instance. ";
        BO_ASSERT("Trying to get marker from dead or not inited instance. ");

        result = std::shared_ptr<BindableObject>(nullptr);
    }
    else
    {
        auto ptr = m_ownWeakPtr.lock();
        result = ptr;
    }
    return result;
}

///////////////////////////////////////////////////////////////////////////
void BindableObject::InitOwnWeakPointer(std::shared_ptr<BindableObject> sharedPtr)
{

    if (sharedPtr.get() != this)
    {
        m_inited = false;
        BO_LOG << "Trying to init own weak pointer with different instance. ";
        BO_ASSERT("Trying to init own weak pointer with different instance. ");
        return;
    }
    m_inited = true;
    m_ownWeakPtr = sharedPtr;
}

///////////////////////////////////////////////////////////////////////////
void BindableObject::PauseObject(uint64_t now)
{
    if (false == m_isPaused)
    {
        m_lastPauseStart = now;
    }
    m_isPaused = true;
    OnObjectPause();
}

///////////////////////////////////////////////////////////////////////////
void BindableObject::ResumeObject(uint64_t now)
{
    if (true == m_isPaused)
    {
        m_lastPauseDuration = now - m_lastPauseStart;
    }
    m_isPaused = false;
    OnObjectResume();
}

///////////////////////////////////////////////////////////////////////////
bool BindableObject::IsPaused() const
{
    return m_isPaused;
}

///////////////////////////////////////////////////////////////////////////
uint64_t BindableObject::GetLastPauseDuration() const
{
    return m_lastPauseDuration;
}

///////////////////////////////////////////////////////////////////////////
uint64_t BindableObject::GetLastPauseStartTime() const
{
    return m_lastPauseStart;
}
