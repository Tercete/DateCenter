/***************************************************************************

   cdatatypes.h - Tipos basicos portaveis

****************************************************************************/

#ifndef __CDATETIMETYPE_H  // Impede multiplas inclusoes
#define __CDATETIMETYPE_H

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

#ifndef uchar
#define uchar       unsigned char
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
   #define __External __declspec( dllimport )
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

CDateTime convertCStrToDateTime( CStr& szData );

/***************************************************************************

                          T I P O S    B A S I C O S

****************************************************************************/
class CStr;
class CVariant;

struct _DateTimeDetail {
    public:
        // deixar tipo basico int por questão de otimizacao
        int m_inDay;
        int m_inMonth;
        int m_inYear;
        int m_inWeekDay;
        int m_inDayOfYear;
        int m_inHour;
        int m_inMin;
        int m_inSec;

        int m_inHDay;
        int m_inHMonth;
        int m_inHYear;
};


/*
class (1)
    public (5)
        virtual (9)
                void (17)
                                Funcao (33)
*/
class __External CDateTime {
    public :
                                CDateTime( const CDateTime & other );
                                CDateTime();
                                CDateTime( const char * Datastr );
                                CDateTime( double );
                                CDateTime( int year, int month, int day, int hour=0, int min=0, int sec=0 );
        virtual                 ~CDateTime();

        static  bool            isValidTime( int nYear, int nMonth, int nDay );
        static  bool            isValidDate( int nYear, int nMonth, int nDay );
                bool            isEmpty() const;
                bool            isHoliday(CStr* pszHoliday = NULL) const;
                bool            isHHoliday(CStr* pszHoliday = NULL);
                CInteger        getDay() const;
                CInteger        getWeekDay() const;
                CInteger        getMonth() const;
        static  CInteger        getDaysInMonth( int month, int year );
                CInteger        getDaysInMonth() const;
                double          getJulianDay() const;
                CInteger        getYear() const;
                CInteger        getCentury() const;
                CInteger        getHour() const;
                CInteger        getMin() const;
                CStr            format( const CStr & format ) const;
                CInteger        getSec() const;
        static  CDateTime       getNow();
                int             getDiff(const CDateTime & dtFinal ) const;
                double          getDiffInSecs( const CDateTime & d ) const;
                CDateTime       addDays( int day ) const;
                CDateTime       addMonths( int months ) const;
                CDateTime       addYears( int years ) const;
                CDateTime       getNextMonth( int desiredDay ) const;
                CDateTime       getPreviousMonth( int desiredDay = 0) const;
                void            setEmpty();
                void            setJulianDay( double j );
                void            setYear( int year );
                void            setMonth( int month );
                void            setDay( int day );

                void            setDate( int year, int month, int day );
                void            setTime( int hour, int min, int sec );
                void            setDateTime( int year, int month, int day, int hour, int min, int sec );

                CDateTime &     operator=( const CDateTime & other );
                CDateTime       operator+( const CDateTime & ) const;
                CDateTime       operator-( const CDateTime & ) const;
                CDateTime&		operator+= (const CInteger days );
                CDateTime&      operator-= (const CInteger days );

                CInteger        getHDay() ;
                CInteger        getHMonth() ;
                CInteger        getHYear() ;
                void            setHYear( int year );
                void            setHMonth( int month );
                void            setHDay( int day );

                CStr            civ2heb(_DateTimeDetail* DtDetail = NULL , bool boConsiderSunset = false);
                CStr            heb2civ(_DateTimeDetail& DtDetail);

                _DateTimeDetail m_DateTimeDetail;

    protected:
        static  const uchar     DaysInMonth[ 12 ];
        static  const char*     MonthNames[ 12 ];
        static  const char*     MonthNamesJ[ 13 ];
        static  const char*     MonthNamesEnglish[ 12 ];
        static  const char*     WeekDayNames[ 7 ];
        static  const char *    WeekDayNamesE[ 7 ] ;
        static  const char *    WeekDayNamesH[ 7 ] ;
                double          m_dlJulianDay;


                int             getRep( const char * & picture, char c ) const;
        static  bool            isLeapYear( int );
                CStr            getMonthName(int month ) const;
                CStr            getWeekDayName() const;

                CStr            getWeekDayNameH();
                CStr            getWeekDayNameH( int weekDay );

        static  CStr            getWeekDayName( int );
                void            getDate( _DateTimeDetail & ) const;
                void            getDateH( _DateTimeDetail & ) ;
                double          _getJulianDay(int year, int month, int day, int hour=0, int min=0, int sec=0) const;
                int             gauss(int iAno = NULL);

};

__External CDateTime convertYYYYMMDDToDateTime( const char * date );
__External CDateTime convertDDMMYYYYToDateTime( const char * date );

// Operadores para CDateTime
__External CDateTime operator +  ( double,             const CDateTime & s );
__External CDateTime operator -  ( double,             const CDateTime & s );
__External int       operator == ( const CDateTime &,  const CDateTime & );
__External int       operator != ( const CDateTime &,  const CDateTime & );
__External int       operator <  ( const CDateTime & c,  double d   );
__External int       operator <  ( const CDateTime & c,  const CDateTime & d );
__External int       operator <= ( const CDateTime & c,  double d   );
__External int       operator <= ( const CDateTime & c,  const CDateTime & d );
__External int       operator >  ( const CDateTime & c,  double d   );
__External int       operator >  ( const CDateTime & c,  const CDateTime & d );
__External int       operator >= ( const CDateTime & c,  double d   );
__External int       operator >= ( const CDateTime & c,  const CDateTime & d );


#endif

