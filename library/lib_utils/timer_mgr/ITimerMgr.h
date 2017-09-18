/*
 * Author: Velislav Velkov
 *
 * Copyright (c) 2016 EGT Ltd.
 * All rights reserved
 *
 * More information at: http://www.egt-bg.com
 */

#ifndef ITIMERMGR_H
#define ITIMERMGR_H

#include "ITimerClient.h"

class ITimerMgr
{
public:
    virtual ~ITimerMgr() {}
    virtual void StartTimer(ITimerClient *pClient, int nID, int delayMillis, int periodMillis, int times = -1) = 0;
    virtual void StartTimer(ITimerClient *pClient, int nID, int periodMillis) = 0;
    virtual bool StopTimer(ITimerClient *pClient, int nID) = 0;
};

#endif // ITIMERMGR_H
