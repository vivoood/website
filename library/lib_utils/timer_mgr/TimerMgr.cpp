/*
 * Author: Velislav Velkov
 *
 * Copyright (c) 2016 EGT Ltd.
 * All rights reserved
 *
 * More information at: http://www.egt-bg.com
 */

#include "TimerMgr.h"

#include <egt_lib/debug/egt_debug.h>
#include <SDL2/SDL.h>
#include <time.h>
#include <typeinfo>

int TimerMgr::Init()
{
    m_nClientsCount = 0;
    m_nClientsToRemoveCount = 0;
    return 0;
}

void TimerMgr::StartTimer ( ITimerClient *pClient, int nID, int delayMillis, int periodMillis, int times/* = -1*/ )
{
    if ( m_nClientsCount >= MAX_TIMER_CLIENTS )
    {
        CleanUpClients();

        if ( m_nClientsCount >= MAX_TIMER_CLIENTS )
        {
            SetTimerMgrError ( TimerMgr::eTimerOutOfRange );
            return;
        }
    }

    if ( 0 == pClient || delayMillis < 0 ||periodMillis <= 0 )
    {
        SetTimerMgrError ( TimerMgr::eInvalidArguments );
        return;
    }

    /*****************************************************************/
    for ( int i=0; i<m_nClientsCount; i++ )
        if ( false == IsInRemoveList ( i ) &&
                m_aClientsInfo[i].pClient == pClient &&
                m_aClientsInfo[i].nTimerID == nID )
        {
            SetTimerMgrError ( TimerMgr::TimerMgr::eDuplicateTimer );
            return;
        }
    /*****************************************************************/

    m_aClientsInfo[m_nClientsCount].pClient = pClient;
    m_aClientsInfo[m_nClientsCount].nTimerID = nID;
    m_aClientsInfo[m_nClientsCount].nTickType = TT_ONCE_TIMER_MGR;
    m_aClientsInfo[m_nClientsCount].nPeriodMillis = periodMillis;

    m_aClientsInfo[m_nClientsCount].nLastTickTime = SDL_GetTicks() + delayMillis - periodMillis;
    m_aClientsInfo[m_nClientsCount].nMaxTimes = times;
    m_aClientsInfo[m_nClientsCount].nTimes = 0;

    m_nClientsCount++;
}

void TimerMgr::StartTimer ( ITimerClient *pClient, int nID, int peroidMillis )
{
    StartTimer ( pClient, nID, peroidMillis, peroidMillis );
}

bool TimerMgr::CheckIfTimerOn ( ITimerClient *pClient, int nID )
{
    for ( int i = 0; i < m_nClientsCount; ++i )
    {
        if ( ( m_aClientsInfo[i].pClient ==  pClient ) &&
                ( m_aClientsInfo[i].nTimerID ==  nID ) &&
                false == IsInRemoveList ( i ) )
        {
            return true;
        }
    }

    return false;
}

#ifdef REAL_TIMER

void TimerMgr::StartRealTimer ( ITimerClient *pClient, int nID, int delayMillis, int periodMillis, int times/* = -1*/ )
{
    Assert ( m_nClientsCount < MAX_TIMER_CLIENTS );
    Assert ( 0 != pClient );
    Assert ( delayMillis >= 0 );
    Assert ( periodMillis > 0 );
    Assert ( -1 == times || times > 0 );

    /*****************************************************************/

#ifdef EGT_DEBUG
    /*DbgPrintf("\n[ TimerMgr ] StartRealTimer(): Client = 0x%08X, ID = %d, Delay = %d, Period = %d, Times = %d\n",
    	pClient, nID, delayMillis, periodMillis, times);*/

    for ( int i=0; i<m_nClientsCount; i++ )
        if ( false == IsInRemoveList ( i ) &&
                m_aClientsInfo[i].pClient == pClient &&
                m_aClientsInfo[i].nTimerID == nID )
        {
            Assert ( false );
        }
#endif //EGT_DEBUG
    /*****************************************************************/

    m_aClientsInfo[m_nClientsCount].pClient = pClient;
    m_aClientsInfo[m_nClientsCount].nTimerID = nID;
    m_aClientsInfo[m_nClientsCount].nTickType = TT_REAL;
    m_aClientsInfo[m_nClientsCount].nPeriodMillis = periodMillis;

    m_aClientsInfo[m_nClientsCount].nLastTickTime = SDL_GetTicks() + delayMillis - periodMillis;
    m_aClientsInfo[m_nClientsCount].nMaxTimes = times;
    m_aClientsInfo[m_nClientsCount].nTimes = 0;

    m_nClientsCount++;
}


void TimerMgr::StartRealTimer ( ITimerClient *pClient, int nID, int peroidMillis )
{
    StartRealTimer ( pClient, nID, peroidMillis, peroidMillis );
}

#endif // REAL_TIMER

bool TimerMgr::StopTimer ( ITimerClient *pClient, int nID )
{
    for ( int i=0; i< m_nClientsCount; i++ )
        if ( m_aClientsInfo[i].pClient == pClient &&
                m_aClientsInfo[i].nTimerID == nID &&
                false == IsInRemoveList ( i ) )
        {
            m_anClientsToRemoveIndices[m_nClientsToRemoveCount++] = i;
            return true;
        }

    return false;
}

bool TimerMgr::IsInRemoveList ( int indexClient ) const
{
    for ( int i=0; i<m_nClientsToRemoveCount; i++ )
        if ( m_anClientsToRemoveIndices[i] == indexClient )
            return true;

    return false;
}

