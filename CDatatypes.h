/***************************************************************************

   cdatatypes.h - Tipos basicos portaveis

****************************************************************************/

#ifndef __CDATATYPES_H  // Impede multiplas inclusoes
#define __CDATATYPES_H

#include <QApplication>
#include <QtMath>

//#include <stdlib.h>
//#include <string.h>
//#include <time.h>
//#include <math.h>
//#include <ctype.h>
//#include <stdio.h>
#ifdef _WIN32
//    #include <fcntl.h>
//    #include <errno.h>

//    #include <windows.h>       /* required for all Windows applications */
//    #include <winnt.h>
    #ifdef __PHACT_API
        #pragma message(" ==> Using a DLL Version of CDataTypes.")
        #ifndef _DEBUG
            #pragma comment (lib, "Phact.lib")
        #else
            #pragma comment (lib, "PhactD.lib")
        #endif
    #else
        #ifdef __DTSRC_
            #pragma message(" ==> Using a Source-Code Version of CDataTypes.")
        #else
            #pragma message(" ==> Using a DLL Version of CDataTypes.")
            #ifndef _DEBUG
                #pragma comment (lib, "Phact.lib")
            #else
                #pragma comment (lib, "PhactD.lib")
            #endif
        #endif
    #endif
#endif

#ifdef UNIX
#include <dirent.h>
#endif

/***************************************************************************

                          D E F I N I C O E S

****************************************************************************/
#if defined( __CLASS_EXPORT )
   #define __External __declspec( dllexport )
#elif defined( __CLASS_IMPORT )
   #define __External __declspec( dllimport )
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
    #define uint64 unsigned __int64
#else
    #define cint64 long long
    #define uint64 unsigned long long
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

int pstrnicmp( const char * pc1, const char * pc2, size_t size );

/***************************************************************************

                          T I P O S    B A S I C O S

****************************************************************************/


#include "CBooleanType.h"
#include "CDoubleType.h"
#include "CIntegerType.h"
#include "CRoundType.h"
#include "CStrType.h"
#include "CDateTimeType.h"
#include "CVariantType.h"
#ifdef _WIN32
    #ifndef _WIN32_WCE
        #include "CPFileType.h"
        #include "CFileListType.h"
/***************************************************************************
                     S U P O R T E     A     E R R O
****************************************************************************/
        #include "CError.h"

/***************************************************************************
                     S U P O R T E     A    D E B U G
****************************************************************************/
        #include "CDebug.h"
    #else
        #define DEBUG_MSG( msg ) 
    #endif // _WIN32_WCE
#else
    #include "CError.h"
    #include "CDebug.h"
    //#define DEBUG_MSG( msg )
#endif // _WIN32
#include "CLinkedList.h"

#endif

