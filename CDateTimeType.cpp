
#include "CDatatypes.h"
#include <QDebug>
/*------------------------------------------------
Function    : -
Author      : FLM
Date        : dd/mm/aaaa
Visibility  : Exported / Internal
Arguments   : name (type) - Description
Return      : type & description
Description : -
Portability : WULOMINCQ (Win/Unix/Linux/Os2/Mac os/Ingenico(MONOS)/Nurit(Lipman)/winCe 2.0|3.0/Qt)
Remarks     : -
History     : -
------------------------------------------------*/

#ifdef _WIN32
#include <Windows.h>
#endif


/////////////////////////////////////////////////////////////////////////////
// CDateTime
//
const unsigned char CDateTime::DaysInMonth[ 12 ] =
{ 31,28,31,30,31,30,31,31,30,31,30,31 };

const char * CDateTime::MonthNames[ 12 ] =
{ "Janeiro","Fevereiro","Março","Abril","Maio","Junho","Julho",
  "Agosto", "Setembro", "Outubro", "Novembro", "Dezembro" };

const char * CDateTime::MonthNamesEnglish[ 12 ] =
{ "January","February","March","April","May","June","July",
  "August", "September", "October", "November", "December" };

const char * CDateTime::MonthNamesJ[ 13 ] =
{ "Nisan", "Iyyar", "Sivan", "Tammuz", "Av", "Elul",
  "Tishrei", "Cheshvan", "Kislev", "Tevet", "Shevat",
  "Adar", "Adar II"};

const char * CDateTime::WeekDayNames[ 7 ] =
{ "Domingo", "Segunda-feira","Terça-feira","Quarta-feira","Quinta-feira",
  "Sexta-feira","Sábado" };

const char * CDateTime::WeekDayNamesE[ 7 ] =
{ "Sunday", "Monday","Tuesday","Wednesday","Thursday",
  "Friday","Saturday" };

const char * CDateTime::WeekDayNamesH[ 7 ] =
{ "Yom Rishon", "Yom Sheni","Yom Shlishi","Yom Revii","Yom Chamishi",
  "Yom Shishi","Yom Shabbat" };


CDateTime::CDateTime( int year, int month, int day, int hour, int min, int sec )
{
    m_dlJulianDay = 0;
    setDateTime( year, month, day, hour, min, sec );

    getDate( m_DateTimeDetail );
}

CDateTime::CDateTime( double j )
{
    m_dlJulianDay = j;

    getDate( m_DateTimeDetail );
}

CDateTime::CDateTime( const CDateTime & other )
{
    m_dlJulianDay = other.m_dlJulianDay;
    getDate( m_DateTimeDetail );
}

CDateTime::CDateTime()
{
    m_dlJulianDay = 0;
    getDate( m_DateTimeDetail );
}

CDateTime CDateTime::operator-( const CDateTime & cur ) const
{
    return CDateTime( m_dlJulianDay - cur.m_dlJulianDay );
}

CDateTime& CDateTime::operator+= (const CInteger days )
{
    m_dlJulianDay += static_cast<double>(days);
    getDate( m_DateTimeDetail );

    return *this;
}

CDateTime& CDateTime::operator-= (const CInteger days )
{
    m_dlJulianDay -= static_cast<double>(days);
    getDate( m_DateTimeDetail );

    return *this;
}


CDateTime::CDateTime(const char* Datastr)
{
    m_dlJulianDay = convertDDMMYYYYToDateTime(Datastr).getJulianDay();

    getDate( m_DateTimeDetail );
}

CDateTime::~CDateTime()
{
}

CDateTime CDateTime::getNow()
{
    _DateTimeDetail p_DateTimeDetail;

#ifdef _WIN32

    SYSTEMTIME      SystemTime;

    GetLocalTime( &SystemTime );

    p_DateTimeDetail.m_inHYear = SystemTime.wYear;
    p_DateTimeDetail.m_inMonth = SystemTime.wMonth;
    p_DateTimeDetail.m_inDay   = SystemTime.wDay;
    p_DateTimeDetail.m_inHour  = SystemTime.wHour;
    p_DateTimeDetail.m_inMin   = SystemTime.wMinute;
    p_DateTimeDetail.m_inSec   = SystemTime.wSecond;
#else
    struct tm* SystemTime ;
    time_t    ttAgora = time(0);

    SystemTime = localtime(&ttAgora);
    p_DateTimeDetail.m_inHYear = SystemTime->tm_year + 1900;
    p_DateTimeDetail.m_inMonth = SystemTime->tm_mon;
    p_DateTimeDetail.m_inDay   = SystemTime->tm_mday;
    p_DateTimeDetail.m_inHour  = SystemTime->tm_hour;
    p_DateTimeDetail.m_inMin   = SystemTime->tm_min;
    p_DateTimeDetail.m_inSec   = SystemTime->tm_sec;

#endif

    //return CDateTime( SystemTime.wYear, SystemTime.wMonth, SystemTime.wDay, SystemTime.wHour, SystemTime.wMinute, SystemTime.wSecond );
    return CDateTime( p_DateTimeDetail.m_inHYear, p_DateTimeDetail.m_inMonth, p_DateTimeDetail.m_inDay, p_DateTimeDetail.m_inHour, p_DateTimeDetail.m_inMin, p_DateTimeDetail.m_inSec);
}

/********************************************************************
 Proposito  : Calcula a diferenca entre duas datas (em dias)
 Parametros : Data final
 Retorno    : Numero de dias entre o objeto e a data final fornecida
********************************************************************/
int CDateTime::getDiff( const CDateTime & dtFinal ) const
{
    return int(m_dlJulianDay - dtFinal.m_dlJulianDay);
}


/********************************************************************
 Proposito  : Calcula a diferenca entre duas datas (em segundos)
 Parametros : Data final
 Retorno    : Numero de segundos entre o objeto e a data final fornecida
********************************************************************/
double CDateTime::getDiffInSecs( const CDateTime & d ) const
{
    double x;

    x = (getJulianDay() - d.getJulianDay());
    x *= (x < 0 ? -1 : 1);

    return ((24.0 * 3600.0)) * x;
    //return ((1.0 / (24.0 * 3600.0)) * ((getJulianDay() - d.getJulianDay())));
}



