#include "CDatatypes.h"

#ifdef WIN32
#include <windows.h>
#endif

#ifdef _DEBUG
#pragma warning( disable : 4244 )
#endif

//////////////////////////////////////////////////////////////////////////////
// Str
//
CStr operator +( const char * pc, const CStr & s )
{
    return CStr( pc ) + s;
}

CStr operator+( const char * pc, const CInteger & value )
{
    return CStr( pc ) + value.getString();
}

int operator == ( const CStr & str1, const CStr & str2 )
{
    return str1.compare( str2 ) == 0;
}

int operator == ( const CStr & s, const char * pc )
{
    return s.compare( pc ) == 0;
}

int operator == ( const char * pc, const CStr & s )
{
    return s.compare( pc ) == 0;
}

int operator !=( const CStr & s, const char * pc )
{
    return s.compare( pc ) != 0;
}

int operator !=( const CStr & str1, const CStr & str2 )
{
    return str1.compare( str2 ) != 0;
}

/* _StrRef: classe auxiliar de CStr para suporte a propagacao
   de string e copy-on-write */
CStr::_StrRef::_StrRef( const char * pc, unsigned int size )
{
    m_inConnections = 0;
    m_szValue = 0;
    m_inSize = 0;

    if( pc && size > 0 ) {
        m_szValue = new char[ size + 1 ];
        m_inSize = size;
        memcpy( m_szValue, pc, size );
       *( m_szValue + m_inSize ) = '\0';             // Forca terminacao nula
    }
}

CStr::_StrRef::_StrRef( unsigned int size )
{
    m_inConnections = 0;
    m_szValue = 0;
    m_inSize = 0;
    m_szValue = new char[ size + 1 ];

    m_inSize = size;
    memset( m_szValue, 0, size + 1 );
}

CStr::_StrRef::~_StrRef()
{
    delete m_szValue;
}

CStr::CStr( const char * pc )
{
    if( pc )
        m_pStrRef = new _StrRef( pc, strlen( pc ));
    else
        m_pStrRef = 0;
}

CStr::CStr( const char * pc, int size )
{
    if( pc )
        m_pStrRef = new _StrRef( pc, size );
    else
        m_pStrRef = 0;
}

CStr::CStr( const unsigned char * pc )
{
    if( pc )
        m_pStrRef = new _StrRef( (char*) pc, strlen((char*) pc ));
    else
        m_pStrRef = 0;
}

void CStr::destroyStrRef()
{
    if( m_pStrRef ) {
        if( m_pStrRef->m_inConnections )
            m_pStrRef->m_inConnections--;
        else
            delete m_pStrRef;
        m_pStrRef = 0;
    }
}

void CStr::createStrRef( const char * pc, unsigned int size )
{
    destroyStrRef();
    m_pStrRef = new _StrRef( pc, size );
}

void CStr::createStrRef( unsigned int size )
{
    destroyStrRef();
    m_pStrRef = new _StrRef( size );
}

void CStr::createStrRef( const CStr & s )
{
    if( m_pStrRef != s.m_pStrRef ) {
        destroyStrRef();

        m_pStrRef = s.m_pStrRef;

      if( m_pStrRef )
         m_pStrRef->m_inConnections++;
    }
}

void CStr::copyStrRef()
{
    if( m_pStrRef && m_pStrRef->m_inConnections ) {
        m_pStrRef->m_inConnections--;

        if( m_pStrRef->m_szValue )
            m_pStrRef = new _StrRef( m_pStrRef->m_szValue, strlen( (char*)m_pStrRef->m_szValue ));
        else
            m_pStrRef = new _StrRef( 0 );
    }
}

/********************************************************************
 Proposito:    Remove a string da memoria deixando o valor nulo
********************************************************************/
void CStr::clear()
{
    destroyStrRef();
}

int getHashCode( const char * pc )
{
    int res = 0;
    int n = 0;
    register int v = *pc;

    while( v ) {
        v = pc[n];
        res += v * v * v * n + v;
        n++;
    }
    return res;
}

