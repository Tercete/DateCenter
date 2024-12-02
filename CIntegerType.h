/***************************************************************************

   cdatatypes.h - Tipos basicos portaveis

****************************************************************************/

#ifndef __CINTEGERTYPE_H  // Impede multiplas inclusoes
#define __CINTEGERTYPE_H

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

#ifdef UNIX
#include <dirent.h>
#endif

//const char _CRLF[]  = "\r\n";   // Carriage Return + Line Feed (New Line)
//const char _LF[]    = "\n";     // Line Feed (New Line)
//const char _CR[]    = "\r";     // Carriage Return

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
class CStr;
class CDateTime;
class CVariant;

/*
class (1)
    public (5)
        virtual (9)
                void (17)
                                Funcao (33)
*/
class __External CInteger {
    public:
        virtual                 ~CInteger();
                                CInteger();
                                CInteger( const int n );
                                CInteger( const CInteger & other );

                CStr            format( const char * formatSpec ) const;
                CStr            getString() const;
                CStr            getHex() const;
                CInteger        GetPercent( int num ) const { return num * m_inValue / 100; }
                bool            isInDomain( int low, int high ) { return ((( m_inValue >= low ) && ( m_inValue <= high )) ? true : false ); }

                int             getInt() const { return m_inValue; }
                                operator int() const { return m_inValue; }
                CInteger &      operator=( int n ) { m_inValue = n; return *this; }
                CInteger &      operator=( const CInteger & other ) { m_inValue = other.m_inValue; return *this; }
                CInteger &      operator+=( const CInteger & n ) { m_inValue += n; return *this; }
                CInteger &      operator-=( const CInteger & n ) { m_inValue -= n; return *this; }
                CInteger        operator++() { return ++m_inValue; }
                CInteger        operator++( int ) { return m_inValue++; }
                CInteger        operator--() { return --m_inValue; }
                CInteger        operator--( int ) { return m_inValue--; }
    protected:
                int             m_inValue;
};

#endif