/* Formatação de data e/ou hora

    \       Caracter de escape para exibir um literal
    d       Dia do mês como número sem um zero à esquerda (1-31)
    dd      Dia do mês como número com zero à esquerda (01-31)
    ddd     Dia da semana como abreviação (Dom-Sab)
    dddd    Dia da semana como nome completo (Domingo-Sábado)
    o       Dia (Yom) do mês (Data) Hebraica (1-31)
    oo      Dia (Yom) do mês (Data) Hebraica (01-31)
    ooo     Dia (Yom) da semana ((Hebraico)
    w       Dia da semana como um número (1 para Domingo e 7 para Sábado)
    ww      Semana do ano como um número (1-54)
    m       Mês como número sem um zero à esquerda (1-12)
    mm      Mês como número com zero à esquerda (01-31)
    mmm     Mês em portugûes como uma abreviação (Jan-Dez)
    mmmm    Mês em português como nome completo (Janeiro-Dezembro)
    c       Mês (Chodesh) Hebraico (1-13)
    cc      Mês (Chodesh) Hebraico (01-13)
    ccc     Mês (Chodesh) Hebraico como nome (Nisan-Adar II)
    eee     Mês em inglês como uma abreviação (Jan-Dec)
    eeee    Mês em inglês como nome completo (January-December)
    *q      Trimestre do ano como um número (1-4)
    y       Dia do ano como número (1-366)
    yy      Ano como um número de dois dígitos (00-99)
    yyyy    Ano como um número de quatro dígitos( 100-9999)
    aa      Ano (Shaná) Hebraico (00-99)
    aaaa    Ano (Shaná) Hebraico ( 100-9999)
    h       Hora como um número sem zeros à esquerda (0-23 ou 0-12)
    hh      Hora como um número com zeros à esquerda (00-23 ou 00-12)
    n       Minuto como um número sem zeros à esquerda (0-59)
    nn      Minuto como um número com zeros à esquerda (00-59)
    s       Segundos como um número sem zeros à esquerda (0-59)
    ss      Segundos como um número com zeros à esquerda (00-59)
    *tt     modifica a hora de 24 para 12 horas e acrescenta pm ou am
    *TT     modifica a hora de 24 para 12 horas e acrescenta PM ou AM

    * falta implementação
*/
CStr CDateTime::format( const CStr & format ) const
{
    CStr            s;
    const char *    picture = format;
    _DateTimeDetail dt;

    getDate( dt );

    while( *picture != '\0' ) {
        if( *picture == '\\' ) {                        // seq. de escape
            picture++;
            s += *picture;

            if( *picture != '\0' )
                picture++;
        }
        else if( *picture == 'd' ) {                    // ** Dia **
            switch( getRep( picture, 'd' )) {
                case 1 :
                    s += CInteger( dt.m_inDay ).format("");
                    break;
                case 2 :
                    s += CInteger( dt.m_inDay ).format( "02" );
                    break;
                case 3 :
                    s += getWeekDayName( dt.m_inWeekDay ).getLeft( 3 );
                    break;
                case 4 :
                    s += getWeekDayName( dt.m_inWeekDay );
                    break;
            }
        }
        else if( *picture == 'm' )  {                      // *** Mes ***
            switch( getRep( picture, 'm' )) {
                case 1 :
                    s += CInteger( dt.m_inMonth ).format( "" );
                    break;
                case 2 :
                    s += CInteger( dt.m_inMonth ).format( "02" );
                    break;
                case 3 :
                    s += getMonthName( dt.m_inMonth ).getLeft( 3 );
                    break;
                case 4 :
                    s += getMonthName( dt.m_inMonth );
                    break;
            }
        }
        else if( *picture == 'e' )  {                      // *** Mes ***
            switch( getRep( picture, 'e' )) {
                case 1 :
                    s += CInteger( dt.m_inMonth ).format( "" );
                    break;
                case 2 :
                    s += CInteger( dt.m_inMonth ).format( "02" );
                    break;
                case 3 :
                    s += CStr( MonthNamesEnglish[ dt.m_inMonth - 1 ]).getLeft( 3 );
                    break;
                case 4 :
                    s += MonthNamesEnglish[ dt.m_inMonth - 1 ];
                    break;
            }
        }
        else if( *picture == 'y' ) {                       // *** Ano ***
            switch( getRep( picture, 'y' )) {
                case 1 :
                    s += CInteger( dt.m_inDayOfYear ).format( "" );
                    break;
                case 2 :
                    s += CInteger( dt.m_inYear % 100 ).format( "02" );
                    break;
                case 4 :
                    s += CInteger( dt.m_inYear ).format( "04" );
                    break;
            }
        }
        else if( *picture == 'h' ) {                       // *** Hora ***
            switch( getRep( picture, 'h' )) {
                case 1 :
                    s += CInteger( dt.m_inHour ).format( "" );
                    break;
                case 2 :
                    s += CInteger( dt.m_inHour ).format( "02" );
                    break;
            }
        }
        else if( *picture == 'n' ) {                       // *** Minuto ***
            switch( getRep( picture, 'n' )) {
                case 1 :
                    s += CInteger( dt.m_inMin ).format( "" );
                    break;
                case 2 :
                    s += CInteger( dt.m_inMin ).format( "02" );
                    break;
            }
        }
        else if( *picture == 's' ) {                       // *** Segundo ***
            switch( getRep( picture, 's' )) {
                case 1 :
                    s += CInteger( dt.m_inSec ).format( "" );
                    break;
                case 2 :
                    s += CInteger( dt.m_inSec ).format( "02" );
                    break;
            }
        }
//        else if( *picture == 'o' )  {                      // *** Dia Hebraico ***
//            civ2heb(&dt);
//            switch( getRep( picture, 'o' )) {
//                case 1 :
//                    s += CInteger( dt.m_inHDay ).format( "" );
//                    break;
//                case 2 :
//                    s += CInteger( dt.m_inHDay ).format( "02" );
//                    break;
//                case 3 :
//                    s += getWeekDayName( dt.m_inWeekDay );
//                    break;
//            }
//        }
//        else if( *picture == 'c' )  {                      // *** Mes Hebraico ***
//            civ2heb(&dt);
//            switch( getRep( picture, 'c' )) {
//                case 1 :
//                    s += CInteger( dt.m_inHMonth ).format( "" );
//                    break;
//                case 2 :
//                    s += CInteger( dt.m_inHMonth ).format( "02" );
//                    break;
//                case 3 :
//                    s += getMonthNameH( dt.m_inMonth );
//                    break;
//            }
//        }
//        else if( *picture == 'a' )  {                      // *** Ano Hebraico ***
//            civ2heb(&dt);
//            switch( getRep( picture, 'a' )) {
//                case 1 :
//                    s += CInteger( dt.m_inHYear ).format( "" );
//                    break;
//               case 2 :
//                    s += CInteger( dt.m_inHYear % 100 ).format( "02" );
//                    break;
//                case 4 :
//                    s += CInteger( dt.m_inHYear ).format( "04" );
//                    break;
//            }
//        }
        else if( *picture == 'w' ) {
            switch( getRep( picture, 'w' )) {               // *** Dia da Semana ***
                case 1 :
                    s += CInteger( dt.m_inWeekDay ).format( "" );
                    break;
                case 2 :                                    // *** No. da Semana ***
                    {
                        int inIncremento, inDias;
                        inDias = getDiff( CDateTime(getYear(), 1, 1)) + 1;
                        inIncremento = ((inDias % 7) == 0 ? 0 : 1);
                        s += CInteger( ((inDias / 7) + inIncremento) ).format( "02" );
                    }
                    break;
            }
        }
        else
            s += *picture++;                                    // Separador
    }
    return s;
}