/********************************************************************
 Proposito:    Criar um HashCode para a String
 Retorno:    Inteiro com o valor do Hash Code
********************************************************************/
CInteger CStr::getHashCode() const 
{
    if( !getLen())
        return 0;

    return ::getHashCode( m_pStrRef->m_szValue );
}


/********************************************************************
 Proposito:     Compara uma String com outra
 Parametros: pc1 - string a ser comparada
 Retorno:    = 0 se as strings forem iguais
             < 0 se a string for menor que pc1
             > 0 se a string for maior que pc1
********************************************************************/
int CStr::compare( const char * pc1 ) const
{
    if( !pc1 && !getLen())
        return 0;

    if( !pc1 )
        return -1;

    if( !getLen())
        return strlen( pc1 ) == 0 ? 0 : 1;

    return strcmp( pc1, (char*)m_pStrRef->m_szValue );
}

CStr CStr::format( const char* format, ... )
{
    //int len = strlen( format );

    //if( len ) {
    //    int formatCount = 0;
    //    int textCount = 0;

    //    CStr ret = format;

    //    while( formatCount < len ) {
    //        char f = format[ formatCount ];
    //        char t = format[ textCount ];

    //        // verifica formato numérico
    //        if( f == '0' ) {
    //            // se caracter não é válido, coloca zero '0' no lugar
    //            ret[ formatCount ] = ( t >= '0' && t <= '9' ) ? t : '0';
    //            textCount++;
    //        }
    //        formatCount++;
    //    }
    //    return ret;
    //}
    //return *this;

    if( format != NULL ) {
        va_list	args;
        char	szBuf[32675];

        va_start( args, format );
        vsprintf( szBuf, format, args );
        va_end( args );
        return CStr(szBuf);
    }
    return CStr("");
}

/***********************************************************************
 Proposito:  Verifica se a string faz parte de um dominio. Em geral
             esta funcao substituir uma sequencia de condicoes do tipo
             if( str == "nn" || str == "mm" || str == "xx" )    por
             if( str.isInDomain( "nn,mm,xx" ))

 Parametros: domain         - dominio, com os item separados 
             elemSeparator  - separador dos itens, o padrao e' o caracter
             virgula
 Retorno:    true se a string pertence ao dominio, false caso contrario
***********************************************************************/
bool CStr::isInDomain( const char * domain, const char * elemSeparator ) const
{
    int size;

    int pos = 0;
    CStr sdomain( domain );

    while( pos < sdomain.getLen()) {
        size = sdomain.find(elemSeparator, pos + 1);
        size = ((size == -1) ? (sdomain.getLen() - pos) : (size - pos));
        if( sdomain.getMid(pos, size) == *this) {
            return true;
        }
        pos = sdomain.find(elemSeparator, pos + 1);
        pos = ((pos == -1) ? (sdomain.getLen() + 1) : (pos + 1));
    }
    return false;
}

/********************************************************************
 Proposito:     Procura um texto do fim para o comeco da string
 Parametros: toFind - texto a ser pesquisado
             pos    - posicao inicial da procura na string 
             ignoreCase - se true faz uma pesquisa "case-insensitive"
 Retorno:     posicao na string onde o texto foi encontrado ou -1 se nao
             achou o texto
********************************************************************/
CInteger CStr::findFromBack( const char * toFind, int pos, bool ignoreCase ) const
{
    int last = getLen();

   if( !getLen() || pos < 0 )
        return -1;

    if( pos > last )
        pos = last;

    int ret;

   while( last >= pos ) {
        if(( ret = find( toFind, last, ignoreCase )) != -1 ) {
            return ret;
      }
      last--;
   }
    return -1;
}

