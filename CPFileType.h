/***************************************************************************

   cdatatypes.h - Tipos basicos portaveis

****************************************************************************/

#ifndef __CPFILETYPE_H  // Impede multiplas inclusoes
#define __CPFILETYPE_H

#include <io.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <ctype.h>
#include <stdio.h>
#ifdef _WIN32
  #include <fcntl.h>
  #include <errno.h>
  #include <sys/stat.h>
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

#ifndef MAX_INT 
#define MAX_INT 2147483647
#endif

#ifndef MAX_SIZE
#define MAX_SIZE        512
#endif

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


/*
class (1)
    public (5)
        virtual (9)
                void (17)
                                 Funcao (33)
*/
class __External CPFile {
    public:
        /*
        enum EOpenMode {
            ReadOnly,
            Write,
            CreateAndWrite,
            TruncateAndWrite
        } ; */

        enum EOpenMode {
            Append = _O_APPEND, 
            WrOnly = _O_WRONLY,
            RdOnly = _O_RDONLY,
            Binary = _O_BINARY,
            Create = _O_CREAT,
            ReadWr = _O_RDWR,
            Trunc  = _O_TRUNC,
            Text   = _O_TEXT
        };

        virtual bool            isEnd();
        virtual CStr            getFileName() const; 
        virtual int             getPos() const;
        virtual void            close();
        virtual void            remove();
        virtual CStr            getLine();
        virtual void            open();
        virtual void            open( const CStr & fileName, int mode = RdOnly );
        virtual int             read( void * buf , int size );
        virtual void            clear();
        virtual void            moveTo( int seekPos );
        virtual void            skip( int offset );
        virtual void            rename( const CStr & newName );
        virtual void            write( const void * buf, int size );
        virtual void            append( const CStr & text );

                                CPFile();
                                CPFile( const CStr & fileName, int mode = RdOnly );
        virtual                 ~CPFile();

    protected:
                bool            End;
                int             Stream;
                int             OpenMode;
                CStr            FileName;

                void            error();
};

#endif

