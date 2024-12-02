/***************************************************************************

   cdatatypes.h - Tipos basicos portaveis

****************************************************************************/

#ifndef __CVARIANTTYPE_H  // Impede multiplas inclusoes
#define __CVARIANTTYPE_H

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

#ifndef UINT
typedef unsigned int        UINT;
#endif

/***************************************************************************

                          T I P O S    B A S I C O S

****************************************************************************/
class CStr;
class CDateTime;
class CVariant;

////////////////////////////////////////////////////////////////////////////
// CVariant
/*
class (1)
    public (5)
        virtual (9)
                void (17)
                                Funcao (33)
*/
class __External CVariant {
    public:
        enum {
            Type_Null     = 0,
            Type_Bool     = 0x0010,
            Type_Int      = 0x0020,
            Type_Double   = 0x0040,
            Type_Str      = 0x0080,
            Type_DateTime = 0x0100
        };
                                CVariant();
        virtual                 ~CVariant();
                                CVariant( const bool b );
                                CVariant( const int n );
                                CVariant( const double n );
                                CVariant( const char * pc );
                                CVariant( const CStr & s );
                                CVariant( const CDouble & n );
                                CVariant( const CDateTime & dt );
                                CVariant( const CBoolean & b );
                                CVariant( const CVariant & other );

        // informacoes sobre o conteudo
                CInteger        getType() const { return m_inType; }
                bool            isNumericType() const;
                bool            isStr() const { return m_inType == Type_Str ? true : false; }
                void            setType( int );
                void            changeType( int );
                bool            compare( const CVariant & var2 ) const;

        // obtem o valor em tipos diferentes
                bool            getBoolean() const;
                CInteger        getInteger() const;
                CDouble         getDouble() const;
                CStr            getString() const;
                CDateTime       getDateTime() const;
                void*           getAddress(UINT inTipo = Type_Str );

                                operator bool() const { return getBoolean(); }
                                operator int() const { return getInteger(); }
                                operator double() const { return getDouble(); }
                                operator CStr() const { return getString(); }
                                operator CDateTime() const { return getDateTime(); }

        // estabelece o valor em tipos diferentes
        virtual void            setEmpty();
        virtual void            setBoolean( bool );
        virtual void            setInteger( int );
        virtual void            setDouble( double );
        virtual void            setDouble( const CDouble & );
        virtual void            setString( const CStr & );
        virtual void            setString( const int  n );
        virtual void            setDateTime( const CDateTime & );

                CVariant &      operator=( const bool n ) { setBoolean( n ); return *this; }
                CVariant &      operator=( const int n ) { setInteger( n ); return *this; }
                CVariant &      operator=( const double n ) { setDouble( n ); return *this; }
                CVariant &      operator=( const char * pc ) { setString( pc ); return *this; }
                CVariant &      operator=( const CDouble & f ) { setDouble( f ); return *this; }
                CVariant &      operator=( const CStr & pc ) { setString( pc ); return *this; }
                CVariant &      operator=( const CDateTime & dt ) { setDateTime( dt ); return *this; }
                CVariant &      operator=( const CVariant & other ) { copyFrom( other ); return *this; }
                CVariant &      operator=( const CBoolean & n ) { setBoolean( n ); return *this; }
                void            copyFrom( const CVariant & other );

   protected:
                int             m_inType;
                bool            m_boBValue;
                int             m_inIValue;
                double          m_dlFValue;
                CStr            m_szSValue;
                CDateTime       m_dtDValue;
};

#endif

