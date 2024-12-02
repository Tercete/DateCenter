
#include "CDatatypes.h"

#ifdef WIN32
#include <windows.h>
#endif

// Compara dois ponteiros para string (case insensitive)
int pstrnicmp( const char * pc1, const char * pc2, size_t size )
{
#ifdef _UNICODE
    while( size-- && *pc1 && *pc2 && (towupper( *pc1 ) == towupper( *pc1 ))) {
#else
    while( size-- && *pc1 && *pc2 && (toupper( *pc1 ) == toupper( *pc1 ))) {
#endif
        pc1++;
        pc2++;
    }
#ifdef _UNICODE
    if( !size && (towupper( *pc1 ) == towupper( *pc1 ))) {
#else
    if( !size && (toupper( *pc1 ) == toupper( *pc1 ))) {
#endif
        return 0;
    }
    return 1;
}

#ifdef __PHACT_API
    #include "CBooleanType.cpp"
    #include "CIntegerType.cpp"
    #include "CDoubleType.cpp"
    #include "CRoundType.cpp"
    #include "CStrType.cpp"
    #include "CDateTimeType.cpp"
    #include "CVariantType.cpp"
    #ifdef _WIN32
        #ifndef _WIN32_WCE
            #include "CPFileType.cpp"
            #include "CFileListType.cpp"
        #endif
    #endif
    #include "CError.cpp"
    #include "CDebug.cpp"
#else
    #ifdef __DTSRC_
        #include "CBooleanType.cpp"
        #include "CIntegerType.cpp"
        #include "CDoubleType.cpp"
        #include "CRoundType.cpp"
        #include "CStrType.cpp"
        #include "CDateTimeType.cpp"
        #include "CVariantType.cpp"
        #ifdef _WIN32
            #ifndef _WIN32_WCE
                #include "CPFileType.cpp"
                #include "CFileListType.cpp"
            #endif
        #endif
        #include "CError.cpp"
        #include "CDebug.cpp"
    #else
        #pragma message(" ==> Using a DLL Version of CDataTypes.")
    #endif
#endif // __PHACT_API