/********************************************************************
 Proposito:     Procura um texto na string
 Parametros: toFind - texto a ser pesquisado
             pos    - posicao inicial da procura na string 
             ignoreCase - se true faz uma pesquisa "case-insensitive"
 Retorno:     posicao na string onde o texto foi encontrado ou -1 se nao
             achou o texto
********************************************************************/
CInteger CStr::find( const char * toFind, int pos, bool ignoreCase ) const
{
    if( !getLen() || pos < 0 )
        return -1;

    if( pos > getLen())
        pos = getLen();

    char * pcResult = 0;
    CStr temp = *this;

    if( ignoreCase ) {
        CStr stoFind( toFind );
        CStr toFindTemp = stoFind.getUpperCase();
        temp = getUpperCase();

        pcResult = strstr((char*) temp.m_pStrRef->m_szValue + pos, (char*) toFindTemp );
    }
    else {
        pcResult = strstr((char*) temp.m_pStrRef->m_szValue + pos, toFind );
    }
    if( !pcResult )
        return -1;

    return (int )( pcResult - (char*)temp.m_pStrRef->m_szValue );
}

/********************************************************************
 Proposito:    Idenitifica se a string e' vazia (ou nula)
 Retorno:   true se a string e' vazia ou nula
********************************************************************/
bool CStr::isEmpty() const
{
  if ( getLen() == 0 )
    return true;
  return false;
}

/********************************************************************
 Proposito:    Converte um numero de hexadecimal inteiro
 Retorno:   inteiro convertido ou zero caso nao consiga a conversao
********************************************************************/
CInteger CStr::getHexToInt() const
{
   if( !getLen())
      return 0;

   char * s = m_pStrRef->m_szValue;
   int ret = 0;

    while( *s ) {
        if( *s >= '0' && *s <= '9' )
         ret += *s - '0';
        else if( *s >= 'a' && *s <= 'f' )
            ret += *s - 'a' + 10;
      else if( *s >= 'A' && *s <= 'F' )
         ret += *s - 'A' + 10;
      else
         return 0;

        s++;

      if( *s )
         ret = ret << 4;
   }
   return ret;
}

/********************************************************************
 Proposito:     Retorna um texto a esquerda da string
 Parametros: size - tamanho do texto a ser retornado
 Retorno:    Texto a esquerda da string. Se o tamanho for maior que
             a string, retorna a string inteira
********************************************************************/
CStr CStr::getLeft( int size ) const
{
    if( size > getLen())
        size = getLen();

    if( !getLen() || size <= 0 )
        return "";

    CStr s;
    s.createStrRef( m_pStrRef->m_szValue, size );
    return s;
}

/********************************************************************
 Proposito:    Converte uma string com o primeiro caracter em maiusculo
 Retorno:   String convertida
 Exemplo:   "UMA FRASE"  ->  retorna "Uma Frase"
            "um teXTO"   ->  retorna "Um Texto"
********************************************************************/
CStr CStr::getFirstUpperCase() const
{
   if( getLen() == 0 )
      return "";

   const char * c = m_pStrRef->m_szValue;
   char * buf;
   char * pos = buf = new char[ getLen() + 1 ];
   bool upper = true;

   while( *c ) {
#ifdef UNICODE
        *pos =  (char) (upper ? towupper( *c ) : towlower( *c ));
        upper = iswalnum( *c )  ? false : true;
#else
        *pos =  (char) (upper ? toupper( *c ) : tolower( *c ));
        upper = isalnum( *c )  ? false : true;
#endif
        c++;
        pos++;
   }
   *pos = '\0';
   CStr ret = buf;
   delete buf;
   return ret;
}

/********************************************************************
 Proposito:     Retorna um trecho de uma string
 Parametros: start - posicao inicial na string (primeira posicao e' zero)
             len - quantidade de caracteres
 Retorno:     Trecho da string. Caso start seja maior que o tamanho da
             string, retorna uma string vazia.
********************************************************************/
CStr CStr::getMid( int start, int len ) const
{
    if( start <  0 )
        start = 0;

    if( getLen() == 0 || len <= 0 || start >= getLen())
        return "";

    if( len > (getLen()-start))
        len = getLen()-start;

    CStr s;
     s.createStrRef( m_pStrRef->m_szValue + start, len );

     return s;
}

