#include "CDatatypes.h"

#ifdef WIN32
#include <windows.h>
#endif

#ifndef _WIN32_WCE
#pragma warning( push )
#endif
#pragma warning( disable : 4800 )

/***************************************************************************

                              V A R I A N T

****************************************************************************/

CVariant::~CVariant()
{
}

CVariant::CVariant()
{
    setEmpty(); 
    m_inType = 0; 
}

CVariant::CVariant( const bool b ) 
{ 
    setEmpty(); 
    m_inType = 0; 
    setBoolean( b ); 
}

CVariant::CVariant( const int n ) 
{ 
    setEmpty(); 
    m_inType = 0; 
    setInteger( n ); 
}

CVariant::CVariant( const double n ) 
{ 
    setEmpty(); 
    m_inType = 0; 
    setDouble( n ); 
}

CVariant::CVariant( const char * pc )
{
    setEmpty(); 
    m_inType = 0; 
    setString( pc ); 
}

CVariant::CVariant( const CStr & s ) 
{
    setEmpty(); 
    m_inType = 0; 
    setString( s ); 
}

CVariant::CVariant( const CDouble & n ) 
{
    setEmpty(); 
    m_inType = 0; 
    setDouble( n ); 
}

CVariant::CVariant( const CDateTime & dt ) 
{
    setEmpty(); 
    m_inType = 0; 
    setDateTime( dt ); 
}

CVariant::CVariant( const CBoolean & b ) 
{
    setEmpty(); 
    m_inType = 0; 
    setBoolean( b ); 
}

CVariant::CVariant( const CVariant & other ) 
{
    setEmpty(); 
    m_inType = 0; 
    copyFrom( other ); 
}

bool CVariant::compare( const CVariant & other ) const
{
    if( other.m_inType != m_inType )
        return false;

    switch( m_inType ) {
        case Type_Bool :
            return m_boBValue == other.m_boBValue;
            break;
        case Type_Int :
            return m_inIValue == other.m_inIValue;
            break;
        case Type_Double :
            return m_dlFValue == other.m_dlFValue;
            break;
        case Type_Str :
            return m_szSValue == other.m_szSValue ? true : false;
            break;
        default : 
            return false;
    }
}

bool CVariant::getBoolean() const
{
    switch(m_inType) {
        case Type_Bool :
            return m_boBValue;
            break;
        case Type_Int :
            return m_inIValue ? true : false;
            break;
        case Type_Double :
            return m_dlFValue ? true : false;
            break;
        case Type_Str :
            return m_szSValue.getBoolean();
            break;
        default :
            return false;
    }
}

CInteger CVariant::getInteger() const
{
    switch(m_inType ) {
        case Type_Int :
            return m_inIValue;
            break;
        case Type_Double :
            return (int)m_dlFValue;
            break;
        case Type_Str :
            return m_szSValue.getInteger();
            break;
        default :
            return 0;
    }
}

CDateTime CVariant::getDateTime() const
{
    CDateTime ret;

    switch( m_inType ) {
        case Type_DateTime :
            return m_dtDValue;
            break;
        case Type_Double :             
            ret.setJulianDay( m_dlFValue );
            return ret;
            break;
        case Type_Str :
            return m_szSValue.getDateTime();
            break;
        default:
            return CDateTime();
    }
}

CDouble CVariant::getDouble() const
{
    switch( m_inType ) {
        case Type_Double :
            return m_dlFValue;
            break;
        case Type_Int :
            return (double) m_inIValue;
            break;
        case Type_Str :
            return m_szSValue.getDouble();
            break;
        default :
            return 0.0;
    }
}

CStr CVariant::getString() const
{
    switch( m_inType ) {
        case Type_Str :
            return m_szSValue;
            break;
        case Type_Int :
            return CInteger( m_inIValue ).getString();
            break;
        case Type_Double :
            return CDouble( m_dlFValue ).getString();
            break;
        case Type_DateTime : 
            return m_dtDValue.format( "yyyy/mm/dd hh:nn:ss" );
            break;
        default :
            return "";
    }
}

void CVariant::copyFrom( const CVariant & other )
{
    setType( other.m_inType );
    
    switch( m_inType ) {
        case Type_Double :
            m_dlFValue = other.m_dlFValue;
            break;
        case Type_Bool :
            m_boBValue = other.m_boBValue;
            break;
        case Type_Int :
            m_inIValue = other.m_inIValue;
            break;
        case Type_Str :
            m_szSValue = other.m_szSValue;
            break;
        case Type_DateTime :
            m_dtDValue = other.m_dtDValue;
            break;
    }
}

bool CVariant::isNumericType() const
{
    if(( m_inType == Type_Int ) || m_inType == Type_Double )
        return true;

    return false;
}

void CVariant::setEmpty()
{
    m_boBValue = false;
    m_inIValue = 0;
    m_dlFValue = 0.0;
    m_szSValue.clear();
    m_dtDValue.setEmpty();
}

void CVariant::setString( const CStr & value )
{
   if( !m_inType )
      setType( Type_Str );

    switch( m_inType ) {
        case Type_Str :
            m_szSValue = value;
            break;
        case Type_Int :
            m_inIValue = value.getInteger();
            break;
        case Type_Double :
            m_dlFValue = value.getDouble();
            break;
        case Type_DateTime :
            m_dtDValue = value.getDateTime();
            break;
    }
}

