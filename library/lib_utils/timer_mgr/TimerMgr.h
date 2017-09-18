/*
 * Author: Velislav Velkov
 *
 * Copyright (c) 2016 EGT Ltd.
 * All rights reserved
 *
 * More information at: http://www.egt-bg.com
 */

#ifndef TIMERMGR_H
#define TIMERMGR_H

#include "ITimerClient.h"

class TimerMgr
{

public:

    /** Enumerate errors */
    enum ETimerErrors
    {
        eNoError,
        eTimerOutOfRange,
        eInvalidArguments,
        eDuplicateTimer,
        eAutoCountErrors
    };

    /** Max number of clients */
    static const int MAX_TIMER_CLIENTS = 200;

    /**  */
    static const int TT_ONCE_TIMER_MGR = 1;

    /**  */
    static const int TT_REAL_TIMER_MGR = 2;

    /** Constructor */
    TimerMgr() : m_aClientsInfo(), m_nClientsCount(), m_anClientsToRemoveIndices(), m_nClientsToRemoveCount() {}

    /** Destructor */
    virtual ~TimerMgr() {}

    /** Initialize */
    int Init();

    /**  */
    void Deinit() {}

    /** StartTimer - start timer
     * @param pClient - pointer to timer client
     * @param nID - current timer id
     * @param delayMillis -
     * @param periodMillis -
     * @param times -
     */
    void StartTimer ( ITimerClient *pClient, int nID, int delayMillis, int periodMillis, int times = -1 );

    /** Start a timer with the given parameters - the firs tick will be after periodMillis
     * @param pClient - pointer to timer client
     * @param nID - current timer id
     * @param periodMillis -
     */
    void StartTimer ( ITimerClient *pClient, int nID, int periodMillis );

    /** CheckIfTimerOn -
     * @param pClient - pointer to timer client
     * @param nID - current timer id
     * @return true if timer with id is started
     */
    bool CheckIfTimerOn ( ITimerClient *pClient, int nID );

    /** CleanUpClients - */
    void CleanUpClients();

#ifdef REAL_TIMER
    void StartRealTimer ( ITimerClient *pClient, int nID, int delayMillis, int periodMillis, int times = -1 );
    void StartRealTimer ( ITimerClient *pClient, int nID, int periodMillis );
#endif //REAL_TIMER	

    /** StopTimer - stop timer with id
     * @param pClient - pointer to timer client
     * @param nID - current timer id
     * @return success
     */
    bool StopTimer ( ITimerClient *pClient, int nID );

    /** Process -  */
    void TimerProcess();

    /** tgt -
     * @return time in miliseconds since the last system reboot
     */
    unsigned int tgt();

    /** GetCurrentTime -
     * @return the time since the Epoch (00:00:00 UTC, January 1, 1970), measured in seconds
     */
    unsigned int GetCurrentTime();

    /** Synchronizing all current timers after change of the system time; nDifferne is in ms
     * @param nDifference
     */
    void Synchronize ( int nDifference );

    /** SetError - 
     * @param eTimerErrors - error id
     */
    virtual void SetTimerMgrError( ETimerErrors eTimerErrors ) {}

private:

    /** Array with timer clients */
    STimerClientInfo m_aClientsInfo[MAX_TIMER_CLIENTS];

    /** Current timer clients count */
    int m_nClientsCount;

    /** Array with timer clients indices to remove it */
    int m_anClientsToRemoveIndices[MAX_TIMER_CLIENTS];

    /** Current timer clients indices count to remove it */
    int m_nClientsToRemoveCount;

    /** IsInRemoveList - check is in remove list current timer id
     * @param indexClient - check index of current removed timer
     * @return success
     */
    bool IsInRemoveList ( int indexClient ) const;

    /** SortRemoveList - */
    void SortRemoveList();
};

#endif // TIMERMGR_H
