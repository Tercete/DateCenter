/***************************************************************************

   cdatatypes.h - Tipos basicos portaveis

****************************************************************************/

#ifndef __CFILELISTTYPE_H  // Impede multiplas inclusoes
#define __CFILELISTTYPE_H

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


/***************************************************************************

                          T I P O S    B A S I C O S

****************************************************************************/

class CStr;
class CDateTime;



/*
class (1)
    public (5)
        virtual (9)
                void (17)
                                Funcao (33)
*/
class __External CFileList {
    public :
                                CFileList();
                                CFileList( const CStr & dirName );
        virtual                 ~CFileList();

                void            open( const CStr & dirName );
                bool            isEOF();
                void            moveNext();

                CStr            getFileName();
                bool            isDirectory();
                bool            isReadOnly();
                bool            isHidden();
                int             getLenght();
                CDateTime       getCreationTime();
                CDateTime       getLastAccessTime();

    protected:
                bool            m_EOF;
#ifdef WIN32
                void *          m_hFile;
                void *          m_findFileData;
#endif
#ifdef UNIX
                DIR           * m_dir
                struct dirent * m_ent;
                CStr            m_nomeDir ;

                void *          m_hFile;
                void *          m_findFileData;

#endif
};

#endif

