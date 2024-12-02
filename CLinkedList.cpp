/*

#include "CLinkedList.h"

CLinkedList::CLinkedList()
{
    m_pBegin   = 0;
    m_pEnd     = 0;
    m_pPos     = 0;
    m_boSorted = false;
    m_boAutoDelete = false;
    m_inCount  = 0;
}

CLinkedList::~CLinkedList() 
{
    Clear();
}

void CLinkedList::SetAutoDelete( bool value )
{
    if( m_inCount == 0 ) {
        m_boAutoDelete = value;
    }
}

bool CLinkedList::GetAutoDelete() const
{
    return m_boAutoDelete;
}

int CLinkedList::GetCount() const
{
    return m_inCount; 
}

bool CLinkedList::IsEmpty()  const 
{ 
    Return m_inCount == 0; 
}

bool CLinkedList::InsertAt( int i, T * element )
{
    // FIXME: Implementar
    return false;
}

bool CLinkedList::InsertSort( T * element )
{
    // FIXME: Implementar
    return false;
}
void CLinkedList::Prepend( T * element )
{
    Node<T> * node = new Node<T>;

    node->m_pElement = element;

    if( !m_pBegin ) { // se nao tem m_pBegin, tambem nao tem m_pEnd...
        m_pBegin = m_pEnd = node;
    }
    else {
        m_pBegin->m_pPrevious = node;
        node->m_pNext = m_pBegin;
        m_pBegin = node;
    }
    m_inCount++;
}

void CLinkedList::Append( T * element )
{
    Node<T> * node = new Node<T>;

    node->m_pElement = element;

    if( !m_pBegin ) {  // se nao tem m_pBegin, tambem nao tem m_pEnd...
        m_pBegin = m_pEnd = node;
    }
    else {
        m_pEnd->m_pNext = node;
        node->m_pPrevious = m_pEnd;
        m_pEnd = node;
    }
    m_inCount++;
}

bool CLinkedList::Remove( int i )
{
    // FIXME: Implementar
    return false;
}

bool CLinkedList::Remove( T * element )
{
    Node<T> * node = m_pBegin;

    while( node ) {
        if( node->m_pElement == element ) {
            if( node->m_pNext ) {
                node->m_pNext->m_pPrevious = node->m_pPrevious;
            }
            if( node == m_pBegin ) {
                m_pBegin = node->m_pNext;
            }
            if( node->m_pPrevious ) {
                node->m_pPrevious->m_pNext = node->m_pNext;
            }
            if( node == m_pEnd ) {
                m_pEnd = node->m_pPrevious;
            }
            if( m_boAutoDelete ) {
                delete node->m_pElement;
            }
            delete node;
            m_inCount--;
            return true;
        }
        node = node->m_pNext;
    }
    return false;
}

bool CLinkedList::RemoveFirst()
{
    if( m_pBegin )
        return Remove( m_pBegin->m_pElement );
    return false;
}

bool CLinkedList::RemoveLast()
{
    if( m_pEnd )
        return Remove( m_pEnd->m_pElement );
    return false;
}

T * CLinkedList::Take( int i )
{
    // FIXME: Implementar
    return 0;
}

T * CLinkedList::Get( int i )
{
    if( i >=0 && i < m_inCount ) {
        Node<T> * node = m_pBegin;

        while( node && i-- ) {
            node = node->m_pNext;
        }
        if( node )
            return node->m_pElement;
    }
    return 0;
}

void CLinkedList::Clear()
{
    Node<T> * node = m_pEnd;

    while( node ) {
        Node<T> * temp = node;
        node = node->m_pPrevious;

        if( m_boAutoDelete ) {
            delete temp->m_pElement;
        }
        delete temp;
    }
    m_pBegin = m_pEnd = m_pPos = 0;
    m_inCount = 0;
}

void CLinkedList::Sort()
{
    //FIXME: Implementar
}

int CLinkedList::Contains( T * element ) const
{
    //FIXME: Implementar
    return 0;
}

T* CLinkedList::GetFirst()
{
    m_pPos = m_pBegin;

    if( m_pPos )
        return m_pPos->m_pElement;
    return 0;
}

T* CLinkedList::GetNext()
{
    if( m_pPos )
        m_pPos = m_pPos->m_pNext;

    if( m_pPos )
        return m_pPos->m_pElement;
    return 0;
}

T* CLinkedList::GetPrevious()
{
    if( m_pPos )
        m_pPos = m_pPos->m_pPrevious;

    if( m_pPos )
        return m_pPos->m_pElement;
    return 0;
}

T* CLinkedList::GetPos()
{
    if( m_pPos )
        return m_pPos->m_pElement;
    return 0;
}

*/