/**********************************************************************
 Proposito:    Converte uma string para CDateTime
 Retorno:    DateTime convertido.
 Obs.:      a string deve estar no formato yyyymmdd, sem espaços ou outros caracteres
*************************************************************************/
CDateTime CStr::getDateTime() const
{
    if( !getLen())
        return CDateTime();

    return CDateTime( getMid( 0, 4 ).getInteger(), getMid( 4, 2 ).getInteger(),
      getMid( 6, 2 ).getInteger(), getMid( 8, 2 ).getInteger(), getMid( 10, 2 ).getInteger(),
      getMid( 12, 2 ).getInteger());
}

/********************************************************************
 Proposito:    Converte uma string substituindo os carateres especiais
            em HTML ( de "&" para "&amp;" por exemplo )
 Retorno:   Texto convertido
********************************************************************/
CStr CStr::getHTML() const
{
    CStr text = *this;

    text = text.replace( "&", "&amp;", -1 );
    text = text.replace( "<", "&lt;", -1 );
    text = text.replace( ">", "&gt;", -1 );
    text = text.replace( "\"", "&quot;", -1 );
    text = text.replace( "\r\n", "<br>", -1 );
    text = text.replace( "\r", "<br>", -1 );

    return text;
}

/********************************************************************
 Proposito:  Le um parametro de uma String
 Parametros: paramName - Nome do parametro
 Retorno:    Valor do parametro
 Obs:        Parametros sao textos separadas por dois pontos e
             ponto e virgula, exemplo:
             "text:Hello world; size:4" -> o parametro de nome "text" 
             tem o valor "Hello word" e o parametro de nome "size" tem
             o valor de "4"
********************************************************************/
CStr CStr::getParam( const char * paramName ) const
{
   if( !getLen())
      return "";

   char * pos = m_pStrRef->m_szValue;

   while( *pos ) {
      if( *pos == *paramName ) {
         int len = strlen( paramName );

         if( strncmp( pos, paramName, len ) == 0 ) {
            char * last = pos;
            pos += len;

            while( *pos == ' ' )
               pos++;

            if( *pos == ':' ) {
               pos++;

               char * start = pos;

               while( *pos && *pos != ';' )
                  pos++;

               return CStr( start, pos - start );
            }
            pos = last;
         }
      }
      pos++;
   }
   return "";
}


typedef struct tagConvItem {
    char * HTML;
    char * ANSI;
} _ConvItem;

_ConvItem ConvTable[] = {
    { "lt;", "<" },
    { "gt;", ">" },
    { "amp;", "&" },
    { "quot;", "\"" },
    { "gt;", ">" }};

/********************************************************************
 Proposito:    Converte uma string com caracteres especiais de HTML
            para um texto ( de "&gt;" para ">" por exemplo )
 Retorno:    texto convertido
********************************************************************/
CStr CStr::removeHTML() const
{
    if( !getLen())
        return "";

    char * htmlPos = *this;
    char * buf =  new char[ getLen() * 2 ]; // p/ garantir o tamanho
    char * ansiPos = buf;

    while( *htmlPos ) {
        if( *htmlPos == '&' ) {
            htmlPos++;

            for( int n = 0; n < sizeof( ConvTable ) / sizeof( _ConvItem ); n++ ) {
                int size = strlen( ConvTable[ n ].HTML );

                if( strncmp( htmlPos, ConvTable[ n ].HTML, size ) == 0 ) {
                    strcpy( ansiPos, ConvTable[ n ].ANSI );
                    ansiPos += strlen( ConvTable[ n ].ANSI );
                    htmlPos += size;
                    break;
                }
            }
        }
        else if( *htmlPos == '%' ) {
            int n = 0;
            char temp[20];
            htmlPos++;

            while( *htmlPos >= '0' && *htmlPos <= '9' ) {
                temp[ n ] = *htmlPos;
                n++;
                htmlPos++;
            }
            temp[n]='\0';
            *ansiPos++ = (char)CStr( temp ).getHexToInt();
        }
        else if( *htmlPos == '<' && strncmp( htmlPos, "<br>", 4 ) == 0 ) {
            *ansiPos++ = '\r';
            *ansiPos++ = '\n';
            htmlPos += 4;
        }
        else {
            *ansiPos++ = *htmlPos++;
        }
    }
    *ansiPos = '\0';
    CStr ret = buf;
    delete buf;
    return ret;
}

