/*
 * Author: Velislav Velkov
 *
 * Copyright (c) 2016 EGT Ltd.
 * All rights reserved
 *
 * More information at: http://www.egt-bg.com
 */

#ifndef ITIMERCLIENT_H
#define ITIMERCLIENT_H

class ITimerClient
{
public:
    virtual ~ITimerClient() {}
    virtual void OnTick ( int nID, int times ) = 0;
};

typedef struct tagTimerClientInfo
{
	tagTimerClientInfo() :
		pClient(nullptr),
		nTimerID(),
		nTickType(),
		nPeriodMillis(),
		nLastTickTime(),
		nTimes(),
		nMaxTimes()	{ }

    ITimerClient	*pClient;
    int nTimerID;
    int nTickType;
    int nPeriodMillis;
    unsigned int nLastTickTime;
    int nTimes;
    int nMaxTimes;
} STimerClientInfo;

#endif // ITIMERCLIENT_H