//
// Convert a Julian day number to its corresponding Gregorian calendar
// date.  Algorithm 199 from Communications of the ACM, Volume 6, No. 8,
// (Aug. 1963), p. 444.  Gregorian calendar started on Sep. 14, 1752.
// This function not valid before that.
//
void CDateTime::getDate( _DateTimeDetail & date ) const
{
    memset( &date, 0, sizeof( _DateTimeDetail ));

    unsigned long dwDay;
    unsigned long dwJul = (unsigned long) floor( m_dlJulianDay );

    if( dwJul > 0 ) {
        dwJul -= 1721119L;

        date.m_inYear = (int) ((( dwJul << 2 ) - 1 ) / 146097L );
        dwJul = ( dwJul << 2 ) - 1 - 146097L * date.m_inYear;
        dwDay = ( dwJul >> 2 );
        dwJul = (( dwDay << 2 ) + 3 ) / 1461;
        dwDay = ( dwDay << 2 ) + 3 - 1461 * dwJul;
        dwDay = ( dwDay + 4 ) >> 2;
        date.m_inMonth = (int)( 5 * dwDay - 3 ) / 153;
        dwDay = 5 * dwDay - 3 - 153 * date.m_inMonth;
        date.m_inDay  = (int)(( dwDay + 5 ) / 5 );
        date.m_inYear = (int)( 100 * date.m_inYear + dwJul );

        if( date.m_inMonth < 10 )
            date.m_inMonth += 3;
        else {
            date.m_inMonth -= 9;
            date.m_inYear++;
        }
        date.m_inWeekDay   = (int)((((((unsigned long)floor( m_dlJulianDay ) + 1 ) % 7 ) + 6 ) % 7 ) + 2 );

        // coloca domingo como primeiro dia da semana
        if( date.m_inWeekDay == 8 )
            date.m_inWeekDay = 1;

        date.m_inDayOfYear = (int)( m_dlJulianDay - _getJulianDay( date.m_inYear - 1, 12, 31 ));
    }
    double fsecsInDay = ( m_dlJulianDay - floor( m_dlJulianDay )) * 86400.;
    long secsInDay = ( fsecsInDay - floor( fsecsInDay )) > 0.5 ? (long) (fsecsInDay) + 1 : (long) fsecsInDay;

    if( secsInDay == 0 )
        date.m_inHour = date.m_inMin = date.m_inSec = 0;
    else {
        date.m_inSec = (int) secsInDay % 60L;
        long minutesInDay = secsInDay / 60L;
        date.m_inMin = (int) minutesInDay % 60;
        date.m_inHour = (int) minutesInDay / 60;
    }
}

void CDateTime::getDateH( _DateTimeDetail & date )
{
    getDate(date);
    civ2heb(&date);
}


CInteger CDateTime::getDay() const
{
    _DateTimeDetail date;

    getDate( date );
    return date.m_inDay;
}


//
// Converte Calendario Gregoriano para o correnspondente dia juliano.
// Funcao adaptada da biblioteca Borland C++ 4.0
// Abaixo a observacao contida na funcao:

// Algoritm 199 from Communications of the ACM, Volume 6, No.
// 8, (Aug. 1963), p. 444.  Gregorian calendar started on Sep. 14, 1752.
// This function is not valid before that.
//
double CDateTime::getJulianDay() const
{
    _DateTimeDetail date;

    getDate( date );

    return _getJulianDay( date.m_inYear, date.m_inMonth, date.m_inDay, date.m_inHour, date.m_inMin, date.m_inSec);
}

double CDateTime::_getJulianDay( int nYear, int nMonth, int nDay, int nHour, int nMin, int nSec) const
{
    unsigned int c, ya;
    double ret;

    if( !isValidDate( nYear, nMonth, nDay ))
        return 0;

    if( nMonth > 2 )
        nMonth -= 3;
    else {
        nMonth += 9;
        nYear--;
    }
    c  = nYear / 100;
    ya = nYear - (100 * c);

    ret = ((146097L *c)>>2) + ((1461 * ya)>>2) + (153*nMonth + 2) / 5 + nDay + 1721119L;
    ret += (((nHour * 3600) + (nMin * 60) + nSec) / (24.0 * 3600.0));
    return ret;
}

CInteger CDateTime::getMonth() const
{
    _DateTimeDetail date;

    getDate( date );
    return date.m_inMonth;
}

CInteger CDateTime::getDaysInMonth( int month, int year )
{
    CDateTime date( year, month, 1 );

    return date.getDaysInMonth();
}

CInteger CDateTime::getDaysInMonth() const
{
    _DateTimeDetail date;

    getDate( date );

    if( date.m_inMonth >= 1 && date.m_inMonth <= 12 ) {
        int nDaysInMonth = DaysInMonth[ date.m_inMonth - 1 ];

        if( isLeapYear( date.m_inYear ) && date.m_inMonth == 2 )
            nDaysInMonth++;

        return nDaysInMonth;
    }
    return 0;
}

CStr CDateTime::getMonthName( int month ) const
{
    if( month >= 1 && month <= 12 ) {
        return MonthNames[ month - 1 ];
    }

    return "";
}

CInteger CDateTime::getWeekDay() const
{
    _DateTimeDetail date;

    getDate( date );

    return date.m_inWeekDay;
}

CStr CDateTime::getWeekDayName() const
{
    _DateTimeDetail date;

    getDate( date );

    return WeekDayNames[ date.m_inWeekDay - 1 ];
}

CStr CDateTime::getWeekDayName( int weekDay )
{
    if( weekDay >= 1 && weekDay <= 7 ) {
        return WeekDayNames[ weekDay - 1 ];
    }

    return "";
}

CStr CDateTime::getWeekDayNameH()
{
    _DateTimeDetail date;

    civ2heb( &date );

    return WeekDayNamesH[ date.m_inWeekDay - 1 ];
}

CStr CDateTime::getWeekDayNameH( int weekDay )
{
    if( weekDay >= 1 && weekDay <= 7 ) {
        return WeekDayNamesH[ weekDay - 1 ];
    }

    return "";
}

CInteger CDateTime::getYear() const
{
    _DateTimeDetail date;

    getDate( date );

    return date.m_inYear;
}

CInteger CDateTime::getCentury() const
{
    return ( getYear() / 100 ) + 1;
}


// Algorithm from K & R, "The C Programming Language", 1st ed.
bool CDateTime::isLeapYear( int year )
{
    return (( year & 3 ) == 0 && year % 100 != 0 || year % 400 == 0 ) ? true : false;
}

CInteger CDateTime::getHour() const
{
    _DateTimeDetail date;

    getDate( date );
    return date.m_inHour;
}

CInteger CDateTime::getMin() const
{
    _DateTimeDetail date;

    getDate( date );
    return date.m_inMin;
}

CInteger CDateTime::getSec() const
{
    _DateTimeDetail date;

    getDate( date );
    return date.m_inSec;
}

int CDateTime::getRep( const char * & picture, char c ) const
{
    int nCount = 0;

    while( *picture == c ) {
        picture++;
        nCount++;
    }
    return nCount;
}

bool CDateTime::isValidTime( int hour, int min, int sec )
{
    if( hour < 0 || hour > 23 || min < 0 || min > 59 || sec < 0 || sec > 59 )
        return false;

    return true;
}

bool CDateTime::isValidDate( int nYear, int nMonth, int nDay )
{
#ifdef _DEBUG
    if( nDay <= 0 || nMonth < 1 || nMonth > 12 || nYear < 1 )
        return false;
#else
    if( nDay <= 0 || nMonth < 1 || nMonth > 12 || nYear < 1753 )
        return false;
#endif

    int nDaysInMonth = DaysInMonth[ nMonth - 1 ];

    if( isLeapYear( nYear ) && nMonth == 2 )
        nDaysInMonth++;

    return nDay <= nDaysInMonth ? true : false;
}