/********************************************************************
 Proposito:     Substitui um texto em uma string
 Parametros: toFind - texto a ser encontrado para substituicao
             toReplace -  novo texto
             times - numero de ocorrencias (vezes) que deve substituir
             o texto. A pesquisa e feita do inicio ao fim do texto. O
             valor -1 substitui todas as ocorrencias
 Retorno:    String com texto substituido
********************************************************************/
CStr CStr::replace( const char * toFind, const char * toReplace, int times ) const
{
    CStr ret = *this;
    int findPos;
    int offset = 0;

    while( times-- && (( findPos = ret.find( toFind, offset, false )) != -1 )) {
        CStr s = ret.getLeft( findPos );
        s = s + toReplace;
        offset = s.getLen();
        ret = s + (char*)( ret.m_pStrRef->m_szValue + (findPos + strlen( toFind )));
    }
    return ret;
}

/********************************************************************
 Proposito:     Retorna um texto a direita da string
 Parametros: size - tamanho do texto a ser retornado
 Retorno:    Texto a direita da string. Se o tamanho for maior que
             a string, retorna a string inteira
********************************************************************/
CStr CStr::getRight( int size ) const
{
    if( size > getLen())
        size = getLen();

    if( !getLen())
        return "";

    CStr s;
    s.createStrRef( m_pStrRef->m_szValue + (getLen() - size), size );
    return s;
}

/********************************************************************
 Proposito:    Converte uma string para um double
 Retorno:   Valor convertido ou 0.0 se o texto nao pode ser convertido
********************************************************************/
CDouble CStr::getDouble() const
{
    if( !getLen())
        return 0;

    CStr value = replace( " ", "", -1 );
#ifdef UNICODE
   return wcstod( (wchar_t *)((char*)value) , NULL );
#else
   return atof((char*) value );
#endif
}

/********************************************************************
 Proposito:    Converte uma string para booleano
 Retorno:   Valor booleano.
 Obs:       Se a string for um valor numerico diferente de zero, 
            retorna verdadeiro, caso contrario falso. Tambem sao
            suportados os textos literais "true" ou "t" para true
            e "false" ou "f" para falso
********************************************************************/
CBoolean CStr::getBoolean() const
{
    if( !getLen())
        return false;

    if( isEqual( "true", true ))
        return true;

    if( isEqual( "t", true ))
        return true;

    if( isEqual("false", true ))
        return false;

    if( isEqual("f", true ))
        return false;

    return atoi((char*) m_pStrRef->m_szValue ) ? true : false;
}

/********************************************************************
 Proposito:    Converte uma string para um valor inteiro
 Retorno:   O numero convertido. Se o valor nao puder ser convertido,
            retorna zero.
********************************************************************/
CInteger CStr::getInteger() const
{
    if( !getLen())
        return 0;

    return atoi((char*) m_pStrRef->m_szValue );
}

/********************************************************************
 Proposito:     Compara a string com um outro texto
 Parametros: other - outra string a ser comparada
             ignoreCase - se verdadeiro, faz uma comparacao case-insensitive
 Retorno:    true se a strings forem iguais, false caso contrario
********************************************************************/
bool CStr::isEqual( const char * other, bool ignoreCase ) const
{
    if( !other || !*other || !getLen())
        return false;

    if( ignoreCase )
        return strncmp( other, (char*)m_pStrRef->m_szValue, strlen( other )) == 0 ? true : false;

    return strcmp( other, (char*)m_pStrRef->m_szValue ) == 0 ? true : false;
}

