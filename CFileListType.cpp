#include "CDatatypes.h"

#ifdef WIN32
#include <windows.h>

CFileList::CFileList()
{
    m_EOF = true;
    m_hFile = 0;
    m_findFileData = new char[ sizeof( WIN32_FIND_DATA ) ];
    memset( m_findFileData, 0, sizeof( WIN32_FIND_DATA ));
}

CFileList::CFileList( const CStr & dirName )
{
    m_EOF = true;
    m_hFile = 0;
    m_findFileData = new char[ sizeof( WIN32_FIND_DATA ) ];
    memset( m_findFileData, 0, sizeof( WIN32_FIND_DATA ));

    open( dirName );
}

CFileList::~CFileList()
{
    FindClose( m_hFile );
    delete m_findFileData;
}

void CFileList::open( const CStr & dirName )
{
    CStr    szTemp = dirName + "*.*";

#ifdef UNICODE
    m_hFile = FindFirstFile( (wchar_t *)((LPCSTR)szTemp), (LPWIN32_FIND_DATA) m_findFileData );
#else
    m_hFile = FindFirstFile( (LPCSTR)szTemp, (LPWIN32_FIND_DATA) m_findFileData );
#endif

    if( m_hFile != INVALID_HANDLE_VALUE ) {
        m_EOF = false;
    }
}

bool CFileList::isEOF()
{
    return m_EOF;
}

void CFileList::moveNext()
{
    if( !m_EOF ) {
        if( !FindNextFile( m_hFile, (LPWIN32_FIND_DATA) m_findFileData )) {
            m_EOF = true;
        }
    }
}

CStr CFileList::getFileName()
{
    return (char*)(((LPWIN32_FIND_DATA) m_findFileData)->cFileName);
}

bool CFileList::isDirectory()
{
    return (((LPWIN32_FIND_DATA) m_findFileData)->dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) ? true : false;
}

bool CFileList::isReadOnly()
{
    return (((LPWIN32_FIND_DATA) m_findFileData)->dwFileAttributes & FILE_ATTRIBUTE_READONLY) ? true : false;
}

bool CFileList::isHidden()
{
    return (((LPWIN32_FIND_DATA) m_findFileData)->dwFileAttributes & FILE_ATTRIBUTE_HIDDEN) ? true : false;
}

int CFileList::getLenght()
{
    return ((LPWIN32_FIND_DATA) m_findFileData)->nFileSizeLow;
}

CDateTime CFileList::getCreationTime()
{
    SYSTEMTIME systemTime;

    FileTimeToSystemTime(&((LPWIN32_FIND_DATA) m_findFileData)->ftCreationTime, &systemTime );

    return CDateTime( systemTime.wYear, systemTime.wMonth, systemTime.wDay,
        systemTime.wHour, systemTime.wMinute, systemTime.wSecond );
}

CDateTime CFileList::getLastAccessTime()
{
    SYSTEMTIME systemTime;

    FileTimeToSystemTime(&((LPWIN32_FIND_DATA) m_findFileData)->ftLastAccessTime, &systemTime );

    return CDateTime( systemTime.wYear, systemTime.wMonth, systemTime.wDay,
        systemTime.wHour, systemTime.wMinute, systemTime.wSecond );
}

#endif

#ifdef _UNIX 

CFileList::CFileList()
{
    m_EOF = true;
    m_hFile = 0;
    m_findFileData = new char[ sizeof( WIN32_FIND_DATA ) ];
    memset( m_findFileData, 0, sizeof( WIN32_FIND_DATA ));
}

CFileList::CFileList( const CStr & dirName )
{
    m_EOF = true;
    m_hFile = 0;
    m_findFileData = new char[ sizeof( WIN32_FIND_DATA ) ];
    memset( m_findFileData, 0, sizeof( WIN32_FIND_DATA ));

    open( dirName );
}

CFileList::~CFileList()
{
    FindClose( m_hFile );
    delete m_findFileData;
}

void CFileList::open( const CStr & dirName )
{
    m_nomeDir    = dirname;
    m_ent = readdir( dirName );

    if( m_ent != NULL ) {
        m_EOF = false;
    }
}

bool CFileList::isEOF()
{
    return m_EOF;
}

void CFileList::moveNext()
{
    if( !m_EOF ) {
        open ( m_nomeDir );
    }
}

CStr CFileList::getFileName()
{
    return m_ent->d_name;
}

bool CFileList::isDirectory()
{
    return (((LPWIN32_FIND_DATA) m_findFileData)->dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) ? true : false;
}

bool CFileList::isReadOnly()
{
    return (((LPWIN32_FIND_DATA) m_findFileData)->dwFileAttributes & FILE_ATTRIBUTE_READONLY) ? true : false;
}

bool CFileList::isHidden()
{
    return (((LPWIN32_FIND_DATA) m_findFileData)->dwFileAttributes & FILE_ATTRIBUTE_HIDDEN) ? true : false;
}

int CFileList::getLenght()
{
    return ((LPWIN32_FIND_DATA) m_findFileData)->nFileSizeLow;
}

CDateTime CFileList::getCreationTime()
{
    SYSTEMTIME systemTime;

    FileTimeToSystemTime(&((LPWIN32_FIND_DATA) m_findFileData)->ftCreationTime, &systemTime );

    return CDateTime( systemTime.wYear, systemTime.wMonth, systemTime.wDay,
        systemTime.wHour, systemTime.wMinute, systemTime.wSecond );
}

CDateTime CFileList::getLastAccessTime()
{
    SYSTEMTIME systemTime;

    FileTimeToSystemTime(&((LPWIN32_FIND_DATA) m_findFileData)->ftLastAccessTime, &systemTime );

    return CDateTime( systemTime.wYear, systemTime.wMonth, systemTime.wDay,
        systemTime.wHour, systemTime.wMinute, systemTime.wSecond );
}

#endif    

