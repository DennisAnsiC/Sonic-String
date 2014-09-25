
/* 
** Sonic String.
** 
** M�todos (Public)...
**    .value("Novo valor da string."); OK
**        Seta novo valor na string (pode ser utilizado para inicializa��o).    
** 
**    .string(this); // OK
**        Retorna string atual.
**
**    .length(this); // OK
**        Retorna tamanho da string atual.
**
**    .concat(this, " Concatena texto no final da string."); OK
**        Concatena texto no final da string, caso n�o tiver dados setados, seta como '.value' (concatena��o).
**     
**    .compare(this, "Valor a ser comparado"); // OK
**        Compara dados com o valor atual da string setado em '.value' (compara��o).
** 
**    .search(this, "Valor a ser procurado.); // OK
**        Pesquisa dados dentro da string atual setada em '.value' (busca).
**
**    .delete(this); // OK
**        Deleta string da mem�ria (free).
** 
**    .set_value(this, "novo", 6); //OK
**        Substitui parte da string a partir de determinada posi��o.
**
**    .replace(this, "velho", "novo");
**        Substitui parte da string.
** 
**    .zero(this); // OK
**        Zera string setando todos os valores para '\0'.
** 
**    .split("++");
**        Reparte string atual em peda�os de acordo com o delimitador.
** 
**    .split_limit();
**        Retorna quantidade de peda�os existentes (�til ap�s uso de .split(..) para saber quantas strings existem).
**    
**    .split_value(1); <- 1, 2, 3, 4...
**        Retorna valor da string que foi repartida.
**    
**    .split_length(1); <- 1, 2, 3, 4...
**        Retorna tamanho atual da string repartida.
**
**    
**    M�todos (Private)...
**    .alloc (void* pointer, unsigned int length) // OK
**        Aloca tamanho na mem�ria.
**        Retorno: void *
**
**    .clear(void *this, unsigned int length); // OK
**        Libera buffer da mem�ria.
**
**    .len(const unsigned char *this); // OK
**        Calcula tamanho da string e armazena resultado em 'string_length'.
**        Retorno: unsigned int
**    
**    .set(void *pointer, unsigned int value, unsigned int length); // OK
**        Altera valores de buffer na mem�ria.
**        Retorno: void *
**    
**    .copy(void *destination, const void *source, unsigned int length); // OK
**        Copia buffer para outro buffer.
**        Retorno: void *
**    
**    
**    Tratamento de erros.
**    .error(); // OK
**        Retorna c�digo do ultimo erro.
**
**        C�digos de erro:
**            SS_UNKNOWN = Erro desconhecido.
**            SS_OK = String sem nenhum erro.
**
*/

/* Error Codes */
#define SS_UNKNOWN                 0x00
#define SS_OK                      0x01
#define SS_DELETED                 0x02
#define SS_SET_VALUE               0x03
#define SS_CONCATENATED            0x04
#define SS_ZEROED                  0x05
#define SS_EQUAL                   0x06
#define SS_NOT_EQUAL               0x07
#define SS_INVALID_BUFFER          0x08
#define SS_STRING_FOUND            0x09
#define SS_STRING_NOT_FOUND        0x10
#define SS_VERY_LARGE_STRING       0x11
#define SS_STRING_COPIED           0x12
#define SS_REPLACED                0x13

/* Types. (Public) */
typedef unsigned int (*___error)(struct sstring *);
typedef unsigned char *(*___string)(struct sstring *);
typedef unsigned int (*___length)(struct sstring *);
typedef unsigned char *(*___value)(struct sstring *, const unsigned char *);
typedef void (*___delete)(struct sstring *);
typedef unsigned char *(*___concat)(struct sstring *, const unsigned char *);
typedef void (*___zero)(struct sstring *);
typedef int (*___compare)(struct sstring *, const unsigned char *);
typedef unsigned char *(*___search)(struct sstring *, const unsigned char *);
typedef unsigned char *(*___set_value)(struct sstring *, const unsigned char *, unsigned int);
typedef unsigned char *(*___replace)(struct sstring *, const unsigned char *, const unsigned char *);

/* Types. (Private) */
typedef unsigned int (*___len)(const unsigned char *);
typedef void *(*___set)(void *, unsigned int, unsigned int);
typedef void *(*___copy)(void *, const void *, unsigned int);
typedef void *(*___alloc)(void *, unsigned int);
typedef void (*___clear)(void *, unsigned int);

/* Structure of Sonic String. */
typedef struct sstring
{
    int last_error;                     // Armazena C�digo do ultimo erro.
    unsigned char *string_value;        // Armazena Valor atual da string.
    unsigned int string_length;         // Armazena Tamanho atual da string.

    /* Public */
    ___error error;                      // Retorna ultimo c�digo de erro.
    ___string string;                    // Retorna string atual.
    ___length length;                    // Retorna tamanho da string.
    ___value value;                      // Seta novo valor na string.
    ___delete delete;                    // Deleta string da mem�ria.
    ___concat concat;                    // Concatena texto no final da string.
    ___zero zero;                        // Seta todos os bytes da string para '\0';
    ___compare compare;                  // Compara se strings s�o iguais.
    ___search search;                    // Procura por string.
    ___set_value set_value;              // Substitui string a partir de uma determinada posi��o.
    ___replace replace;                  // Substitui todas as ocorrencias encontradas em uma string.

    /* Private */
    ___len len;                          // Equivalente a strlen().
    ___set set;                          // Equivalente a memset().
    ___copy copy;                        // Equivalente a memcpy().
    ___alloc alloc;                      // Equivalente a realloc().
    ___clear clear;                      // Equivalente a free().
} sstring;

/* Prototypes. (Checking) */
int sstring_isok(sstring *this);
int sstring_array_isok(sstring *this[], int limit);

/* Prototypes. (Constructor) */
sstring *new_sstring(const unsigned char *string_initialization);

/* Prototypes. (Public) */
unsigned int _error(sstring *this);
unsigned char *_string(sstring *this);
unsigned int _length(sstring *this);
unsigned char *_value(sstring *this, const unsigned char *string);
void _delete(sstring *this);
unsigned char *_concat(sstring *this, const unsigned char *string);
void _zero(sstring *this);
int _compare(sstring *this, const unsigned char *string);
unsigned char *_search(struct sstring *this, const unsigned char *delimiter);
unsigned char *_set_value(struct sstring *this, const unsigned char *string, unsigned int startup);
unsigned char *_replace(struct sstring *this, const unsigned char *old_string, const unsigned char *new_string);

/* Prototypes. (Private) */
unsigned int _len(const unsigned char *string);
void *_set(void *pointer, unsigned int value, unsigned int length);
void *_copy(void *destination, const void *source, unsigned int length);
void *_alloc(void* pointer, unsigned int length);
void _clear(void *pointer, unsigned int length);

/* Prototypes. (Extras) */
void *smalloc(unsigned int length);
void *smemset(void *pointer, unsigned int value, unsigned int length);