void CVariant::setBoolean( bool value )
{
    if( !m_inType )
        setType( Type_Bool );

    switch( m_inType ) {
        case Type_Bool :
            m_boBValue = value;
            break;
        case Type_Int :
            m_inIValue = value ? 1 : 0;
            break;
        case Type_Double :
            m_dlFValue = value ? 1.0 : 0.0;
            break;
        case Type_Str :
            m_szSValue = value ? "1" : "0";
            break;
    }
}

void CVariant::setInteger( int value )
{
   if( !m_inType )
      setType( Type_Int );

    switch( m_inType ) {
        case Type_Int :
            m_inIValue = value;
            break;
        case Type_Double :
            m_dlFValue = value;
            break;
        case Type_Str :
            m_szSValue = CInteger( value ).getString();
            break;
   }
}

void CVariant::setDouble( double value )
{
   if( !m_inType )
      setType( Type_Double );

    switch( m_inType ) {
    case Type_Double :
        m_dlFValue = value;
        break;
    case Type_Int :
        m_inIValue = (long) value;
        break;
    case Type_Str :
        m_szSValue = CDouble( value ).format( "" );
        break;
    }
}

void CVariant::setDouble( const CDouble & value )
{
   if( !m_inType )
      setType( Type_Double );

    switch( m_inType ) {
        case Type_Double :
            m_dlFValue = value;
            break;
        case Type_Int :
            m_inIValue = (long) value;
            break;
        case Type_Str :
            m_szSValue = value.format( "" );
            break;
    }
}

void CVariant::setDateTime( const CDateTime & value )
{
   if( !m_inType )
      setType( Type_DateTime );

    if( m_inType == Type_DateTime )
      m_dtDValue = value;
}

void CVariant::changeType( int type )
{
    m_inType = type;
}

void CVariant::setType( int type )
{
    //setEmpty();
    if(m_inType != type) {
        switch(type) {
            case Type_Str:
                switch(m_inType) {
                    case Type_Str:
                        break;
                    case Type_DateTime:
                        m_szSValue = m_dtDValue.format("dd/mm/yyyy");
                        break;
                    case Type_Int:
                        m_szSValue = CInteger(m_inIValue).getString();
                        break;
                    case Type_Bool:
                        m_szSValue = CBoolean(m_boBValue).getString();
                        break;
                    case Type_Double:
                        m_szSValue = CDouble(m_dlFValue).getString();
                        break;
                }
                break;
            case Type_Int:
                switch(m_inType) {
                    case Type_Str:
                        m_inIValue = m_szSValue.getInteger();
                        break;
                    case Type_DateTime:
                        m_inIValue = (int)m_dtDValue.getJulianDay();
                        break;
                    case Type_Int:
                        break;
                    case Type_Bool:
                        m_inIValue = m_boBValue;
                        break;
                    case Type_Double:
                        m_inIValue = (int)m_dlFValue;
                        break;
                }
                break;

            case Type_Double:
                switch(m_inType) {
                    case Type_Str:
                        m_dlFValue = m_szSValue.getDouble();
                        break;
                    case Type_DateTime:
                        m_dlFValue = m_dtDValue.getJulianDay();
                        break;
                    case Type_Int:
                        m_dlFValue = m_inIValue;
                        break;
                    case Type_Bool:
                        m_dlFValue = m_boBValue;
                        break;
                    case Type_Double:
                        break;
                }
                break;

            case Type_Bool:
                switch(m_inType) {
                    case Type_Str:
                        m_boBValue = m_szSValue.getInteger();
                        break;
                    case Type_DateTime:
                        m_boBValue = (int)m_dtDValue.getJulianDay();
                        break;
                    case Type_Int:
                        m_boBValue = m_inIValue;
                        break;
                    case Type_Bool:
                        break;
                    case Type_Double:
                        m_boBValue = (int)m_dlFValue;
                        break;
                }
                break;

            case Type_DateTime:
                switch(m_inType) {
                    case Type_Str:
                        m_dtDValue = convertCStrToDateTime(m_szSValue);
                        break;
                    case Type_DateTime:
                        break;
                    case Type_Int:
                        m_dtDValue.setJulianDay((double)m_inIValue);
                        break;
                    case Type_Bool:
                        m_dtDValue.setJulianDay((double)m_boBValue);
                        break;
                    case Type_Double:
                        m_dtDValue = (int)m_dlFValue;
                        break;
                }
                break;
            default:
                break;
        }
    }
    m_inType = type;
}

void CVariant::setString( const int  n )
{
    char* pBuff = new char[ n + 1];

    memset(pBuff, 0, n+1 );
    memset(pBuff, 32, n );
    m_szSValue = pBuff;
}

void* CVariant::getAddress(UINT inTipo )
{
    void* lpVarAddr = 0;

    switch( inTipo ) {
        case Type_Str:
#ifdef WIN32
        lpVarAddr = (void*)(LPCSTR) m_szSValue;
#else
        lpVarAddr = (void*) m_szSValue;
#endif
            break;
        case Type_Int:
            lpVarAddr = (void*)&m_inIValue;
            break;
        case Type_Double:
            lpVarAddr = (void*)&m_dlFValue;
            break;
        case Type_Bool:
            lpVarAddr = (void*)&m_boBValue;
            break;
        default:
#ifdef WIN32
        lpVarAddr = (void*)(LPCSTR) m_szSValue;
#else
        lpVarAddr = (void*) m_szSValue;
#endif
    }
    return lpVarAddr;
}

#ifndef _WIN32_WCE
#pragma warning( pop )
#endif

