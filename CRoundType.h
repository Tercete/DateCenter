/***************************************************************************

   cdatatypes.h - Tipos basicos portaveis

****************************************************************************/

#ifndef __CROUNDTYPE_H  // Impede multiplas inclusoes
#define __CROUNDTYPE_H

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
   Obs.: nao criar 'operator double()', para exigir conversoes explicitas de round para double
*/
/*
class (1)
    public (5)
        virtual (9)
                void (17)
                                 Funcao (33)
*/
class __External CRound {
    public :
                                CRound( double n, int prec = 2 );
                                CRound( const CRound & other ) { m_dlValue = other.m_dlValue; m_inPrecision = other.m_inPrecision; }
                                CRound() { m_dlValue = 0; m_inPrecision = 2; }
        virtual                 ~CRound();

                CInteger        getPrecision() const { return m_inPrecision; }
                void            setPrecision( int );
                CRound          getAbs() const;
                CStr            format( const char * formatSpec ) const;
                CStr            getString() const;
                CDouble         getDouble() const;
                CRound          round( int precision ) const;
                CRound          ceil ( int precision ) const;
                CRound          floor( int precision ) const;

                CRound          operator+( const CRound & ) const;
                CRound          operator+( double ) const;
                CRound          operator-( const CRound & ) const;
                CRound          operator-( double ) const;
                CRound          operator*( const CRound & ) const;
                CRound          operator*( double ) const;
                CRound          operator/( const CRound & ) const;
                CRound          operator/( double ) const;
                CRound          operator^( const CRound & ) const;
                CRound          operator^( double ) const;
                CRound &        operator = ( const CRound & n ) { m_dlValue = _round( n.m_dlValue, m_inPrecision ); return *this; }
                CRound &        operator = ( double n );
                CRound &        operator += ( const CRound n ) { m_dlValue += _round( n.m_dlValue, m_inPrecision ); return *this; }
                CRound &        operator += ( double );
                CRound &        operator -= ( const CRound n ) { m_dlValue -= _round( n.m_dlValue, m_inPrecision ); return *this; }
                CRound &        operator -= ( double );
                CRound &        operator *= ( const CRound n );
                CRound &        operator *= ( double );
                CRound &        operator /= ( const CRound n );
                CRound &        operator /= ( double );

                CRound          operator++() { m_dlValue++; return *this; }
                CRound          operator++( int ) { CRound ret = *this; m_dlValue++; return ret; }
                CRound          operator--();
                CRound          operator--( int );
                CRound          operator-();

                double          m_dlValue;

    protected:
                int             m_inPrecision;
        static  double          _round( double, int );
};

// Operadores para CRound
__External CRound operator +  ( double,      const CRound & s );
__External CRound operator -  ( double,      const CRound & s );
__External CRound operator *  ( double,      const CRound & s );
__External CRound operator /  ( double,      const CRound & s );
__External CRound operator ^  ( double,      const CRound & s );
__External int    operator == ( const CRound & c,  double d   );
__External int    operator == ( const CRound & c,  const CRound & d );
__External int    operator == ( double c,    const CRound & d );
__External int    operator != ( const CRound & c,  double d   );
__External int    operator != ( const CRound & c,  const CRound & d );
__External int    operator != ( double c,    const CRound & d );
__External int    operator <  ( const CRound & c,  double d   );
__External int    operator <  ( const CRound & c,  const CRound & d );
__External int    operator <= ( const CRound & c,  double d   );
__External int    operator <= ( const CRound & c,  const CRound & d );
__External int    operator >  ( const CRound & c,  double d   );
__External int    operator >  ( const CRound & c,  const CRound & d );
__External int    operator >= ( const CRound & c,  double d   );
__External int    operator >= ( const CRound & c,  const CRound & d );


#endif

