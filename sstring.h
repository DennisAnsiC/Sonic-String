
/* 
** Sonic String.
** 
** Métodos (Public)...
**	.value("Novo valor da string."); OK
**		Seta novo valor na string (pode ser utilizado para inicialização).	
** 
**	.string(this); // OK
**		Retorna string atual.
**
**	.length(this); // OK
**		Retorna tamanho da string atual.
**
**	.concat(" Concatena texto no final da string.");
**		Concatena texto no final da string, caso não tiver dados setados, seta como '.value' (concatenação).
** 	
**	.compare("Valor a ser comparado");
**		Compara dados com o valor atual da string setado em '.value' (comparação).
** 
**	.search("Valor a ser procurado.);
**		Pesquisa dados dentro da string atual setada em '.value' (busca).
**
**	.delete();
**		Deleta string da memória (free).
** 
**	.set_value("Novo", 0, 4);
**		Seta valor em determinada parte da string.
** 
**	.zero(this);
**		Zera string setando todos os valores para '\0'.
** 
**	.split("++");
**		Reparte string atual em pedaços de acordo com o delimitador.
** 
**	.split_limit();
**		Retorna quantidade de pedaços existentes (útil após uso de .split(..) para saber quantas strings existem).
**	
**	.split_value(1); <- 1, 2, 3, 4...
**		Retorna valor da string que foi repartida.
**	
**	.split_length(1); <- 1, 2, 3, 4...
**		Retorna tamanho atual da string repartida.
**
**	
**	Métodos (Private)...
**	.alloc (void* pointer, unsigned int size) // OK
**		Aloca tamanho na memória.
**		Retorno: void *
**
**	.clear(void *this);
**		Libera buffer da memória.
**
**	.strlen(const unsigned char *this); // OK
**		Calcula tamanho da string e armazena resultado em 'string_length'.
**		Retorno: unsigned int
**	
**	.memset(void *ptr, unsigned int value, unsigned int size); // OK
**		Altera valores de buffer na memória.
**		Retorno: void *
**	
**	.memcpy(void *destination, const void *source, unsigned int size); // OK
**		Copia buffer para outro buffer.
**		Retorno: void *
**	
**	
**	Tratamento de erros.
**	.error();
**		Retorna código do ultimo erro.
**
**		Códigos de erro:
**			SS_OK = String sem nenhum erro.
**
*/

/* Códigos de erro */
#define SS_UNKNOWN	0x00
#define SS_OK		0x01

/* Tipos. (Public) */
typedef unsigned int (*___error)(struct sstring *);
typedef unsigned char * (*___string)(struct sstring *);
typedef unsigned int (*___length)(struct sstring *);
typedef unsigned char * (*___value)(struct sstring *, const unsigned char *);

/* Tipos. (Private) */
typedef unsigned int (*___strlen)(const unsigned char *);
typedef void * (*___memset)(void *, unsigned int, unsigned int);
typedef void * (*___memcpy)(void *, const void *, unsigned int);
typedef void * (*___alloc)(void *, unsigned int);

/* Estrutura da Sonic String. */
typedef struct sstring
{
	int last_error;				// Armazena Código do ultimo erro.
	char *string_value;			// Armazena Valor atual da string.
	int string_length;			// Armazena Tamanho atual da string.

	/* Public */
	___error error;				// Retorna ultimo código de erro.
	___string string;			// Retorna string atual.
	___length length;			// Retorna tamanho da string.
	___value value;				// Seta novo valor na string.

	/* Private */
	___strlen strlen;			// Equivalente a strlen().
	___memset memset;			// Equivalente a memset().
	___memcpy memcpy;			// Equivalente a memcpy().
	___alloc  alloc;			// Equivalente a realloc().
} sstring;

/* Construtor. */
sstring * new_sstring (const unsigned char *this);

/* Protótipos. (Public) */
unsigned int _error(sstring *this);
unsigned char * _string (sstring *this);
unsigned int _length(sstring *this);
unsigned char * _value(sstring *this, const unsigned char *str);

/* Protótipos. (Private) */
unsigned int _strlen(const unsigned char *string);
void *_memset(void *pointer, unsigned int value, unsigned int size);
void *_memcpy(void *destination, const void *source, unsigned int size);
void* _alloc (void* pointer, unsigned int size);
