
//#ifndef _CDebug_H

#include "CDatatypes.h"

CDebug::CDebug(const char* szArquivo)
{
    CStr    szBufferTmp;
    m_enInDebugMode = DMDisabled;
    m_szDebugFileName = szArquivo;
    m_szDebugFileName += ".log";
    m_szConfigFileName = szArquivo;
    m_szConfigFileName += ".ini";
    m_hnFILE = NULL;

    FILE * hnFileTmp;
    if((hnFileTmp = fopen(m_szConfigFileName,"r" )) == NULL) {
        m_enInDebugMode = DMDisabled;
        return;
    }
    if( hnFileTmp != NULL ) { 
        char    szBuffer[20];
        int        inQtde = 0;

        while( !feof(hnFileTmp )) {
            inQtde = fread( szBuffer, 1, 13, hnFileTmp );            

            if( inQtde < 10 )
                break;

            szBufferTmp = szBuffer;

            if( strncmp(szBufferTmp.getUpperCase(), "DEBUGMODE=", 10 ) == 0) {
                setDebugMode(szBufferTmp.getMid(10, 1) == "1" ? DMEnabled : DMDisabled );
                break;
            }
        }
        fclose( hnFileTmp );
    }
}

void CDebug::setDebugMode( _DebugMode mode)
{
    if(mode == DMSuspended || m_enInDebugMode == DMSuspended) {
        m_enInDebugMode = mode;
        return;
    }
    if( mode != m_enInDebugMode ) {
        m_enInDebugMode = mode;
        openFile();
    }
}

void CDebug::openFile()
{
    closeFile();

    if( m_enInDebugMode == DMEnabled ) {
        m_hnFILE = fopen( m_szDebugFileName, "a+" );

        if( m_hnFILE ) {
            m_dtStartTime = CDateTime().getNow();
            CStr result = "==============================================================================\r\nLog de Atividades\r\n" +
                m_dtStartTime.format( "dddd, dd \\d\\e mmmm \\d\\e yyyy" ) + "\r\nInicio do log as " +
                m_dtStartTime.format( "hh:nn:ss" ) + " hs \r\n\r\n";
            fputs( result, m_hnFILE );
        }
    }
}

CDebug::~CDebug()
{
    closeFile();
}

void CDebug::closeFile()
{
    if( m_hnFILE ) {
        CDateTime endTime = CDateTime().getNow();
        CDateTime elapsed = endTime - m_dtStartTime;
            CStr result = "\r\nTermino as " + endTime.format( "hh:nn:ss" ) + " hs\r\nTempoTotal " +
                elapsed.format( "hh:nn:ss" ) + "\r\n\r\n";

        fputs( result, m_hnFILE );
        fclose( m_hnFILE );
        m_hnFILE = NULL;
    }
}

_DebugMode CDebug::getInDebugMode() const 
{ 
    return m_enInDebugMode; 
}

void CDebug::put( const char * s )
{
    if( m_enInDebugMode != DMEnabled)
        return;

    CStr result = CDateTime().getNow().format( "hh:nn:ss   " ) + CStr( s ) + "\r\n";

    if( m_hnFILE ) {
        fputs( result, m_hnFILE );
        fflush( m_hnFILE );
    }
}

//#define CDebug::Put( s ) CDebug::put( s )

//#else

//#define DEBUG_MSG( msg ) 

//#endif

