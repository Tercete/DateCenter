/***************************************************************************

   cdatatypes.h - Tipos basicos portaveis

****************************************************************************/

#ifndef __CSTRTYPE_H  // Impede multiplas inclusoes
#define __CSTRTYPE_H

#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <ctype.h>
#include <stdio.h>
#ifdef _WIN32
  #include <fcntl.h>
  #include <errno.h>
#endif

#include <CDatatypes.h>

#ifdef UNIX
#include <dirent.h>
#endif

typedef struct tagStringTableErrorTable {
    int Code;
    const char * Description;
} CStrTable;

/***************************************************************************

                          D E F I N I C O E S

****************************************************************************/
#if defined( __CLASS_EXPORT )
   #define __External __declspec( dllexport )
#elif defined( __CLASS_IMPORT )
   #define __External __declspec( dllexport )
#else
   #define __External
#endif

#ifdef __BORLAND_C
enum bool {
    false = 0,
    true  = !false
};
#endif

#ifdef WIN32
   #define cint64 __int64
#else
   #define cint64 long long
#endif

#include <string.h>
#include <stdio.h>

#define MAX_INT 2147483647

#ifndef TRUE
#define TRUE    true
#endif

#ifndef FALSE
#define FALSE   false
#endif

#ifndef MIN 
#define MIN( value1, value2 ) (( value1 < value2 ) ? value1 : value2)
#endif

#ifndef MAX
#define MAX( value1, value2 ) (( value1 > value2 ) ? value1 : value2)
#endif


/***************************************************************************

                          T I P O S    B A S I C O S

****************************************************************************/
//class CStr;
//class CDouble;
//class CVariant;
////class CInteger;
//class CBoolean;
//class CDateTime;


/*
class (1)
    public (5)
        virtual (9)
                void (17)
                                 Funcao (33)
*/
class __External CStr {
    public:
        // Inicialização

                            CStr( const char * pc );
                            CStr( const char * pc, int size );
                            CStr( const unsigned char * pc );
                            CStr( const CStr & s ) { m_pStrRef = s.m_pStrRef; if( m_pStrRef ) m_pStrRef->m_inConnections++; }
                            CStr() { m_pStrRef = 0; }

        virtual             ~CStr(){ destroyStrRef(); }

        // Obtenção de sequencia da CStr

        CStr                getLeft( int size ) const;
        CStr                getMid( int begin, int size = MAX_INT ) const;
        CStr                getRight( int size ) const;
        CStr                leftTrim() const;
        CStr                rightTrim() const;
        CStr                trim() const;
        CStr                remove( int len, int offset, int times = MAX_INT );
        CStr                remove( const char * text, int offset, int times = MAX_INT );
        CStr                replace( const char * find, const char * replace, int times = MAX_INT ) const;
        CStr                format( const char * format, ... );
        char                operator[]( int index ) const;

        // procura

        int                 compare( const char * ) const;
        CInteger            find( const char * other, int offset = 0, bool ignoreCase = false ) const;
        CInteger            findFromBack( const char * other, int offset = 0, bool ignoreCase = false ) const;
        bool                startsWith( const char * prefix, int offset = 0, bool ignoreCase = false ) const;
        bool                endsWith( const char * suffix, bool ignoreCase = false ) const;

        // informação
        bool                isInDomain( const char * domain, const char * elemSeparator = "," ) const;
        bool                isNumber() const;
        bool                isAlpha() const;
        bool                isEmpty() const;
        bool                isHex() const;
        bool                isEqual( const char * other, bool ignoreCase ) const;
        CInteger            getLen() const { if( m_pStrRef ) return m_pStrRef->m_inSize; return 0; }
        CInteger            getHashCode() const;

        // conversão

        CInteger            getHexToInt() const;
        CBoolean            getBoolean() const;
        CDateTime           getDateTime() const;
        CStr                getFirstUpperCase() const;
        CDouble             getDouble() const;
        CInteger            getInteger() const;
        CStr                getLowerCase() const;
        CStr                getUpperCase() const;
        CStr                getHTML() const;
        CStr                removeHTML() const;
        CStr                getParam( const char * paramName ) const;

                            operator char*() const { if( m_pStrRef && m_pStrRef->m_szValue ) return (char*) m_pStrRef->m_szValue; return NULL; }

        // preenchimento / concatenação / escrita

        void                clear();
        void                fill( char c, int size );
        CStr                concat( const char * other );
        CStr                replaceField( const char * field, const char * newValue, bool convertHTML = true ) const;
        void                set( const CStr & s );
        void                truncate( int Pos );
        CStr                operator+( const CStr & s ) const;
        CStr                operator+( const char * ) const;
        CStr &              operator=( const unsigned char * pc ) { set((char*) pc ); return *this; }
        CStr &              operator=( const char * pc ) { set( pc ); return *this; }
        CStr &              operator=( const CStr & other ) {  set( other ); return *this; }
        CStr &              operator+=( char );
        CStr &              operator+=( const char * pc);
        CStr &              operator+=( const CStr & other );
        char &              operator[]( int index );
    protected:
        class _StrRef {
            public:
                char*       m_szValue;
                int         m_inSize;
                unsigned    int m_inConnections;

                            _StrRef( const char *, unsigned int );
                            _StrRef( unsigned int size );
                            ~_StrRef();
        };
        _StrRef *           m_pStrRef;

        void                destroyStrRef();
        void                createStrRef( const char * ref, unsigned int );
        void                createStrRef( const CStr & other );
        void                createStrRef( unsigned int );
        void                copyStrRef();
};

// Operadores para CStr
__External CStr operator +  ( const char *,       const CStr & s     );
__External CStr operator +  ( const char *,       const CInteger & s );
__External int  operator == ( const CStr &,       const CStr & s     );
__External int  operator == ( const char *,       const CStr & s     );
__External int  operator == ( const CStr & s,     const char *       );
__External int  operator != ( const CStr &,       const CStr & s     );
__External int  operator != ( const char *,       const CStr & s     );
__External int  operator != ( const CStr &,       const char *       );


#endif

