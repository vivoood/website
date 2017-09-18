/* SimpleMutex.h

        Declares/Defines a simple mutex class

        Copyright (c) 2004-2014 EGT Ltd. 
        All rights reserved

        More information at: http://www.egt-bg.com
*/

#ifndef _SIMPLEMUTEX_H_
#define _SIMPLEMUTEX_H_

#include <unistd.h>
#include <pthread.h>
#include <egt_lib/debug/egt_debug.h>

/** Simple mutex class */
class SimpleMutex
{
  
public:

	/** Constructor */
	SimpleMutex() {

		int res = pthread_mutex_init(&m_mutex, NULL);
		if (0 != res) { 
			eCDebug( LOG_CATEGORY_EGT_LIB ) << "ERROR: pthread_mutex_init failed!!!";
		}
	}

	/** Virtual destructor */
	virtual ~SimpleMutex() {

		int res = pthread_mutex_destroy(&m_mutex);
		if (0 != res) {
			eCDebug( LOG_CATEGORY_EGT_LIB ) << "ERROR: pthread_mutex_destroy failed!!!";
		}
	}

	/** Lock mutex */
	bool Lock() {

		int res = pthread_mutex_lock(&m_mutex);
		if (0 != res) { 
			eCDebug( LOG_CATEGORY_EGT_LIB ) << "ERROR: pthread_mutex_lock failed!!!";
		}

		return (0 == res);
	}

	/** Unlock mutex */
	bool Unlock() {

		int res = pthread_mutex_unlock(&m_mutex);
		if (0 != res) {
			eCDebug( LOG_CATEGORY_EGT_LIB ) << "ERROR: pthread_mutex_unlock failed!!!";
		}

		return (0 == res);
	}

	/** Auto mutex in block context */
	class Auto {

	public:

		Auto(SimpleMutex& mutex) : m_mutex(mutex) { m_mutex.Lock(); }

		~Auto() { m_mutex.Unlock(); }

	private:

		Auto() : m_mutex(*(new SimpleMutex)) { }

		SimpleMutex& m_mutex;
	};

private:
  
	pthread_mutex_t m_mutex; // posix mutex
};

#endif /* _SIMPLEMUTEX_H_ */
