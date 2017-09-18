/* DeadlineThread.h

        Declares/Defines a dead line thread class
        (not very pretty, but pthread does not support dead line thread
        at the point of this implementation)

        Copyright (c) 2004-2011 EGT Ltd.
        All rights reserved

        More information at: http://www.egt-bg.com
*/

#ifndef _DEADLINETHREAD_H_
#define _DEADLINETHREAD_H_

#include "SimpleThread.h"

#include <egt_lib/debug/egt_debug.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <linux/unistd.h>
#include <linux/kernel.h>
#include <linux/types.h>
#include <sys/syscall.h>
#include <linux/sched.h>

namespace egt
{
    struct deadline_type
    {
        void operator()()
        {
            sched_attr attr;
            attr.size = sizeof(attr);
            attr.sched_flags = 0;
            attr.sched_nice = 0;
            attr.sched_priority = 0;

            /* This creates a (runtime micro seconds)/(period micro seconds) reservation */
            attr.sched_policy = SCHED_DEADLINE;
            attr.sched_runtime = runtime * 1000;
            attr.sched_period = attr.sched_deadline = period * 1000;

            auto ret = sched_setattr(0, &attr, 0);
            if (ret < 0) {
                eCDebug(LOG_CATEGORY_LIBS) << "sched_setattr FAILED!!! for " << std::this_thread::get_id();
            }
        }
    private:
        static constexpr uint64_t runtime = 200;
        static constexpr uint64_t period = 500;

        struct sched_attr {
            __u32 size;

            __u32 sched_policy;
            __u64 sched_flags;

            /* SCHED_NORMAL, SCHED_BATCH */
            __s32 sched_nice;

            /* SCHED_FIFO, SCHED_RR */
            __u32 sched_priority;

            /* SCHED_DEADLINE (nsec) */
            __u64 sched_runtime;
            __u64 sched_deadline;
            __u64 sched_period;
        };

        long sched_setattr(pid_t pid,
                          const struct sched_attr *attr,
                          unsigned int flags)
        {
            return syscall(__NR_sched_setattr, pid, attr, flags);
        }

        long sched_getattr(pid_t pid,
                          struct sched_attr *attr,
                          unsigned int size,
                          unsigned int flags)
        {
            return syscall(__NR_sched_getattr, pid, attr, size, flags);
        }
    };

    using deadline_thread = thread<deadline_type>;
}

#endif /* _DEADLINETHREAD_H_ */