/*------------------------------------------------
Function    : isHoliday
Author      : FLM
Date        : 10/07/2001
Visibility  : Exported
Arguments   : -
Return      : bool indicando Feriado (TRUE) ou nao (FALSE)
Description : Calcula se a data eh um Feriado (fixo ou movel)
Portability : WULOMIN (Win/Unix/Linux/OS2/Mac/Ingenico(MONOS)/Nurit(Lipman))
Remarks     : -
History     : -
------------------------------------------------*/
bool CDateTime::isHoliday(CStr* pszHoliday /* = NULL */) const
{
    int inAno, inMes, inDia;
    bool boFeriado;

    boFeriado = FALSE;
    inAno = getYear();
    inMes = getMonth();
    inDia = getDay();

    // Feriados Fixos
    if((inMes ==  1 && inDia ==  1) ||
       (inMes ==  1 && inDia == 25) || // Em SP: Aniversário da Cidade de SP
       (inMes ==  4 && inDia == 21) ||
       (inMes ==  5 && inDia ==  1) ||
       (inMes ==  7 && inDia ==  9) || // Em SP: Revolucao de 1932
       (inMes ==  9 && inDia ==  7) ||
       (inMes == 10 && inDia == 12) ||
       (inMes == 11 && inDia ==  2) ||
       (inMes == 11 && inDia == 15) ||
       (inMes == 11 && inDia == 20) || // Em SP: Dia da Consciencia Negra
       (inMes == 12 && inDia == 25) ||
       (inMes == 12 && inDia == 31)) {
        boFeriado = TRUE;
        if(pszHoliday) {
            switch(inMes) {
                case 1:
                    if(inDia == 1) {
                        *pszHoliday = "Confraternização Universal";
                    } else {
                        *pszHoliday = "Aniversário de SP (SP)";
                    }
                    break;
                case 4:
                    *pszHoliday = "Tiradentes";
                    break;
                case 5:
                    *pszHoliday = "Dia do Trabalho";
                    break;
                case 7:
                    *pszHoliday = "Revolução de 1932 (SP)";
                    break;
                case 9:
                    *pszHoliday = "Independência";
                    break;
                case 10:
                    *pszHoliday = "Dia de Nsa. Senhora Aparecida";
                    break;
                case 11:
                    if(inDia == 2) {
                        *pszHoliday = "Finados";
                    } else if(inDia == 15) {
                        *pszHoliday = "Proclamação da República";
                    } else {
                        *pszHoliday = "Dia da Consciência Negra (SP)";
                    }
                    break;
                case 12:
                    if(inDia == 25) {
                        *pszHoliday = "Natal";
                    } else {
                        *pszHoliday = "Ano Novo";
                    }
                    break;
            }
        }
    }
    else {
        int inTempA, inTempB, inTempC, inTempD, inTempE;
        int inTempF, inTempG, inTempH, inTempI, inTempK;
        int inTempL, inTempM, inTempP, inTempQ;

        inTempA = inAno % 19;
        inTempB = inAno / 100;
        inTempC = inAno % 100;
        inTempD = inTempB / 4;
        inTempE = inTempB % 4;
        inTempF = (inTempB + 8) / 25;
        inTempG = (inTempB - inTempF + 1) / 3;
        inTempH = ((19 * inTempA + inTempB - inTempD - inTempG + 15) % 30);
        inTempI = inTempC / 4;
        inTempK = inTempC % 4;
        inTempL = ((32 + (2 * inTempE) + (2 * inTempI) - inTempH - inTempK) % 7);
        inTempM = ((inTempA + (11 * inTempH) + (22 * inTempL)) / 451);
        inTempP = ((inTempH + inTempL - (7 * inTempM) + 114) / 31);
        inTempQ = ((inTempH + inTempL - (7 * inTempM) + 114) % 31);
        CDateTime inTempDT(inAno, inTempP, inTempQ+1);

        switch (getDiff(inTempDT)) {
            case -48:   // 1o. dia Carnaval (Seg)
                if(*pszHoliday) {
                    *pszHoliday = "Segunda de Carnaval";
                }
                boFeriado = TRUE;
                break;
            case -47:   // 2o. dia Carnaval (Ter)
                if(*pszHoliday) {
                    *pszHoliday = "Terça de Carnaval";
                }
                boFeriado = TRUE;
                break;
            case -2:    // Sexta-Feira Santa
                if(*pszHoliday) {
                    *pszHoliday = "Sexta-Feira Santa";
                }
                boFeriado = TRUE;
                break;
            case 0:     // Domingo de Pascoa
                if(*pszHoliday) {
                    *pszHoliday = "Domingo de Páscoa";
                }
                boFeriado = TRUE;
                break;
            case 60:    // Corpus-Cristi
                if(*pszHoliday) {
                    *pszHoliday = "Corpus Cristi";
                }
                boFeriado = TRUE;
                break;
            default:    // Diferente de todos acima
                boFeriado = FALSE;
        }
    }
    return boFeriado;
}

bool CDateTime::isEmpty() const
{
    return (m_dlJulianDay == 0.00 );
}

void CDateTime::setDay( int day )
{
    _DateTimeDetail date;

    getDate( date );

    setDate( date.m_inYear, date.m_inMonth, day );
}

void CDateTime::setMonth( int month )
{
    _DateTimeDetail date;

    getDate( date );

    setDate( date.m_inYear, month, date.m_inDay );
}

void CDateTime::setYear( int year )
{
    _DateTimeDetail date;

    getDate( date );

    setDate( year, date.m_inMonth, date.m_inDay );
}

void CDateTime::setDate( int year, int month, int day )
{
    _DateTimeDetail Detail;
    getDate( Detail );
    setDateTime( year, month, day, Detail.m_inHour, Detail.m_inMin, Detail.m_inSec );
}

void CDateTime::setTime( int hour, int min, int sec  )
{
    _DateTimeDetail Detail;
    getDate( Detail );
    setDateTime( Detail.m_inYear, Detail.m_inMonth, Detail.m_inDay, hour, min, sec );
}

void CDateTime::setDateTime( int year, int month, int day, int hour, int min, int sec )
{
    if( isValidDate( year, month, day ) && isValidTime( hour, min, sec )) {
        m_dlJulianDay = _getJulianDay( year, month, day ) +
                        (((long)hour * 3600L) +  // hrs in seconds
                         ((long)min * 60L) +  // mins in seconds
                         ((long)sec)) / 86400.;   // fracao de 1 segundo em cada hora do dia (24*3600)
    }
    // coloca somente a hora
    else if( isValidTime( hour, min, sec )) {
        m_dlJulianDay = (((long)hour * 3600L) +  // hrs in seconds
                         ((long)min * 60L) +  // mins in seconds
                         ((long)sec)) / 86400.;   // fracao de 1 segundo em cada hora do dia (24*3600)
    }
    getDateH( m_DateTimeDetail );
}

/********************************************************************
 Proposito  : Retorna uma data somando (ou subtraindo) dias da data atual
 Parametros : days - quantidade de dias a somar a data atual. Caso day
              seja um numero negativo, subtrai os dias data.
 Retorno    : data com os dias somados / subtraidos
********************************************************************/
CDateTime CDateTime::addDays( int days ) const
{
    return CDateTime( m_dlJulianDay + days );
}

/********************************************************************
 Proposito  : Retorna uma data somando (ou subtraindo) meses da data atual.
 Parametros : months - quantidade de meses a somar a data atual. Caso months
              seja um numero negativo, subtrai os meses da data. Caso no mes
              final não exista o dia correspondente ( por exemplo, somar
              um mes a data 31/01/2000, não existe o dia 31/02) será
              atribuido o último dia válido do mês. Veja também a função
              getNextMonth().
 Retorno    : data com os meses somados / subtraidos
********************************************************************/
CDateTime CDateTime::addMonths( int months ) const
{
    int desiredDay = getDay();
    CDateTime ret = *this;

    if( months > 0 ) {
        while( months ) {
            ret = ret.getNextMonth( desiredDay );
            months--;
        }
    }
    else if( months < 0 ) {
        while( months ) {
            ret = ret.getPreviousMonth( desiredDay );
            months++;
        }
    }
    return ret;
}

