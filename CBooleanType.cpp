#include "CDatatypes.h"

#ifdef WIN32
#include <windows.h>
#endif


CBoolean::CBoolean()
{
    m_boValue = false; 
}

CBoolean::CBoolean(const bool b)
{
    m_boValue = b; 
}

CBoolean::CBoolean( const CBoolean & other )
{ 
    m_boValue = other.m_boValue; 
}

CBoolean::~CBoolean()
{
}

CBoolean & CBoolean::operator=( const CVariant & v )
{
   m_boValue = v.getBoolean();
   return *this;
}

CStr CBoolean::getString() const
{
    return CStr( m_boValue ? "VERDADEIRO" : "FALSO" );
}

CBoolean::operator bool() const 
{ 
    return m_boValue; 
}

CBoolean & CBoolean::operator=( bool b )
{
    m_boValue = b; 
    return *this; 
}

CBoolean & CBoolean::operator=( const CBoolean & other ) 
{ 
    m_boValue = other.m_boValue; 
    return *this; 
}


