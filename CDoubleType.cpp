#include "CDatatypes.h"

#ifdef WIN32
#include <windows.h>
#endif

//////////////////////////////////////////////////////////////////////////////
// CDouble
//

CDouble::CDouble()
{
    m_dlValue = 0; 
}

CDouble::CDouble( const double n )
{
    m_dlValue = n; 
}

CDouble::CDouble( const CDouble & other )
{
    m_dlValue = other.m_dlValue; 
}

CDouble::~CDouble()
{
}

CStr CDouble::getExtent1To999( double value, const CStr& lang ) const
{
    CStr ret;

    if(lang == "BRL") {
        static char * table100[] = { "Cem" };
        static char * table100To900[] = { "Cento", "Duzentos", "Trezentos", "Quatrocentos",
            "Quinhentos", "Seiscentos", "Setecentos", "Oitocentos", "Novecentos" };
        static char * table20To90[] = { "Vinte", "Trinta", "Quarenta",
            "Cinqüenta", "Sessenta", "Setenta", "Oitenta", "Noventa" };
        static char * table1To19[] = { "Um", "Dois", "Três", "Quatro",
            "Cinco", "Seis", "Sete", "Oito", "Nove", "Dez", "Onze", "Doze",
            "Treze", "Quatorze", "Quinze", "Dezesseis", "Dezessete", "Dezoito",
            "Dezenove" };

        if( value < 1000.0 ) {
            // verifica as centenas
            int num = (int)(value / 100.0);

            if( num > 0 ) {
                if((int) value == 100 )
                    ret += table100[ 0 ];
                else
                    ret += table100To900[ num - 1 ];
            }
            value -= num * 100;

            // verifica as dezenas
            num = (int)(value / 10.0);

            // se o valor é maior que 20, coloca dezenas + unidades
            if( num >= 2 ) {
                if( ret != "" )
                    ret += " e ";

                ret += table20To90[ num - 2 ];
             value -= num * 10;

             // verifica a unidade
             num = (int)(value);
       
             if( num > 0 ) {
                    if( ret != "" )
                        ret += " e ";

                    ret += table1To19[ num - 1 ];
                }
            }
          else {
             // valor entre 1 e 19
             num = (int) value;

                if( num >= 1 && num <= 19 ) {
                    if( ret != "" )
                        ret += " e ";

                    ret += table1To19[ num - 1 ];
                }
            }     
        }
    }
    else if(lang == "ENG") {
        static char * table100[] = { "Hundred" };
        static char * table100To900[] = { "One Hundred","Two Hundred", "Three Hundred", "Four Hundred",
            "Five Hundred", "Six Hundred", "Seven Hundred", "Eight Hundred", "Nine Hundred" };
        static char * table20To90[] = { "Twenty", "Thirth", "forty",
            "fifty", "Sixty", "Seventy", "Eighty", "Ninety" };
        static char * table1To19[] = { "One","Two", "Three", "Four",
            "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Eleven", "Twelve",
            "Thirteen", "Fourteen", "Fiveteen", "Sixteen", "Seventeen", "Eighteen",
            "Nineteen" };

        if( value < 1000.0 ) {
            // verifica as centenas
            int num = (int)(value / 100.0);

            if( num > 0 ) {
                if((int) value == 100 )
                    ret += table100[ 0 ];
                else
                    ret += table100To900[ num - 1 ];
            }
            value -= num * 100;

            // verifica as dezenas
            num = (int)(value / 10.0);

            // se o valor é maior que 20, coloca dezenas + unidades
            if( num >= 2 ) {
                if( ret != "" )
                    ret += " ";

                ret += table20To90[ num - 2 ];
             value -= num * 10;

             // verifica a unidade
             num = (int)(value);
       
             if( num > 0 ) {
                    if( ret != "" )
                        ret += " ";

                    ret += table1To19[ num - 1 ];
                }
            }
          else {
             // valor entre 1 e 19
             num = (int) value;

                if( num >= 1 && num <= 19 ) {
                    if( ret != "" )
                        ret += " ";

                    ret += table1To19[ num - 1 ];
                }
            }     
        }
    }
   return ret;
}

/********************************************************************
 Proposito:    Retorna o valor absoluto do numero
 Retorno:   valor absoluto
********************************************************************/
CDouble CDouble::getAbs() const
{
    if( m_dlValue < 0 )
         return -m_dlValue;

    return m_dlValue;
}

/********************************************************************
 Proposito:     Arredonda um numero
 Parametros: decimalPlaces - quantidade de casa decimais
 Retorno:    valor arrendondado
********************************************************************/
CDouble CDouble::round( int precision ) const
{
    return format( "." + CInteger( precision ).getString()).getDouble();
}

/********************************************************************
 Proposito:     Arredonda um numero para cima
 Parametros: decimalPlaces - quantidade de casa decimais
 Retorno:    valor arrendondado
********************************************************************/
CDouble CDouble::ceil( int precision ) const
{
    return ::ceil(m_dlValue*pow(static_cast<double>(10),precision))/pow(static_cast<double>(10),precision);
}
        
/********************************************************************
 Proposito:     Arredonda um numero para baixo
 Parametros: decimalPlaces - quantidade de casa decimais
 Retorno:    valor arrendondado
********************************************************************/
CDouble CDouble::floor( int precision ) const
{
    return ::floor(m_dlValue*pow(static_cast<double>(10),precision))/pow(static_cast<double>(10),precision);
}

