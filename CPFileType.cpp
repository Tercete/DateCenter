#include "CDatatypes.h"

#ifdef WIN32
#include <windows.h>
#endif

typedef struct __PStrTableEntry {
    int Id;
    char * Str;
} __StrTableEntry;

#ifndef EPERM
#define EPERM           1
#define ENOENT          2
#define ESRCH           3
#define EINTR           4
#define EIO             5
#define ENXIO           6
#define E2BIG           7
#define ENOEXEC         8
#define EBADF           9
#define ECHILD          10
#define EAGAIN          11
#define ENOMEM          12
#define EACCES          13
#define EFAULT          14
#define EBUSY           16
#define EEXIST          17
#define EXDEV           18
#define ENODEV          19
#define ENOTDIR         20
#define EISDIR          21
#define ENFILE          23
#define EMFILE          24
#define ENOTTY          25
#define EFBIG           27
#define ENOSPC          28
#define ESPIPE          29
#define EROFS           30
#define EMLINK          31
#define EPIPE           32
#define EDOM            33
#define EDEADLK         36
#define ENAMETOOLONG    38
#define ENOLCK          39
#define ENOSYS          40
#define ENOTEMPTY       41
#endif

static __StrTableEntry  entries[] = {
    { EPERM,   "Nao e'  dono" },
    { ENOENT,  "O arquivo '%1' nao foi encontrado." },
    { ESRCH,   "Processo nao encontrado" },
    { EINTR,   "Chamada de sistema interrompida" },
    { EIO,     "Erro de Entrada e Saida" },
    { ENXIO,   "Dispositivo ou endereco invalido" },
    { E2BIG,   "Lista de argumentos muito longa" },
    { ENOEXEC, "Formato do executavel invalido" },
    { EBADF,   "Numeo de arquivo incorreto" },
    { ECHILD,  "Processo nao criado" },
    { EAGAIN,  "Sem memoria" },
    { ENOMEM,  "Sem memoria" },
    { EACCES,  "Permissao negada" },
    { EFAULT,  "Endereco invalido" },
    { EBUSY,   "Dispositivo ocupado" },
    { EEXIST,  "Arquivo %1 ja' existe" },
    { EXDEV,   "Ligacao de dispostivo cruzada" },
    { ENODEV,  "Dispositivo invalido" },
    { ENOTDIR, "Arquivo %1 nao e' um diretorio" },
    { EISDIR,  "Arquivo %1 e' um diretorio" },
    { EINVAL,  "Argumento invalido" },
    { ENFILE,  "Tabela de arquivos excedida" },
    { EMFILE,  "Muitos arquivos abertos" },
    { ENOTTY,  "Nao e' TTY" },
    { EFBIG,   "Arquivo muito longo" },
    { ENOSPC,  "Sem espaco no dispositivo" },
    { ESPIPE,  "Procura ilegal" },
    { EROFS,   "Arquivo %1 e' somente leitura" },
    { EMLINK,  "Muitas ligacoes" },
    { EPIPE,   "'Pipe' quebrado" },
    { EDOM,    "Argumento matematico" },
    { ERANGE,  "Resultado muito longo" },
    { EDEADLK, "Recurso 'deadlock' deve ocorrer" },
    { ENAMETOOLONG, "Nome muito longo para %1" },
    { 0, 0 } };

CPFile::CPFile()
{
    Stream = 0;
    OpenMode = RdOnly;
    End = false;
}

CPFile::CPFile( const CStr & file, int mode )
{
    Stream = 0;
    End = false;

    open( file, mode );
}

CPFile::~CPFile()
{
    close();
}

void CPFile::close()
{
   if( Stream )
      _close( Stream );

   Stream = 0;
}

void CPFile::remove()
{
    close();

    if( ::remove( (LPCSTR) FileName ) == -1 ) {
        error();
    }
}

void CPFile::open()
{
    open( FileName );
}

int CPFile::read( void * buf, int size )
{
    if( !Stream )
        return 0;

    int count = _read( Stream, buf, size);

    if( count <= 0 ) {
        error();
    }
    if( count < size )  // Se leu menos do que o requisitado, alcancou EOF
        End = true;

    return count;
}

void CPFile::skip( int offset )
{
    moveTo( getPos() + offset );
}

void CPFile::moveTo( int lSeekPos )
{
    int nSeek = SEEK_SET;

    if( Stream ) {
        if( _lseek( Stream, lSeekPos, nSeek ) != 0 ) {
            error();
        }
    }
}

void CPFile::rename( const CStr & newName )
{
    close();

    if( ::rename( FileName, newName ) != 0 ) {
        error();
    }
    FileName = newName;
}

void CPFile::error()
{
   int pos = 0;

   while( entries[ pos ].Str ) {
      if( entries[ pos ].Id == errno ) {
          THROW_ERROR( errno, CStr( entries[ pos ].Str ).replace( "%1", FileName ));
      }
      pos++;
   }
   THROW_ERROR( errno, "<sem descricao>" );
}

int CPFile::getPos() const
{
    return Stream ? _lseek( Stream, 0, SEEK_SET ) : 0;
}

void CPFile::write( const void * buf, int size )
{
    if( !Stream )
        return;

    int count = _write( Stream, buf, size );

    if( count < size ) {
        error();
    }
}

void CPFile::open( const CStr & fileName, int openMode )
{
    close();

    OpenMode = openMode;
    FileName = fileName;

    if((Stream = _open(FileName, openMode , _S_IREAD | _S_IWRITE)) <= 0 ) {
        error();
    }
}

CStr CPFile::getLine()
{
    if( !Stream )
        return "";

    char*   buf = new char[ MAX_SIZE + 1 ];
    DWORD   dwRead = 1;
    UINT    uiContador;

    uiContador = 0;

    while((buf[uiContador-2] != '\r' && buf[uiContador-1] != '\n') && (uiContador < MAX_SIZE) && (dwRead != 0)) {
        dwRead = _read(Stream, &buf[uiContador], 1);
        ++uiContador;
    }
    buf[uiContador-2] = '\0';
    uiContador -= 2;

    CStr ret( buf );
    delete buf;
    return ret;
}

void CPFile::append( const CStr & text )
{
    if( !Stream )
        return;

    if( _lseek(Stream, 0, SEEK_END ) < 0 ) {
        error();
    }
    if( _write( Stream, text, text.getLen() ) < 0 ) {
        error();
    }
}

void CPFile::clear()
{ 
    return ; //End; 
}

bool CPFile::isEnd()
{ 
    return End; 
}

CStr CPFile::getFileName() const
{ 
    return FileName; 
}

