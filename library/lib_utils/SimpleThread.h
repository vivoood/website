/* SimpleThread.h

        Declares/Defines a simple thread class

        $Id: SimpleThread.h,v 1.1.2.1 2015/01/07 12:38:09 sopotski Exp $

        Copyright (c) 2004-2011 EGT Ltd.
        All rights reserved

        More information at: http://www.egt-bg.com
*/

#ifndef _SIMPLETHREAD_H_
#define _SIMPLETHREAD_H_

#include <atomic>
#include <thread>

namespace egt
{
    struct default_type
    {
        void operator()(){ }
    };

    template<typename type = default_type>
    class thread
    {
    public:
        virtual ~thread()
        {
            request_to_quit();
            if (thread_.joinable())
            {
                thread_.join();
            }
        }

        /** Check if thread is finished */
        bool is_finished() const { return finished_; }

        /** Check if thread is run */
        bool is_run() const { return req_to_run_; }

        /** Check if the current and this threads are the same*/
        bool is_same() const {  return std::this_thread::get_id() == thread_.get_id(); }

        /** Request to quit from thread loop */
        void request_to_quit() { req_to_quit_ = true; }

        /** Request to run thread loop */
        void request_to_run(bool req_to_run = true) { req_to_run_ = req_to_run; }

        /** Thread entry point */
        virtual void run() = 0;

        /** Default sleep interval */
        virtual void sleep() { std::this_thread::sleep_for(std::chrono::microseconds(100)); }

    protected:
        thread(std::string name = "egt::thread")
            : thread_([this]{ type{}(); thread_func(); })
        {
            pthread_setname_np(thread_.native_handle(), name.c_str());
        }
    private:

        /** Thread loop */
        void thread_func()
        {
            while (!req_to_quit_)
            {
                if (req_to_run_)
                {
                    run();
                    sleep();
                }
                else
                {
                    std::this_thread::sleep_for(std::chrono::microseconds(100));
                }
            }
            finished_ = true;
        }

        std::atomic_bool req_to_run_ {false};
        std::atomic_bool req_to_quit_ {false};
        std::atomic_bool finished_ {false};

        std::thread thread_;
    };

    using default_thread = thread<default_type>;
}

#endif /* _SIMPLETHREAD_H_ */
