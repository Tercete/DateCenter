#include "CDatatypes.h"

#ifdef WIN32
#include <windows.h>
#endif

CError::CError( int id, const char * msg, const char * fileName, int lineNumber )
{ 
    m_Id = id; 
    m_Msg = msg; 
    m_FileName = fileName; 
    m_LineNumber = lineNumber; 
}

CError::~CError()
{
}

CStr CError::getMsg() const 
{ 
    return m_Msg; 
}

int  CError::getErrorCode() const 
{ 
    return m_Id; 
}

CStr CError::getFileName() const
{
    return m_FileName;
}

int  CError::getLineNumber() const
{
    return m_LineNumber;
}