/********************************************************************
 Proposito  : Retorna uma data somando (ou subtraindo) anos da data atual
 Parametros : years - quantidade de dias a somar a data atual. Caso day
              seja um numero negativo, subtrai os dias data.
 Retorno    : data com os dias somados / subtraidos
********************************************************************/
CDateTime CDateTime::addYears( int years ) const
{
    int iAno, iMes, iDia;

    iAno = getYear() + years;
    iMes = getMonth();
    iDia = getDay();
    if(!isValidDate(iAno, iMes, iDia)) {
        return CDateTime(iAno, iMes, getDaysInMonth(iAno, iMes));
    } else {
        return CDateTime( iAno, iMes, iDia);
    }
}

/********************************************************************
 Proposito  : Retorna a data referente ao mes subsequente.
 Parametros : desiredDay - dia no mes seguinte (0=Mesmo dia atual). Caso o mes
              tenha menos dias do que o dia desejado, será utilizado
              o ultimo dia do mes (por exemplo, se o mes seguinte for
              fevereiro e o dia desejado for o dia 30, será utilizado
              o dia 28 ou 29, se o ano for bissexto)
 Retorno    : data no mes seguinte
 Exemplo    : se a data atual for 10/05/2001 e desiredDay for dia 20,
              a funcao retornará 20/06/2001.
********************************************************************/
CDateTime CDateTime::getNextMonth( int desiredDay ) const
{
    int nextMonth = getMonth() + 1;
    int year = getYear();
    int day = getDay();

    if( nextMonth > 12 ) {
        year++;
        nextMonth = 1;
    }
    int iMaxDays = getDaysInMonth( nextMonth, year );
    return CDateTime( year, nextMonth, (desiredDay == 0 ? (iMaxDays < day ? iMaxDays : day) : (iMaxDays < desiredDay ? iMaxDays : desiredDay)));
}

/********************************************************************
 Proposito  : Retorna a data referente ao mes anterior.
 Parametros : desiredDay - dia no mes anterior (0=Mesmo dia atual). Caso o mes
              tenha menos dias do que o dia desejado, será utilizado
              o ultimo dia do mes (por exemplo, se o mes anterior for
              fevereiro e o dia desejado for o dia 30, será utilizado
              o dia 28 ou 29, se o ano for bissexto)
 Retorno    : data no mes anterior
 Exemplo    : se a data atual for 10/05/2001 e desiredDay for dia 20,
              a funcao retornará 20/06/2001.
********************************************************************/
CDateTime CDateTime::getPreviousMonth( int desiredDay ) const
{
    int previousMonth = getMonth() - 1;
    int year = getYear();
    int day = getDay();

    if( previousMonth < 1 ) {
        year--;
        previousMonth = 12;
    }
    int iMaxDays = getDaysInMonth( previousMonth, year );
    return CDateTime( year, previousMonth, (desiredDay == 0 ? (iMaxDays < day ? iMaxDays : day) : (iMaxDays < desiredDay ? iMaxDays : desiredDay)));
}


int operator ==( const CDateTime & c, const CDateTime & d )
{
    return (c.getJulianDay() == d.getJulianDay());
}

int operator >( const CDateTime & c, const CDateTime & d )
{
    return (c.getJulianDay() > d.getJulianDay());
}

int operator <( const CDateTime & c, const CDateTime & d )
{
    return (c.getJulianDay() < d.getJulianDay());
}

int operator >=( const CDateTime & c, const CDateTime & d )
{
    return (c.getJulianDay() >= d.getJulianDay());
}

int operator <=( const CDateTime & c, const CDateTime & d )
{
    return (c.getJulianDay() <= d.getJulianDay());
}

int operator !=( const CDateTime & c, const CDateTime & d )
{
    return (c.getJulianDay() != d.getJulianDay());
}

/*------------------------------------------------
Function    : convertCStrToDateTime
Date        : 04/09/2002
Visibility  : Exported (Auxiliar)
Arguments   : date (char*) - Data em um dos formatos: ddmmyy
                                                      ddmmyyyy
                                                      dd/mm/yy
                                                      dd/mm/yyyy
                                                      dd/mm/yyyy hh:nn:ss
Return      : CDateTime contendo a data informada
Description : Converte uma CStr para CDateTime
Remarks     :
Portability : WULO (Win/Unix/Linux/OS2)
History     :
------------------------------------------------*/
CDateTime convertCStrToDateTime( CStr& szData )
{
    int iAno;
    switch(szData.getLen()) {
        case 6:
            iAno = szData.getRight(2).getInteger();
            iAno = (iAno <= 30 ? iAno + 2000 : iAno + 1900);
            return CDateTime(iAno, szData.getMid(3, 2).getInteger(), szData.getLeft(2).getInteger());
            break;
        case 8:
            if(szData.find("/")) {
                iAno = szData.getRight(2).getInteger();
                iAno = (iAno <= 30 ? iAno + 2000 : iAno + 1900);
                return CDateTime(iAno, szData.getMid(3,2).getInteger(), szData.getLeft(2).getInteger());
            }
            else {
                return CDateTime(szData.getRight(4).getInteger(), szData.getMid(3,2).getInteger(), szData.getLeft(2).getInteger());
            }
            break;
        case 10:
            return CDateTime(szData.getRight(4).getInteger(), szData.getMid(4,2).getInteger(), szData.getLeft(2).getInteger());
            break;
        case 19:
            return CDateTime(szData.getMid(6, 4).getInteger(),  szData.getMid(3, 2).getInteger(),  szData.getLeft(2).getInteger(),
                             szData.getMid(11, 2).getInteger(), szData.getMid(14, 2).getInteger(), szData.getRight(2).getInteger());
            break;
        default:
            return CDateTime();
    }
}

int CDateTime::gauss(int iAno)
{
    double a,b,c;
    double m;
    int    iYear, Mar;    // "day in March" on which Pessach falls (return value)

    iYear = (iAno == NULL ? getYear() + 3760 : iAno);
    a = (int)((12 * iYear + 17) % 19);
    b = (int)(iYear % 4);
    m = 32.044093161144 + 1.5542417966212 * a +  b / 4.0 - 0.0031777940220923 * iYear;
    if (m < 0)
        m -= 1;
    Mar = (int)(m);
    if (m < 0)
        m++;
    m -= Mar;

    c = (Mar + 3 * iYear + 5 * b + 5) ; // % 7);
    c = ((int)c) % 7;
    if(c == 0 && a > 11 && m >= 0.89772376543210 )
        Mar++;
    else if(c == 1 && a > 6 && m >= 0.63287037037037)
        Mar += 2;
    else if(c == 2 || c == 4 || c == 6)
        Mar++;

    Mar += ((int)((iYear - 3760) / 100)) - ((int)((iYear - 3760) / 400)) - 2;
    return Mar;
}