void TimerMgr::SortRemoveList()
{
    for ( int i=0; i<m_nClientsToRemoveCount - 1; i++ )
        for ( int j=i+1; j<m_nClientsToRemoveCount; j++ )
            if ( m_anClientsToRemoveIndices[i] > m_anClientsToRemoveIndices[j] )
            {
                int temp = m_anClientsToRemoveIndices[i];
                m_anClientsToRemoveIndices[i] = m_anClientsToRemoveIndices[j];
                m_anClientsToRemoveIndices[j] = temp;
            }
}

void TimerMgr::CleanUpClients()
{
    SortRemoveList();

    int posToWriteInClients = 0;
    int posIndices = 0;

    for ( int posToReadInClients = 0; posToReadInClients < m_nClientsCount; posToReadInClients ++ )
    {
        if ( posIndices < m_nClientsToRemoveCount &&
                m_anClientsToRemoveIndices[posIndices] == posToReadInClients )
        {
            posIndices ++;
        }
        else
        {
            if ( posToWriteInClients != posToReadInClients )
                m_aClientsInfo[posToWriteInClients] = m_aClientsInfo[posToReadInClients];

            posToWriteInClients ++;
        }
    }

    m_nClientsCount -= m_nClientsToRemoveCount;
    m_nClientsToRemoveCount = 0;
}

#include <chrono>

void TimerMgr::TimerProcess()
{
    CleanUpClients();

    unsigned int nCurrMillis = SDL_GetTicks();

    int i = 0;

    // if machine wasn't turned off for more than 49 days reset the last tick of every client.
    // We relay on fact that we don't have timers with more than 49 days "nPeriodMillis".
    // In practice we dont have clients with more than a second "nPeriodMillis"
    for ( ; i < m_nClientsCount; i++ )
    {
        if ( nCurrMillis < m_aClientsInfo[i].nLastTickTime )
        {
            if ( ( m_aClientsInfo[i].nLastTickTime - nCurrMillis ) > 2000000000 )
            {
                m_aClientsInfo[i].nLastTickTime = nCurrMillis;
            }
        }
        else
        {
            if ( ( nCurrMillis - m_aClientsInfo[i].nLastTickTime ) > 2000000000 )
            {
                m_aClientsInfo[i].nLastTickTime = nCurrMillis;
            }
        }
    }
    ////////////////////////////////////////////////////////////////////////////////

    for ( i = 0; i < m_nClientsCount; i++ )
    {
        if ( nCurrMillis < m_aClientsInfo[i].nLastTickTime )
        {
            m_aClientsInfo[i].nLastTickTime= nCurrMillis;
            continue;
        }

        if ( !IsInRemoveList ( i ) &&
                nCurrMillis - m_aClientsInfo[i].nLastTickTime >= ( unsigned ) m_aClientsInfo[i].nPeriodMillis )
        {
            
#ifdef EGT_DEBUG
            auto timer_start = std::chrono::system_clock::now();
#endif
            switch ( m_aClientsInfo[i].nTickType )
            {
            case TT_ONCE_TIMER_MGR:
            {
                m_aClientsInfo[i].nLastTickTime = nCurrMillis;
                m_aClientsInfo[i].nTimes ++;

                m_aClientsInfo[i].pClient->OnTick ( m_aClientsInfo[i].nTimerID, m_aClientsInfo[i].nTimes );

                if ( -1 != m_aClientsInfo[i].nMaxTimes &&
                        m_aClientsInfo[i].nTimes == m_aClientsInfo[i].nMaxTimes )
                    StopTimer ( m_aClientsInfo[i].pClient, m_aClientsInfo[i].nTimerID );
            }
            break;

            case TT_REAL_TIMER_MGR:
            {
                int tickTimes = ( nCurrMillis - m_aClientsInfo[i].nLastTickTime ) / m_aClientsInfo[i].nPeriodMillis;

                for ( int j=0; j<tickTimes; j++ )
                {
                    m_aClientsInfo[i].nLastTickTime += m_aClientsInfo[i].nPeriodMillis;
                    m_aClientsInfo[i].nTimes ++;

                    m_aClientsInfo[i].pClient->OnTick ( m_aClientsInfo[i].nTimerID, m_aClientsInfo[i].nTimes );

                    if ( -1 != m_aClientsInfo[i].nMaxTimes && m_aClientsInfo[i].nTimes == m_aClientsInfo[i].nMaxTimes )
                    {
                        StopTimer ( m_aClientsInfo[i].pClient, m_aClientsInfo[i].nTimerID );
                        break;
                    }

                    if ( IsInRemoveList ( i ) )
                        break;
                }
            }
            break;

            default:
                Assert ( false );
                break;
            }
            
#ifdef EGT_DEBUG
            auto timer_stop = std::chrono::system_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(timer_stop - timer_start);
            if (duration.count() > 1000)
                eCDebug(LOG_CATEGORY_TIMER_MGR_INFO) << "TI: " << typeid( *(m_aClientsInfo[i].pClient) ).name() << " TID=" << m_aClientsInfo[i].nTimerID <<  " OnTickDelay=" << duration.count() << " us.";
#endif
        }
    }

    CleanUpClients();
}

unsigned int TimerMgr::tgt()
{
    return SDL_GetTicks();
}

unsigned int TimerMgr::GetCurrentTime()
{
    return time ( NULL );
}

void TimerMgr::Synchronize ( int nDifference )
{
    int i = 0;
    for ( ; i < m_nClientsCount; i++ )
    {
        m_aClientsInfo[i].nLastTickTime += nDifference;
    }
}