/* PriorityThread.h

        Declares/Defines a high priority thread class

        $Id: PriorityThread.h,v 1.1.2.1 2015/01/07 12:38:09 sopotski Exp $

        Copyright (c) 2004-2011 EGT Ltd. 
        All rights reserved

        More information at: http://www.egt-bg.com
*/

#ifndef _PRIORITYTHREAD_H_
#define _PRIORITYTHREAD_H_

#include "SimpleThread.h"
#include <egt_lib/debug/egt_debug.h>

class PriorityThread : public SimpleThread {

    pthread_attr_t m_attr;

 public:
    PriorityThread (int queue = SCHED_RR, int priority = 1)
        : SimpleThread(NULL)
    {

        if(pthread_attr_init(&m_attr) != 0) {
            eCDebug(LOG_CATEGORY_LIBS) << "PriorityThread: pthread_attr_init FAILED!!!";
        }

        if(pthread_attr_setschedpolicy(&m_attr, queue) != 0) {
            eCDebug(LOG_CATEGORY_LIBS) << "PriorityThread: pthread_attr_setschedpolicy FAILED!!!";
        }

        struct sched_param sp;
        sp.sched_priority = priority;
        if(pthread_attr_setschedparam(&m_attr, &sp) != 0) {
            eCDebug(LOG_CATEGORY_LIBS) << "PriorityThread: pthread_attr_setschedparam FAILED!!!";
        }

        if(pthread_attr_setinheritsched(&m_attr, PTHREAD_EXPLICIT_SCHED) != 0) {
            eCDebug(LOG_CATEGORY_LIBS) << "PriorityThread: pthread_attr_setinheritsched FAILED!!!";
        }

        if(pthread_create(&m_thread, &m_attr, m_func, this) != 0) {

            eCDebug(LOG_CATEGORY_LIBS) << "PriorityThread: pthread_create FAILED!!! You probably are not root, trying to create a regular priority thread instead";

            if(pthread_create(&m_thread, NULL, m_func, this) != 0) {
                eCDebug(LOG_CATEGORY_LIBS) << "PriorityThread: regular priority pthread_create FAILED!!!";
            }
        }
    }

    ~PriorityThread() {
        pthread_attr_destroy(&m_attr);
    }
};

#endif /* _PRIORITYTHREAD_H_ */
