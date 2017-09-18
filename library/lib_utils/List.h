/*
Copyright (c) 2012 EGT Ltd.
All rights reserved

More information at: http://www.egt-bg.com
*/

#ifndef LIST_H
#define LIST_H

#include <vector>

using namespace std;

template <class T> class List
{

public:

    /** Empty constructor */
    List();
  
    /** Constructor */
    List( unsigned int nMaxElement );

    /** Destructor */
    virtual ~List() {}

    /**
     * Add element to cycle list
     * @param nElement - template for the element
     */
    void push_back( T nElement );

    /**
     * Insert element to cycle list but dont move head and size
     * @param position - the positions where we insert
     * @param nElement - template for the element
     */
    void insert (int position, T nElement );

    /**
     * Get element from current id
     * @param nId the id of the element
     * @return pointer to the template element
     */
    T * at( int nId );

     /**
     * Get element from current id
     * @param nId the id of the element
     * @return pointer to the template element
     */
    T * atList( int nId );
    
    
    /**
     * Get size of list
     * @return size
     */
    unsigned int size() const {
        return m_nSize;
    }

    /** Clear list */
    void clear();

    /**
     * Return last element
     * @return poiner to the template element
     */
    T * back() {
        return & m_List[ (m_nHead + m_nSize) % MAX_ELEMENTS ];
    }

    /**
     * Get last id
     * @return the id
     */
    int GetLastId() {
        return (m_nHead + m_nSize) % MAX_ELEMENTS;
    }

    /** Index of first element */
    int m_nHead;

    /** Size of list */
    unsigned int m_nSize;

    T& operator[](size_t idx);
    const T& operator[](size_t idx) const;
    const vector<T>& GetBuffer() const { return m_List; }
    void GetLastIdxAndValue(size_t& idx, T& value) const;
    void SetBuffer(const vector<T>& buff, size_t maxBufferSize);
    void pop_front();

private:

    /** Maxmimal elements per list */
    unsigned int MAX_ELEMENTS;

    /** Elements of list */
    vector<T> m_List;

};

template<class T>
void List < T >::GetLastIdxAndValue(size_t& idx, T& value) const
{
    idx = (m_nHead + m_nSize) % MAX_ELEMENTS;
    value = m_List[ idx ];
}

template<class T>
void List < T >::SetBuffer(const vector<T>& buff, size_t maxBufferSize)
{
    MAX_ELEMENTS = maxBufferSize;
    m_List = buff;
    if (m_List.size() != MAX_ELEMENTS)
    {
        m_List.resize(MAX_ELEMENTS);
    }
}

template<class T>
void List < T >::pop_front()
{
    if (m_nSize == 0)
    {
        return;
    }
    m_nHead++;
    m_nHead = m_nHead % MAX_ELEMENTS;
    m_nSize--;
}

template<class T>
T& List < T >::operator[](size_t idx)
{
    return m_List[ (m_nHead + idx + 1) % MAX_ELEMENTS ];
}

template<class T>
const T& List < T >::operator[](size_t idx) const
{
    return m_List[ (m_nHead + idx + 1) % MAX_ELEMENTS ];
}

template <class T> List < T >::List() : MAX_ELEMENTS( 0 )
{
    for ( unsigned int i = 0; i < MAX_ELEMENTS; i++ )
    {
        m_List.push_back( T() );
    }
    clear();
}

template <class T> List < T >::List( unsigned int nMaxElement ) : MAX_ELEMENTS( nMaxElement )
{

    for( unsigned int i = 0; i < MAX_ELEMENTS; i++ )
    {
	m_List.push_back( T() );
    }
    
    clear();
}

template <class T> void List < T >::push_back(T nElement)
{
    if ( m_nSize < MAX_ELEMENTS )
    {
        m_nSize++;
    }
    else
    {
        m_nHead = (m_nHead + 1) % MAX_ELEMENTS;
    }

    m_List[ (m_nHead + m_nSize) % MAX_ELEMENTS ] = nElement;
}

template <class T> void List < T >::insert ( int position, T nElement )
{
    m_List[ position ] = nElement;
}

template <class T> T * List < T >::at( int nId )
{
    return & m_List[ (m_nHead + nId + 1) % MAX_ELEMENTS ];
}

template <class T> T * List < T >::atList( int nId )
{
    return & m_List[nId % MAX_ELEMENTS ];
}


template <class T> void List < T >::clear()
{
    m_nSize = 0;
    m_nHead = -1;

    for ( unsigned int i = 0; i < MAX_ELEMENTS; i++ )
    {
        m_List[i] = T();
    }
}

#endif // LIST_H
