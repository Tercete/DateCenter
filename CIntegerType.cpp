#include "CDatatypes.h"

#ifdef WIN32
#include <windows.h>
#endif

CInteger::~CInteger()
{
}

CInteger::CInteger()
{
    m_inValue = 0; 
}

CInteger::CInteger( const int n )
{ 
    m_inValue = n; 
}

CInteger::CInteger( const CInteger & other )
{
    m_inValue = other.m_inValue; 
}

/********************************************************************
 Proposito:    converte um inteiro em hexadecimal
 Retorno:    String com o valor convertido
 *******************************************************************/
CStr CInteger::getHex() const
{
    char result[20];
//#ifdef UNICODE
//    wsprintf( (wchar_t *)result, (wchar_t*)"%X", m_inValue );
//#else
    sprintf( result, "%X", m_inValue );
//#endif
    return CStr( result );
}

/********************************************************************
 Proposito:    Converte um inteiro em uma String
 Retorno:    String convertida
 *******************************************************************/
CStr CInteger::getString() const
{
    return format( "" );
}

/********************************************************************
 Proposito:  Formata um numero inteiro, convertendo para String
 Parametros: format - formato da string
             verificar formatacoes do printf
 Retorno:    String formatada
 Exemplo:    Exemplos de formatacao para o numero 347:

             Format( "05" )   ->   retorna "00347"
             Format( " 5" )   ->   retorna "  347"
             Format( "+2" )   ->   retorna "+347"
********************************************************************/
CStr CInteger::format( const char * format ) const
{
    static char result[30];

    // determina quantos digitos a esquerda e a direta do numero
    const char * cCount = format;
    int nums = 0;
    int integers = 0;
    int decimals = 0;
    bool inDecimal = false;
    bool allowIncrease = false;

    CStr formatPrintf = "%" + CStr( format ) + "d";
//#ifdef UNICODE
//    wsprintf( (wchar_t *) result, (wchar_t *)((char*)formatPrintf), m_inValue );
//#else
    sprintf( result, (char*)formatPrintf, m_inValue );
//#endif
    return result;
}

