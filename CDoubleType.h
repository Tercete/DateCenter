/***************************************************************************

   cdatatypes.h - Tipos basicos portaveis

****************************************************************************/

#ifndef __CDOUBLETYPE_H  // Impede multiplas inclusoes
#define __CDOUBLETYPE_H

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
class CInteger;
class CDateTime;
class CVariant;

/***************************************************************************

                          C D O U B L E

****************************************************************************/
/*
class (1)
    public (5)
        virtual (9)
                void (17)
                                Funcao (33)
*/
class __External CDouble {
    public:
                                CDouble();
                                CDouble( const double n );
                                CDouble( const CDouble & other );
        virtual                 ~CDouble();

                CDouble         getAbs() const;
                CStr            format( const char * formatSpec ) const;
                CStr            getString() const;
                CStr            getExtent( const char * language ) const;
                CDouble         round( int precision ) const;
                CDouble         ceil ( int precision ) const;
                CDouble         floor( int precision ) const;
                bool            isInDomain( double low, double high ) { return ((( m_dlValue >= low ) && ( m_dlValue <= high )) ? true : false ); }
                    
                                operator double() const { return m_dlValue; }
                CDouble &       operator=( double n ) { m_dlValue = n; return *this; }
                CDouble &       operator=( const CDouble & other ) { m_dlValue = other.m_dlValue; return *this; }
                CDouble &       operator+=( const CDouble & n ) { m_dlValue += n.m_dlValue; return *this; }
                CDouble &       operator-=( const CDouble & n ) { m_dlValue -= n.m_dlValue; return *this; }
                CDouble &       operator*=( const CDouble & n ) { m_dlValue *= n.m_dlValue; return *this; }

                double          m_dlValue;

    protected:
                CStr            getExtent1To999( double value, const CStr& lang ) const;
};

// Operadores para CDouble
__External int     operator == ( const CDouble &,  const CDouble &  );
__External int     operator == ( const CDouble &,  const double     );
__External int     operator == ( const double,     const CDouble &  );
__External int     operator != ( const CDouble &,  const CDouble &  );
__External int     operator != ( const CDouble &,  const double     );
__External int     operator != ( const double,     const CDouble &  );
__External CDouble operator ^  ( const CDouble &,  const CDouble &  );
__External CDouble operator ^  ( const CDouble &,  const CInteger & );


#endif