/********************************************************************
 Proposito:     Verifica se uma string termina com um texto
 Parametros: sufix - texto a ser pesquisado
             ignoreCase - se true, faz uma comparacao case-insensitive
 Retorno:     True se a string termina com o texto, false caso contrario
********************************************************************/
bool CStr::endsWith( const char * sufix, bool ignoreCase ) const
{
    if( !sufix || !*sufix || !getLen())
        return false;

   if(((int)strlen( sufix )) > getLen())
        return false;

    if( ignoreCase )
        return strncmp( sufix, (char*)(m_pStrRef->m_szValue + (getLen() - strlen(sufix))), strlen( sufix )) == 0 ? true : false;

    return strncmp( sufix, (char*)(m_pStrRef->m_szValue + (getLen() - strlen(sufix))), strlen( sufix )) == 0 ? true : false;
}   

/********************************************************************
 Proposito:     Verifica se uma string inicia com um texto
 Parametros: prefix - texto a ser pesquisado
             offset - posicao inicial da pesquisa (zero based)
             ignoreCase - se true, faz uma comparacao case-insensitive
 Retorno:     True se a string termina com o texto, false caso contrario
********************************************************************/
bool CStr::startsWith( const char * prefix, int offset, bool ignoreCase ) const
{
    if( !prefix || !*prefix || !getLen())
        return false;

   if(( offset + (int)strlen( prefix )) > getLen())
        return false;


    if( ignoreCase )
        return strncmp( prefix, (char*)(m_pStrRef->m_szValue + offset), strlen( prefix )) == 0 ? true : false;

    return strncmp( prefix, (char*)(m_pStrRef->m_szValue + offset), strlen( prefix )) == 0 ? true : false;
}   

/********************************************************************
 Proposito:    Verifica se uma string e' um numero
 Retorno:    True se a string e' um valor numerico, false caso contrario
********************************************************************/
bool CStr::isNumber() const
{
    if( !getLen())
        return false;

    char * s = m_pStrRef->m_szValue;

    while( *s != '\0' ) {
#ifdef UNICODE
        if( !iswdigit( *s ) && *s != '-' && *s != '.' && *s != '+' )
#else
        if( !isdigit( *s ) && *s != '-' && *s != '.' && *s != '+' )
#endif
            return false;
        s++;
    }
    return true;
}

/********************************************************************
 Proposito: Verifica se uma string inicia e' composta somente por letras
 Retorno:   True se a string e' alfa, caso contrario false
********************************************************************/
bool CStr::isAlpha() const
{
   if( !getLen())
      return false;

    char * s = m_pStrRef->m_szValue;

    while( *s != '\0' ) {
#ifdef UNICODE
        if( !iswalpha( *s ))
#else
        if( !isalpha( *s ))
#endif
            return false;
        s++;
    }
    return true;
}

/********************************************************************
 Proposito: Verifica se uma string e' um numero hexadecimal valido
 Retorno:   True se a string e' um numero hexadecimal.
********************************************************************/
bool CStr::isHex() const
{
    if( !getLen())
        return false;

    char * s = m_pStrRef->m_szValue;

    while( *s != '\0' ) {
#ifdef UNICODE
        if( !iswxdigit( *s ))
#else
        if( !isxdigit( *s ))
#endif
            return false;
        s++;
    }
    return true;
}

void CStr::set( const CStr & other )
{
    createStrRef( other );
}

/********************************************************************
 Proposito:    Converte uma string para lowercase
 Retorno:    String convertida
********************************************************************/
CStr CStr::getLowerCase() const
{
    CStr ret;

    if( getLen()) {
        char * buf  = new char[ getLen() + 1 ];
        char * posValue = m_pStrRef->m_szValue;
        char * posBuf = buf;

        while( *posValue ) {
            *posBuf++ = tolower( *posValue++ );
        }
        *posBuf = '\0';
        ret = (char*) buf;
        delete buf;
    }
    return ret;
}

/********************************************************************
 Proposito:    Converte uma string para upper case
 Retorno:    String convertida
********************************************************************/
CStr CStr::getUpperCase() const
{
    CStr ret;

    if( getLen()) {
        char * buf  = new char[ getLen() + 1 ];
        char * posValue = m_pStrRef->m_szValue;
        char * posBuf = buf;

        while( *posValue ) {
#ifdef UNICODE
            *posBuf++ = towupper( *posValue++ );
#else
            *posBuf++ = toupper( *posValue++ );
#endif
        }
        *posBuf = '\0';
        ret = (char*) buf;
        delete buf;
    }
    return ret;
}

