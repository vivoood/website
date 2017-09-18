#ifndef BINDABLEOBJECT_H
#define BINDABLEOBJECT_H
#include <memory>

class BindableObject
{
public:
    using IsAliveMarker = std::weak_ptr<BindableObject>;
    BindableObject();
    virtual ~BindableObject();
    virtual void OnObjectPause();
    virtual void OnObjectResume();
    virtual IsAliveMarker GetIsAliveMarker() const;
    //
    virtual void PauseObject(uint64_t now);
    virtual void ResumeObject(uint64_t now);
    virtual bool IsPaused() const;
    virtual uint64_t GetLastPauseDuration() const;
    virtual uint64_t GetLastPauseStartTime() const;
protected:
    virtual void InitOwnWeakPointer(std::shared_ptr<BindableObject> sharedPtr);
private:
    bool m_inited;
    bool m_isPaused;
    uint64_t m_lastPauseStart;
    uint64_t m_lastPauseDuration;
    IsAliveMarker m_ownWeakPtr;
};

#endif // BINDABLEOBJECT_H