/********************************************************************
 Proposito:     Retorna uma String com o valor por extenso
 Parametros: language - idioma do valor por extenso:
             "BRL" : Portugues do Brasil
 Retorno:    String com valor por extenso
********************************************************************/
CStr CDouble::getExtent( const char* lang ) const
{
    CStr ret;
    CStr language(lang);
    double value = m_dlValue;

    if( language == "BRL" ) {
        if( value >= 1000000000.0 )
            return "***Erro*** Valor muito grande";

        // verifica os milhões
        if( value >= 2000000.0 ) {
            ret = getExtent1To999( value / 1000000.0, language ) + " Milhões, ";
            value -= ::floor( value / 1000000.0 ) * 1000000.0;
        }
        else if( value >= 1000000.0 ) {
            ret = getExtent1To999( value / 1000000.0, language ) + " Milhão, ";
            value -= ::floor( value / 1000000.0 ) * 1000000.0;
        }
        // verifica os milhares
        if( value > 1000.0 ) {
            CStr result = getExtent1To999( value / 1000.0, language );

            if( result != "" )
                ret += result + " Mil";

                value -= int( value / 1000.0 ) * 1000.0;
         }
        // verifica as centenas
        if( value > 0 ) {
            if( ret != "" )
                ret += " e ";

            ret += getExtent1To999( value, language );
            value -= int( value );
        }
        if( ret != "" ) {
            if(m_dlValue >= 1.00 && m_dlValue < 2.00) {
                ret += " Real";
            } else {
                ret += " Reais";
            }
        }

        // verifica os centavos
        if( value > 0 ) {
            if( ret != "" )
                ret += " e ";

            // essa parafernália de double é para arredondar...
            double cents = CDouble( value ).format( ".2" ).getDouble() * 100;
            ret += getExtent1To999( cents, language );

            if( cents == 1.0 )
                ret += " Centavo";
            else
                ret += " Centavos";
        }
    }
    else if(language == "ENG") {
        if( value >= 1000000000.0 )
            return "***Error*** Very Large Value";

        // verifica os milhões
        if( value >= 2000000.0 ) {
            ret = getExtent1To999( value / 1000000.0, language ) + " Millions, ";
            value -= ::floor( value / 1000000.0 ) * 1000000.0;
        }
        else if( value >= 1000000.0 ) {
            ret = getExtent1To999( value / 1000000.0, language ) + " Million, ";
            value -= ::floor( value / 1000000.0 ) * 1000000.0;
        }
        // verifica os milhares
        if( value > 1000.0 ) {
            CStr result = getExtent1To999( value / 1000.0, language );

            if( result != "" )
                ret += result + " Thousand";

                value -= int( value / 1000.0 ) * 1000.0;
         }
        // verifica as centenas
        if( value > 0 ) {
            if( ret != "" )
                ret += " and ";

            ret += getExtent1To999( value, language );
            value -= int( value );
        }
        if( ret != "" )
            if(m_dlValue >= 1.00 && m_dlValue < 2.00) {
                ret += " Dollar";
            } else {
                ret += " Dollars";
            }

        // verifica os centavos
        if( value > 0 ) {
            if( ret != "" )
                ret += " and ";

            // essa parafernália de double é para arredondar...
            double cents = CDouble( value ).format( ".2" ).getDouble() * 100;
            ret += getExtent1To999( cents, language );

            if( cents == 1.0 )
                ret += " Cent";
            else
                ret += " Cents";
        }
    }
    return ret;
}

/********************************************************************
 Proposito:    Converte um double para string
 Retorno:   String convertida
 ********************************************************************/
CStr CDouble::getString() const
{
    return format( "" );
}

/********************************************************************
 Proposito:     Formata um numero double, convertendo para string
 Parametros: format - formatacao de numero:
             verificar paramentros do printf para double
 Retorno:    String formatada
 Exemplo:    Exemplos de formatacao para o numero 34.567:

             Format( ".2" )     ->   retorna "34.57"
             Format( "04.4" )   ->   retorna "0034.5700"
********************************************************************/
CStr CDouble::format( const char * format ) const
{
    static char result[30];

    // determina quantos digitos a esquerda e a direta do numero
    const char * cCount = format;
    int nums = 0;
    int integers = 0;
    int decimals = 0;
    bool inDecimal = false;
    bool allowIncrease = false;

    CStr formatPrintf = "%" + CStr( format ) + "f";
//#ifdef UNICODE
//    wsprintf( (wchar_t *)result, (wchar_t *)((LPCSTR)formatPrintf), m_dlValue );
//#else
    sprintf( result, (char*)formatPrintf, m_dlValue );
//#endif
    return result;
}

CDouble operator ^( const CDouble & b,  const CDouble & e )
{
    return pow( b, e );
}

CDouble operator ^( const CDouble & b,  const CInteger & e )
{
    return pow( b, e );
}

int operator ==( const CDouble & c, const CDouble & d )
{
    return c.m_dlValue == d.m_dlValue;
}

int operator ==( const CDouble & c, double d )
{
    return c.m_dlValue == d;
}

int operator ==( double  c, const CDouble &d )
{
    return c == d.m_dlValue;
}

int operator !=( const CDouble & c, const CDouble & d )
{
    return c.m_dlValue != d.m_dlValue;
}

int operator !=( const CDouble & c, double d )
{
    return c.m_dlValue != d;
}

int operator !=( double  c, const CDouble &d )
{
    return c != d.m_dlValue;
}