CStr CDateTime::civ2heb(_DateTimeDetail* DtDetail /* = NULL */, bool boConsiderSunset /* = false */)
{
    char   szBuff[50];
    double day = getDay();
    double mon = getMonth();
    double yea = getYear();
    double hy;
    double pessach;
    double anchor;
    double adarType;

    mon -= 2;
    if (mon <= 0) { // Jan or Feb
        mon += 12;
        yea -= 1;
    }

    day += ((int)(7 * mon / 12 + 30 * (mon - 1))); // day in March
    hy = yea + 3760;    // get Hebrew year
    pessach = gauss((int)hy);
    if (day <= pessach - 15) { // before 1 Nisan
        anchor = pessach;
        day += 365;
        if(isLeapYear((int)yea))
            day++;
        yea -= 1;
        hy -= 1;
        pessach = gauss((int)hy);
    }
    else
        anchor = gauss((int)(hy + 1));

    day -= pessach - 15;
    anchor -= pessach - 12;
    yea++;
    if(isLeapYear((int)yea))
        anchor++;

    for(mon = 0; mon < 11; mon++) {
        double days;
        if(mon == 7 && (int)anchor % 30 == 2)
            days = 30; // Cheshvan
        else if(mon == 8 && (int)anchor % 30 == 0)
            days = 29; // Kislev
        else
            days = 30 - ((int)mon % 2);
        if(day <= days)
            break;
        day -= days;
    }

    adarType = 0;            // plain old Adar
    if (mon == 11 && anchor >= 30) {
        if (day > 30) {
            adarType = 1;    // Adar 2
            day -= 30;
        }
        else
            adarType = 0;    // Adar 1
    }

    if(mon >= 6)        // Tishrei or after?
        hy++;        // then bump up year

    if(mon == 11)            // Adar?
        mon += adarType;    // adjust for Adars

    if(boConsiderSunset) {
        if(getHour() >= 18) {
            day++;
        }
    }
    if(DtDetail != NULL) {
        getDate(*DtDetail);
        DtDetail->m_inHDay = (int)day;
        DtDetail->m_inHMonth = (int)mon;
        DtDetail->m_inHYear = (int) hy;
    }

//#ifdef UNICODE
//    wsprintf((wchar_t *)szBuff, (wchar_t*)"%d de %s (%d) de %d", (int)day, MonthNamesJ[(int)mon], (int)(mon+1), (int)hy);
//#else
    sprintf(szBuff, "%d de %s (%d) de %d", (int)day, MonthNamesJ[(int)mon], (int)(mon+1), (int)hy);
//#endif

    return CStr(szBuff);
}

CStr CDateTime::heb2civ(_DateTimeDetail& DtDetail)
{
    _DateTimeDetail dtTemporario;
    CDateTime       dtConvertida;
    double          dlTempo;
    int             inContador, inDiferenca, inIncremento = 2;

    dlTempo = inContador = 0;
    DtDetail.m_inHMonth--;
    dtConvertida.setDate((DtDetail.m_inHYear - 3760), ((DtDetail.m_inHMonth + (DtDetail.m_inHMonth == 9 ? 3 : 4)) % 13), DtDetail.m_inHDay) ;

    dtConvertida.civ2heb(&dtTemporario);
    //while (memcmp(&dtTemporario.m_inHDay, &DtDetail.m_inHDay, (sizeof(int) * 3)) != 0) {
    while (!(dtTemporario.m_inHDay == DtDetail.m_inHDay && dtTemporario.m_inHMonth == DtDetail.m_inHMonth &&
             dtTemporario.m_inHYear == DtDetail.m_inHYear) ) {

        if((inContador++) > 99) {
            setEmpty();
            return CStr("");
        }

        //dtTemporario.m_inHMonth--;
        inDiferenca = ((DtDetail.m_inHYear - dtTemporario.m_inHYear) * 12.5 * 29.5) + ((DtDetail.m_inHMonth - (dtTemporario.m_inHMonth)) * 29.5) + ((DtDetail.m_inHDay - dtTemporario.m_inHDay));
        dlTempo += ((DtDetail.m_inHYear - dtTemporario.m_inHYear) * 12.5 * 29.5) + ((DtDetail.m_inHMonth - (dtTemporario.m_inHMonth - (abs(inDiferenca) <= 60 ? 0 : inIncremento ))) * 29.5) + ((DtDetail.m_inHDay - dtTemporario.m_inHDay) + .5);
        dtConvertida = dtConvertida.addDays((int)dlTempo);
        dlTempo -= (int) dlTempo;
        inIncremento--;
        inIncremento = (inIncremento <= 0) ? 0 : inIncremento;

        dtConvertida.civ2heb(&dtTemporario);
    }
    //dtConvertida = dtConvertida.addDays(-1);
    setDate(dtConvertida.getYear(), dtConvertida.getMonth(), dtConvertida.getDay());
    DtDetail.m_inHMonth++;
    civ2heb(&m_DateTimeDetail);

    //DtDetail.m_inHMonth++;
    return format("dd/mm/yyyy"); //  CStr("");
}

