#ifndef _CDebug_H
#define _CDebug_H

/***************************************************************************

                          T I P O S    B A S I C O S

****************************************************************************/
class CStr;
class CDateTime;

/***************************************************************************

                     S U P O R T E     A    D E B U G

****************************************************************************/
#if defined( __CLASS_EXPORT )
   #define __External __declspec( dllexport )
#elif defined( __CLASS_IMPORT )
   #define __External __declspec( dllimport )
#else
   #define __External
#endif
enum _DebugMode {
    DMDisabled = 0,     // Debug Disabled
    DMEnabled = 1,      // Debug Enabled
    DMSuspended = 2     // Debug Suspended (without closeFile() )
};

/*
class (1)
    public (5)
        virtual (9)
                void (17)
                                Funcao (33)
*/
class __External CDebug
{
    public:
                                CDebug(const char* szArquivo);
        virtual                 ~CDebug();

                void            setDebugMode( _DebugMode );
                void            openFile();
                void            closeFile();
                void            put( const char * s );
                _DebugMode      getInDebugMode() const;

    protected:
                CDateTime       m_dtStartTime;
                CStr            m_szDebugFileName;
                CStr            m_szConfigFileName;
                _DebugMode      m_enInDebugMode; // enumeration 
                FILE*           m_hnFILE;

};

extern CDebug __Debug;
extern const char AppName[];

#ifdef DEBUG_MSG
#undef DEBUG_MSG
#endif

//#define DEBUG_MSG( msg ) if( __Debug.getInDebugMode()) __Debug.put( msg )
//#define DEBUG_MSG( msg ) if( __Debug.getInDebugMode()) { qDebug() << msg; __Debug.put( msg ); }
#define DEBUG_MSG( msg ) if( __Debug.getInDebugMode()) { qDebug() << msg; __Debug.put( msg ); } else { qDebug() << msg; }
#define Put( msg ) put( msg )

#endif
