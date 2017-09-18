/* Singleton.h

	Singleton class; singletone

	Author: Atanas Sopotski
	$Id: Singleton.h,v 1.1.2.1 2015/01/07 12:38:15 sopotski Exp $

	Copyright (c) 2012 EGT Ltd.
	All rights reserved

	More information at: http://www.egt-bg.com
*/

#ifndef __SINGLETON_H__
#define __SINGLETON_H__

#include <iostream>

//! The CSingleton class is a template class for creating singleton object s.
/*!
    When the static Instance() method is called for the first time, the singleton 
    object is created. Every sequential call returns a reference to this instance.
    The class instance can be destroyed by calling the DestroyInstance() method.
*/
template <typename T> 
class Singleton
{
public:
    
    //! Gets a reference to the instance of the singleton class.
    /*!
        \return A reference to the instance of the singleton class.
        If there is no instance of the class yet, one will be created.
    */
    static T* InstancePtr()
    {
        if (m_instance == NULL) m_instance = new T;
        
//        Assert(m_instance != NULL);

        return m_instance;
    };
    
    static T & Instance()
    {
        if (m_instance == NULL) m_instance = new T;
        
//        Assert(m_instance != NULL);

        return *m_instance;
    };

    //! Destroys the singleton class instance.
    /*!
        Be aware that all references to the single class instance will be
        invalid after this method has been executed!
    */
    static void DestroyInstance()
    {
        delete m_instance;
        m_instance = NULL;
    };

protected:

    // shield the constructor and destructor to prevent outside sources
    // from creating or destroying a CSingleton instance.

    //! Default constructor.
    Singleton()
    {
    };


    //! Destructor.
    virtual ~Singleton()
    {
    };

private:

    //! Copy constructor.
    Singleton(const Singleton& source)
    {
    };

    static T* m_instance; //!< singleton class instance
};

//! static class member initialisation.
template <typename T> T* Singleton<T>::m_instance = NULL;


#endif // ! defined __SINGLETON_H__