/*------------------------------------------------
Function    : isHHoliday
Author      : FLM
Date        : 20/08/2002
Visibility  : Exported
Arguments   : -
Return      : bool indicando Feriado (TRUE) ou nao (FALSE)
Description : Calcula se a data eh um Feriado Habraico
Portability : WULOMIN (Win/Unix/Linux/OS2/Mac/Ingenico(MONOS)/Nurit(Lipman))
Remarks     : Baseado no Calendario Habraico em http://www.kaluach.net/
              12/01 = Taanit Bechorot (dow == 5/Quinta)
              14/01 = Taanit Bechorot (dow != 7/Sábado)
              15/01 = Pessach
              02/02 = Yom Hazikaron   (dow == 4/Quarta)
              03/02 = Yom Hazikaron   (dow == 5/Quinta)
              03/02 = Yom Ha'Atzmaut  (dow == 5/Quinta)
              04/02 = Yom Ha'Atzmaut  (dow != 6 && != 7)
              14/02 = Pessach Sheni
              18/02 = Lag B'Omer
              28/02 = Yom Yerushalayim
              06/03 = Shavuot
              17/04 = Fast Of Tammuz  (dow != 7/Sábado )
              18/04 = Fast of Tammuz  (dow == 1/Domingo)
              09/05 = Tisha B'Av      (dow != 7/Sábado )
              10/05 = Tisha B'Av      (dow == 1/Domingo)
              15/05 = Tu B'Av
              06/06 = Meu Aniversario :-D
              01/07 = Rosh Hashanah
              10/07 = Yom Kippur
              15/07 = Sukkot
              25/09 = Chanukkah
              11/13 = Taanit Ester    (dow = 5/Quinta )
              13/13 = Taanit Ester    (dow != 7/Sábado)
              11/12 = Taanit Ester    (dow = 5/Quinta )
              13/12 = Taanit Ester    (dow != 7/Sábado)
              14/13 = Purim
              14/12 = Purim
History     : -
------------------------------------------------*/
bool CDateTime::isHHoliday(CStr* pszHoliday /* = NULL */) // (cday, cmonth, cyear, hday, hmonth, dow)
{
    int                 inDow;
    int                 cday, cmonth, cyear;
    _DateTimeDetail     date, Tmpdate;

    getDateH( date );

    inDow  = getWeekDay();
    cday   = getDay();
    cmonth = getMonth();
    cyear  = getYear();

    if(date.m_inHMonth == 6) { // Tishrei
        if(date.m_inHDay == 1 || date.m_inHDay == 2) {
            if(pszHoliday != NULL) {
                *pszHoliday = "Rosh Hashana";
            }
            return TRUE;
        }
        else if(date.m_inHDay == 3 && inDow != 7) {
            if(pszHoliday != NULL) {
                *pszHoliday = "Fast of Gedalia";
            }
            return TRUE;
        }
        else if(date.m_inHDay == 4 && inDow == 1) {
            if(pszHoliday != NULL) {
                *pszHoliday = "Fast of Gedalia";
            }
            return TRUE;
        }
        else if(date.m_inHDay == 10) {
            if(pszHoliday != NULL) {
                *pszHoliday = "Yom Kippur";
            }
            return TRUE;
        }
        else if(date.m_inHDay >= 15 && date.m_inHDay <= 22) {
            if(pszHoliday != NULL) {
                *pszHoliday = "Sukkot";
            }
            return TRUE;
        }
        else if(date.m_inHDay == 23) {
            if(pszHoliday != NULL) {
                *pszHoliday = "Sukkot (d)";
            }
            return TRUE;
        }
    }
    else if(date.m_inHMonth == 8) { // Kislev
        if(date.m_inHDay >= 25) {
            if(pszHoliday != NULL) {
                *pszHoliday = "Chanukkah";
            }
            return TRUE;
        }
    }
    else if(date.m_inHMonth == 9) { // Tevet
        if(date.m_inHDay <= 2) {
            if(pszHoliday != NULL) {
                *pszHoliday = "Chanukkah";
            }
            return TRUE;
        }
        else if(date.m_inHDay == 3) {
            // Kislev can be malei or chaser
            if(cday == 1) {
                cday = 29;
                cmonth = 11;
            }
            else if(cday == 2) {
                cday = 30;
                cmonth = 11;
            }
            else
                cday -= 3;

            CDateTime hdate(cyear, cmonth, cday);
            hdate.civ2heb(&Tmpdate);
            if(Tmpdate.m_inHDay == 29) {
                if(pszHoliday != NULL) {
                    *pszHoliday = "Chanukkah";
                }
                return TRUE;
            }
        }
        else if(date.m_inHDay == 10) {
            if(pszHoliday != NULL) {
                *pszHoliday = "Fast of Tevet";
            }
            return TRUE;
        }
    }
    else if(date.m_inHMonth == 10) { // Shevat
        if(date.m_inHDay==15) {
            if(pszHoliday != NULL) {
                *pszHoliday = "Tu b'Shvat";
            }
            return TRUE;
        }
    }
    else if(date.m_inHMonth == 11 || date.m_inHMonth == 12) { // Adar / Adar II
        CDateTime hdate;

        getDateH(Tmpdate);
        Tmpdate.m_inHDay = 1;
        Tmpdate.m_inHMonth = 13;
        Tmpdate.m_inHYear = date.m_inHYear;
        hdate.heb2civ(Tmpdate) ;
        if(!hdate.isEmpty()) {
            if(date.m_inHMonth == 11) {
                if(pszHoliday != NULL) {
                    *pszHoliday = "";
                }
                return FALSE;
            }
        }

        if(date.m_inHDay == 11 && inDow == 5) {
            if(pszHoliday != NULL) {
                *pszHoliday = "Ta'anit Esther";
            }
            return TRUE;
        }
        else if(date.m_inHDay == 13 && inDow != 7) {
            if(pszHoliday != NULL) {
                *pszHoliday = "Ta'anit Esther";
            }
            return TRUE;
        }
        else if(date.m_inHDay == 14) {
            if(pszHoliday != NULL) {
                *pszHoliday = "Purim";
            }
            return TRUE;
        }
        else if(date.m_inHDay == 15) {
            CDateTime hdate;

            Tmpdate.m_inHDay = 1;
            Tmpdate.m_inHMonth = 13;
            Tmpdate.m_inHYear = date.m_inHYear;
            hdate.heb2civ(Tmpdate) ;
            if(!hdate.isEmpty()) {
                if(pszHoliday != NULL) {
                    *pszHoliday = "Shushan Purim";
                }
                return TRUE;
            }
        }
    }
    else if(date.m_inHMonth == 0) { // Nisan
        if(date.m_inHDay == 12 && inDow == 5) {
            if(pszHoliday != NULL) {
                qDebug() << "Dia 12 dow 5";
                *pszHoliday = "Ta'anit Bechorot";
            }
            return TRUE;
        }
        else if(date.m_inHDay == 14 && inDow != 7) {
            if(pszHoliday != NULL) {
                qDebug() << "Dia 14 dow !7";
                *pszHoliday = "Ta'anit Bechorot";
            }
            return TRUE;
        }
        else if(date.m_inHDay >= 15 && date.m_inHDay <= 21) {
            if(pszHoliday != NULL) {
                *pszHoliday = "Pessach";
            }
            return TRUE;
        }
        else if(date.m_inHDay == 22) {
            if(pszHoliday != NULL) {
                *pszHoliday = "Pessach (d)";
            }
            return TRUE;
        }
        else if(date.m_inHDay == 27) {
            if(pszHoliday != NULL) {
                *pszHoliday = "Yom HaShoah"; // Dia da Lembranca do Holocausto
            }
            return TRUE;
        }
    }
    else if(date.m_inHMonth == 1) { // Iyyar        
        //DEBUG_MSG(QString("Dia %1/%2 (Dia da Semana %3)").arg(date.m_inHDay).arg(date.m_inHMonth).arg(inDow).toStdString().c_str());
        if(date.m_inHDay == 2 && inDow == 4) {
            if(pszHoliday != NULL) {
                *pszHoliday = "Yom HaZikaron";
            }
            return TRUE;
        }
        else if(date.m_inHDay == 3 && inDow == 4) {
            if(pszHoliday != NULL) {
                *pszHoliday = "Yom HaZikaron";
            }
            return TRUE;
        }
        else if(date.m_inHDay == 4) { // && inDow != 6) {
            if(pszHoliday != NULL) {
                *pszHoliday = "Yom HaZikaron";
            }
            return TRUE;
        }

        if(date.m_inHDay == 3 && inDow == 5) {
            if(pszHoliday != NULL) {
                *pszHoliday = "Yom Ha'Atzmaut";
            }
            return TRUE;
        }
        else if(date.m_inHDay == 4 && inDow == 5) {
            if(pszHoliday != NULL) {
                *pszHoliday = "Yom Ha'Atzmaut";
            }
            return TRUE;
        }
        else if(date.m_inHDay == 5 ) { // && inDow != 7) {
            if(pszHoliday != NULL) {
                *pszHoliday = "Yom Ha'Atzmaut";
            }
            return TRUE;
        }
        if(date.m_inHDay == 14) {
            if(pszHoliday != NULL) {
                *pszHoliday = "Pessach sheni";
            }
            return TRUE;
        }
        else if(date.m_inHDay == 18) {
            if(pszHoliday != NULL) {
                *pszHoliday = "Lag B'Omer";
            }
            return TRUE;
        }
        if(date.m_inHDay == 28) {
            if(pszHoliday != NULL) {
                *pszHoliday = "Yom Yerushalayim";
            }
            return TRUE;
        }
    }
    else if(date.m_inHMonth == 2) { // Sivan
        if(date.m_inHDay == 6) {
            if(pszHoliday != NULL) {
                *pszHoliday = "Shavuot";
            }
            return TRUE;
        }
        else if(date.m_inHDay == 7) {
            if(pszHoliday != NULL) {
                *pszHoliday = "Shavuot (d)";
            }
            return TRUE;
        }
    }
    else if(date.m_inHMonth == 3) { // Tamuz
        if(date.m_inHDay == 17 && inDow != 7) {
            if(pszHoliday != NULL) {
                *pszHoliday = "Fast of Tammuz";
            }
            return TRUE;
        }
        if(date.m_inHDay == 18 && inDow == 1) {
            if(pszHoliday != NULL) {
                *pszHoliday = "Fast of Tammuz";
            }
            return TRUE;
        }
    }
    else if(date.m_inHMonth == 4) { // Av
        if(date.m_inHDay == 9 && inDow != 7) {
            if(pszHoliday != NULL) {
                *pszHoliday = "Tisha B'Av";
            }
            return TRUE;
        }
        if(date.m_inHDay == 10 && inDow == 1) {
            if(pszHoliday != NULL) {
                *pszHoliday = "Tisha B'Av";
            }
            return TRUE;
        }
        if(date.m_inHDay == 15) {
            if(pszHoliday != NULL) {
                *pszHoliday = "Tu B'Av";
            }
            return TRUE;
        }
    }
    else if(date.m_inHMonth == 5) { // Elul
        if(date.m_inHDay == 6) {
            if(pszHoliday != NULL) {
                *pszHoliday = "Yom HaHuledet Sheli";
            }
            return TRUE;
        }
    }

    if(pszHoliday != NULL) {
        *pszHoliday = "";
    }
    return FALSE;
}

