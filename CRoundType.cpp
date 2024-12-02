#include "CDatatypes.h"

#ifdef WIN32
#include <windows.h>
#endif


//////////////////////////////////////////////////////////////////////////////
// CRound
//
CRound::CRound( double n, int precision )
{
    m_dlValue = _round( n, precision );
    m_inPrecision = precision;
}

CRound::~CRound()
{
}

CRound CRound::round( int precision ) const
{
    static char format[30];
    static char result[30];

//#ifdef UNICODE
//    wsprintf( (wchar_t *)format, (wchar_t*)"%%.%df", precision );
//    wsprintf( (wchar_t *)result, (wchar_t *)format, m_dlValue );
//    return CRound( wcstod( (wchar_t *)result, NULL ), precision );
//#else
    sprintf( format, "%%.%df", precision );
    sprintf( result, format, m_dlValue );
    return CRound( atof( result ), precision );
//#endif

//    return CRound( m_dlValue, precision );
}

CRound CRound::floor( int precision ) const
{
    return CRound( ::floor(m_dlValue*pow(static_cast<double>(10),precision))/pow(static_cast<double>(10),precision), precision );
}

void CRound::setPrecision( int value )
{
    if( value < 0 || value > 18 )
        return;

    m_inPrecision = value;
    m_dlValue = _round( m_dlValue, m_inPrecision );
}

CRound CRound::getAbs() const
{
    CRound ret = *this;

    if( m_dlValue < 0 )
        ret.m_dlValue =  -m_dlValue;

    return ret;
}

/********************************************************************
 Proposito:    Converte o numero para string
 Retorno:   String convertida
 ********************************************************************/
CStr CRound::getString() const
{
    return format( CStr( "." + getPrecision().getString()));
}

CStr CRound::format( const char * formatSpec ) const
{
    return CDouble( m_dlValue ).format( formatSpec );
}

CRound & CRound::operator =( double n )
{
    m_dlValue = _round( n, m_inPrecision );
    return *this;
}

CRound CRound::operator -()
{
   CRound ret( *this );
   ret.m_dlValue = -m_dlValue;
   return ret;
}

CRound &  CRound::operator *= ( const CRound n )
{
    m_dlValue = _round( m_dlValue * n.m_dlValue, MAX( m_inPrecision, n.m_inPrecision ));
    return *this;
}

CRound &  CRound::operator *=( double n )
{
    m_dlValue = _round(  m_dlValue * m_dlValue, m_inPrecision );
    return *this;
}

CRound &  CRound::operator /=( double n )
{
    m_dlValue = _round( n / m_dlValue, m_inPrecision );
    return *this;
}

CRound CRound::operator*( const CRound & cur ) const
{
   return CRound( m_dlValue * cur.m_dlValue, 16 );// max( cur.m_inPrecision, m_inPrecision ));
}

CRound CRound::operator^( const CRound & cur ) const
{
   return CRound( pow( m_dlValue, cur.m_dlValue ), 16 );
}

CRound CRound::operator^( double d ) const
{
   return CRound( pow( m_dlValue, d ), 16 );
}

CRound CRound::operator/( const CRound & cur ) const
{
   return CRound( m_dlValue / cur.m_dlValue, 16 );
}

CRound &  CRound::operator +=( double n )
{
    m_dlValue = _round( n + m_dlValue, m_inPrecision );
    return *this;
}

CRound CRound::operator+( const CRound & cur ) const
{
   return CRound( m_dlValue + cur.m_dlValue, MAX( cur.m_inPrecision, m_inPrecision ));
}

CRound CRound::operator+( double n ) const
{
   return CRound( m_dlValue + n, m_inPrecision );
}

CRound operator+( double d, const CRound & value )
{
   return CRound( d + value.m_dlValue, value.getPrecision());
}

CRound operator*( double d, const CRound & value )
{
   return CRound( d * value.m_dlValue, value.getPrecision());
}

CRound operator/( double d, const CRound & value )
{
   return CRound( d / value.m_dlValue, value.getPrecision());
}

CRound operator-( double d, const CRound & value )
{
   return CRound( d - value.m_dlValue, value.getPrecision());
}

CRound CRound::operator-( const CRound & cur ) const
{
   return CRound( m_dlValue - cur.m_dlValue, MAX( cur.m_inPrecision, m_inPrecision ));
}

CRound CRound::operator-( double n ) const
{
   return CRound( m_dlValue - n, m_inPrecision );
}

CRound CRound::operator*( double n ) const
{
   return CRound( m_dlValue * n, 16 );
}

CRound CRound::operator/( double n ) const
{
   return CRound( m_dlValue / n, 16 );
}

int operator ==( const CRound & c, double d )
{
    return c.m_dlValue == d;
}

int operator ==( const CRound & c, const CRound & d )
{
    return c.m_dlValue == d.m_dlValue;
}

int operator ==( double c, const CRound & d )
{
    return c == d.m_dlValue;
}

int operator !=( const CRound & c, double d )
{
    return c.m_dlValue != d;
}

int operator !=( const CRound & c, const CRound & d )
{
    return c.m_dlValue != d.m_dlValue;
}

int operator !=( double c, const CRound & d )
{
    return c != d.m_dlValue;
}

int operator <( const CRound & c, double d )
{
    return c.m_dlValue  < d;
}

int operator <( const CRound & c, const CRound & d )
{
    return c.m_dlValue < d.m_dlValue;
}

int operator <=( const CRound & c, double d )
{
    return c.m_dlValue <= d;
}

int operator >( const CRound & c, double d )
{
    return c.m_dlValue > d;
}

int operator >( const CRound & c, const CRound & d )
{
    return c.m_dlValue > d.m_dlValue;
}

int operator >=( const CRound & c, double d )
{
    return c.m_dlValue >= d;
}

int operator >=( const CRound & c, const CRound & d )
{
    return c.m_dlValue > d.m_dlValue;
}

double CRound::_round( double d, int prec )
{
    double decimais  = d - ::floor( d );
    cint64 potenciaDez = 100;

    for( int n = 0; n < prec; n++ ) {
        potenciaDez *= 10;
    }
    cint64 round = (cint64)(decimais * potenciaDez);

    if(( round % 100 ) == 99 ) {
        round += 100;
    }
    round /= 100;

    return ::floor( d ) + ((double)round / ( potenciaDez / 100 ));
}

//   return CDouble( d ).floor( prec );

/*    static char format[30];
    static char result[30];

    sprintf( format, "%%.%df", prec );
    sprintf( result, format, d );
    return atof( result );*/
//}

