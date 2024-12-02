
#ifndef __CLINKED_LIST_H
#define __CLINKED_LIST_H

#if defined( __CLASS_EXPORT )
   #define __External __declspec( dllexport )
#elif defined( __CLASS_IMPORT )
   #define __External __declspec( dllimport )
#else
   #define __External
#endif

template <class T> class Node {
    public:
        T *         m_pElement;
        Node *      m_pPrevious;
        Node *      m_pNext;

        Node() {
            m_pElement = 0;
            m_pPrevious = 0;
            m_pNext= 0;
        }
};

template< class T> class __External CLinkedList
{
    public:
        CLinkedList() {    
            m_pBegin   = 0;
            m_pEnd     = 0;
            m_pPos     = 0;
            m_boSorted = false;
            m_boAutoDelete = false;
            m_inCount  = 0;
        }

        ~CLinkedList() {
            Clear();
        }

        // deleta os items quando são removidos da lista. So' pode ser alterado com a lista vazia.
        void SetAutoDelete( bool value )
        {
            if( m_inCount == 0 ) {
                m_boAutoDelete = value;
            }
        }

        bool GetAutoDelete() const
        {
            return m_boAutoDelete;
        }

        int  GetCount() const
        {
            return m_inCount; 
        }

        bool IsEmpty() const 
        {
            return m_inCount == 0; 
        }

        bool InsertAt( int i, T * element )
        {
            if( i >=0 && i < m_inCount ) {
                Node<T> * node = m_pBegin;

                while( node && i-- ) {
                    node = node->m_pNext;
                }
                if( node ) {
                    Node<T> * newnode = new Node<T>;
                    newnode->m_pElement = element;

                    node->m_pPrevious->m_pNext = newnode;
                    newnode->m_pPrevious = node->m_pPrevious;
                    newnode->m_pNext = node;
                    node->m_pPrevious = newnode;
                    return true;
                } else {
                    Append( element );
                }
            }
            return false;
        }

        bool InsertSort( T * element )
        {
            Append( element );
            Sort();
            return false;
        }

        void Prepend( T * element )
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

        void Append( T * element )
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

        bool Remove( int i )
        {
            return Remove( Get( i ) );
        }

        bool Remove( T * element )
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
                    if( m_pPos == node) {
                        if( node->m_pNext ) {
                            m_pPos = node->m_pNext;
                        } else {
                            m_pPos = node->m_pPrevious;
                        }
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

        bool RemoveFirst()
        {
            if( m_pBegin )
                return Remove( m_pBegin->m_pElement );
            return false;
        }

        bool RemoveLast()
        {
            if( m_pEnd )
                return Remove( m_pEnd->m_pElement );
            return false;
        }

        Node<T> * GetNode(int i )
        {
            if( i >=0 && i < m_inCount ) {
                Node<T> * node = m_pBegin;

                while( node && i-- ) {
                    node = node->m_pNext;
                }
                if( node )
                    return node;
            }
            return 0;
        }

        T * Get( int i )
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

        void Clear()
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

        void Sort()
        {
            int cols [] = { 1391376, 463792, 198768, 86961, 33936, 13776, 9216, 8748, 8192, 7776, 
                            6912, 6561, 6144, 5832, 5184, 4608, 4374, 4096, 3888, 3456, 3072, 2916,
                            2592, 2304, 2187, 2048, 1944, 1728, 1536, 1458, 1296, 1152, 1024, 972,
                            864, 768, 729, 648, 576, 512, 486, 432, 384, 324, 288, 256, 243, 216, 
                            192, 162, 144, 128, 108, 96, 81, 72, 64, 54, 48, 36, 32, 27, 24, 18, 
                            16, 12, 9, 8, 6, 4, 3, 2, 1 };
            Node<T> *   node; // v ;
            T *         pTemp;
            int i, j, k, h;

            for (k = 0; k < (sizeof(cols) / sizeof(int)); k++) {
                h = cols[k];
                for (i = h; i < m_inCount; i++) {
                    node = GetNode(i);
                    pTemp = node->m_pElement;
                    j = i;
                    while (j >= h && (*(GetNode(j - h)->m_pElement) > *(node->m_pElement))) {
                        GetNode(j)->m_pElement = GetNode(j - h)->m_pElement;
                        j -= h;
                    }
                    GetNode(j)->m_pElement = pTemp;
                }
            }
        } 

        T* GetFirst()
        {
            m_pPos = m_pBegin;

            if( m_pPos )
                return m_pPos->m_pElement;
            return 0;
        }

        T* GetLast()
        {
            m_pPos = m_pEnd;

            if( m_pPos )
                return m_pPos->m_pElement;
            return 0;
        }

        T* GetNext()
        {
            if( m_pPos )
                m_pPos = m_pPos->m_pNext;

            if( m_pPos )
                return m_pPos->m_pElement;
            return 0;
        }

        T* GetPrevious()
        {
            if( m_pPos )
                m_pPos = m_pPos->m_pPrevious;

            if( m_pPos )
                return m_pPos->m_pElement;
            return 0;
        }

        T* GetPos()
        {
            if( m_pPos )
                return m_pPos->m_pElement;
            return 0;
        }

    protected:
                Node<T> *       m_pBegin;
                Node<T> *       m_pEnd;
                Node<T> *       m_pPos;
                int             m_inCount;                            
                bool            m_boSorted;
                bool            m_boAutoDelete;
};

#endif // __CLINKED_LIST_H