CInteger CDateTime::getHDay()
{
    _DateTimeDetail date;

    getDateH( date );
    return date.m_inHDay;
}

CInteger CDateTime::getHMonth()
{
    _DateTimeDetail date;

    getDateH( date );
    return date.m_inHMonth;
}

CInteger CDateTime::getHYear()
{
    _DateTimeDetail date;

    getDateH( date );
    return date.m_inHYear;
}

void     CDateTime::setHYear( int year )
{
    _DateTimeDetail date;

    getDateH( date );
    date.m_inHYear = year;

    heb2civ( date);
}

void     CDateTime::setHMonth( int month )
{
    _DateTimeDetail date;

    getDateH( date );
    date.m_inHMonth = month;

    heb2civ( date);
}

void     CDateTime::setHDay( int day )
{
    _DateTimeDetail date;

    getDateH( date );
    date.m_inHDay = day;

    heb2civ( date );
}

// Funcao auxiliar para conversao de datas
/*------------------------------------------------
Function    : ConvertYYYYMMDDToDateTime
Author      : FLM
Date        : 10/07/2001
Visibility  : Exported
Arguments   : date (char*) - Buffer contendo data  (yyyymmdd
                                                    yyyymmdd HHnnss
                                                    yyyy/mm/dd
                                                    yyyy/mm/dd HH:nn:ss)
Return      : CDateTime contendo data/hora
Description : Converte uma string para um objeto CDateTime
Portability : WULOMIN (Win/Unix/Linux/OS2/Mac/Ingenico(MONOS)/Nurit(Lipman))
Remarks     : -
History     : 21/07/2004 -  Acrescido processamento da hora
------------------------------------------------*/
CDateTime convertYYYYMMDDToDateTime( const char * date )
{
    int iTamanho;

    iTamanho = strlen(date);
    switch(iTamanho) {
        //if(iTamanho == 8) { // yyyymmdd
        case 8:
            {
                CStr dia( date + 4, 2 );
                CStr mes( date + 2, 2 );
                CStr ano( date, 4 );
                return CDateTime( ano.getInteger(), mes.getInteger(), dia.getInteger());
            }
        case 10: //} else if(iTamanho == 10) { // yyyy/mm/dd
            {
                CStr dia( date + 8, 2 );
                CStr mes( date + 5, 2 );
                CStr ano( date, 4 );
                return CDateTime( ano.getInteger(), mes.getInteger(), dia.getInteger());
            }
            //                         12345678901234567890
        case 15: //} else if(iTamanho == 15) { // yyyymmdd hhnnss
            {
                CStr dia( date + 7, 2 );
                CStr mes( date + 5, 2 );
                CStr ano( date, 4 );
                CStr hor( date + 9, 2 );
                CStr mnt( date + 11, 2 );
                CStr seg( date + 13, 2 );
                return CDateTime( ano.getInteger(), mes.getInteger(), dia.getInteger(),
                                  hor.getInteger(), mnt.getInteger(), seg.getInteger());
            }
        default: //} else { // yyyy/mm/dd hh:nn:ss
            {
                CStr dia( date + 8, 2 );
                CStr mes( date + 5, 2 );
                CStr ano( date, 4 );
                CStr hor( date + 11, 2 );
                CStr mnt( date + 14, 2 );
                CStr seg( date + 17, 2 );
                return CDateTime( ano.getInteger(), mes.getInteger(), dia.getInteger(),
                                  hor.getInteger(), mnt.getInteger(), seg.getInteger());
            }
    }

}


/*------------------------------------------------
Function    : ConvertDDMMYYYYToDateTime
Author      : FLM
Date        : 10/07/2001
Visibility  : Exported
Arguments   : date (char*) - Buffer contendo data  (ddmmyyyy
                                                    ddmmyyyy HHnnss
                                                    dd/mm/yyyy
                                                    dd/mm/yyyy HH:nn:ss)
Return      : CDateTime contendo data/hora
Description : Converte uma string para um objeto CDateTime
Portability : WULOMIN (Win/Unix/Linux/OS2/Mac/Ingenico(MONOS)/Nurit(Lipman))
Remarks     : -
History     : 21/07/2004 -  Acrescido processamento da hora
------------------------------------------------*/
CDateTime convertDDMMYYYYToDateTime( const char * date )
{
    int iTamanho;

    iTamanho = strlen(date);
    //                     12345678901234567890
    if(iTamanho == 8) { // DDMMYYYY
        CStr dia( date, 2 );
        CStr mes( date + 2, 2 );
        CStr ano( date + 4, 4 );
        return CDateTime( ano.getInteger(), mes.getInteger(), dia.getInteger());
        //                         12345678901234567890
    } else if(iTamanho == 10) { // DD/MM/YYYY
        CStr dia( date, 2 );
        CStr mes( date + 3, 2 );
        CStr ano( date + 6, 4 );
        return CDateTime( ano.getInteger(), mes.getInteger(), dia.getInteger());
        //                         12345678901234567890
    } else if(iTamanho == 15) { // DDMMYYYY HHNNSS
        CStr dia( date, 2 );
        CStr mes( date + 2, 2 );
        CStr ano( date + 4, 4 );
        CStr hora(date + 9, 2 );
        CStr mnt( date+ 11, 2 );
        CStr sec( date+ 13, 2 );
        return CDateTime( ano.getInteger(), mes.getInteger(), dia.getInteger(),
                          hora.getInteger(), mnt.getInteger(), sec.getInteger());
        //      12345678901234567890
    } else if(iTamanho == 19) { // DD/MM/YYYY HH:NN:SS
        CStr dia( date, 2 );
        CStr mes( date + 3, 2 );
        CStr ano( date + 6, 4 );
        CStr hor( date + 11, 2 );
        CStr mnt( date + 14, 2 );
        CStr seg( date + 17, 2 );
        return CDateTime( ano.getInteger(), mes.getInteger(), dia.getInteger(),
                          hor.getInteger(), mnt.getInteger(), seg.getInteger());
    } else {
        return CDateTime(0, 0, 0, 0, 0, 0);
    }
}

CDateTime & CDateTime::operator=( const CDateTime & other )
{
    m_dlJulianDay = other.m_dlJulianDay;
    getDate( m_DateTimeDetail );

    return *this;
}

void CDateTime::setJulianDay( double j )
{
    m_dlJulianDay = j;
    getDate( m_DateTimeDetail );
}

void CDateTime::setEmpty()
{
    m_dlJulianDay = 0;
}