/********************************************************************
 Proposito: trunca a string
 Parametros:pos - posicao de "corte"
********************************************************************/
void CStr::truncate( int pos )
{
    if( pos < getLen() && pos >= 0 ) {
        copyStrRef();
        m_pStrRef->m_inSize = pos;

        *( m_pStrRef->m_szValue + m_pStrRef->m_inSize ) = '\0';             // Forca terminacao nula
    }
}

/********************************************************************
 Proposito: Preenche o conteudo da string com um caractere
 Parametros:c - caractere de preenchimento
            size - quantidade de caracteres na string
********************************************************************/
void CStr::fill( char c, int size )
{
    if( size <= 0 ) {
        clear();
        return;
    }
    char * pc = new char[ size ];
    memset( pc, c, size );
    createStrRef( pc, size );
    delete pc;
}

/********************************************************************
 Proposito: Remove espacos em branco no inicio e no final da string
 Retorno:   String sem espacos no inicio e no fim
********************************************************************/
CStr CStr::trim() const
{
    if( !getLen())
        return "";

    char * strStart = m_pStrRef->m_szValue;
    char * strEnd = m_pStrRef->m_szValue + m_pStrRef->m_inSize - 1;

    while( *strStart == ' ' )
        strStart++;

    while( strEnd > strStart && *strEnd == ' ' )
        strEnd--;

    CStr s;
    s.createStrRef( strStart, (int) (strEnd - strStart + 1 ));
    return s;
}

char & CStr::operator[]( int index )
{
    static char ret = '\0';

    if( getLen() && index < m_pStrRef->m_inSize && index >= 0 ) {
        copyStrRef();
        return *( m_pStrRef->m_szValue + index );
    }
    return ret;
}

char CStr::operator[]( int index ) const
{
    if( !m_pStrRef || !m_pStrRef->m_szValue || index > m_pStrRef->m_inSize || index < 0 ) {
        return '\0';
    }
    return *(m_pStrRef->m_szValue + index);
}

CStr CStr::operator+( const CStr & s ) const
{
    if( !s.getLen())
        return *this;

    if( getLen()) {
        CStr strTemp;

        strTemp.createStrRef( m_pStrRef->m_inSize + s.m_pStrRef->m_inSize );
        memcpy( strTemp.m_pStrRef->m_szValue, m_pStrRef->m_szValue, m_pStrRef->m_inSize );
        memcpy( strTemp.m_pStrRef->m_szValue + m_pStrRef->m_inSize, s.m_pStrRef->m_szValue, s.m_pStrRef->m_inSize );
        *( strTemp.m_pStrRef->m_szValue + m_pStrRef->m_inSize + s.m_pStrRef->m_inSize ) = '\0';
        return strTemp;
    }
    return s;
}

CStr CStr::operator+( const char * pc ) const
{
    if( !pc )
        return *this;

    if( getLen()) {
        CStr strTemp;
        unsigned int wStrSize = strlen( pc );

        strTemp.createStrRef( m_pStrRef->m_inSize + wStrSize );
        memcpy( strTemp.m_pStrRef->m_szValue, m_pStrRef->m_szValue, m_pStrRef->m_inSize );
        memcpy( strTemp.m_pStrRef->m_szValue + m_pStrRef->m_inSize, pc, wStrSize );
        *( strTemp.m_pStrRef->m_szValue + m_pStrRef->m_inSize + wStrSize ) = '\0';

        return strTemp;
    }
    return pc;
}

CStr & CStr::operator+=( const char * pc)
{
    *this = *this + pc;
    return *this;
}

CStr & CStr::operator+=( char c )
{
    char buf[] = { c, '\0' };

    *this = *this + buf;
    return *this;
}

CStr & CStr::operator+=( const CStr & other )
{
    if( &other != this ) {
        *this = *this + other;
    }
    return *this;
}

