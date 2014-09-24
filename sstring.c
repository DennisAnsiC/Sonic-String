
#include "sstring.h"
#include <stdio.h>
#include <stdlib.h>

/* Construtor */
sstring * new_sstring (const unsigned char *this)
{
	sstring *str = { 0 };

	if ((str = (sstring *)malloc(sizeof(sstring))) != NULL)
	{
		/* Values. */
		str->last_error		= SS_UNKNOWN;
		str->string_value	= NULL;
		str->string_length	= 0;

		/* Public. */
		str->error			= _error;
		str->string			= _string;
		str->length			= _length;
		str->value			= _value;

		/* Private. */
		str->strlen			= _strlen;
		str->memset			= _memset;
		str->memcpy			= _memcpy;
		str->alloc			= _alloc;

		/* Is OK. */
		str->last_error		= SS_OK;

		/* Inicialização */
		if (this != NULL)
		{
			str->value(str, this);
		}
	}

	return str;
}

/* Funções. (Public) */
unsigned int _error(struct sstring *this)
{
	return this->last_error;
}

unsigned char * _string (struct sstring *this)
{
	return this->string_value;
}
	
unsigned int _length(struct sstring *this)
{
	return this->string_length;
}

unsigned char * _value(sstring *this, const unsigned char *str)
{
	unsigned int length = 0;

	if ((length = this->strlen(str)) > 0)
	{
		if ((this->string_value = (char *)this->alloc(this->string_value, (length * sizeof(char)) + 1)) != NULL)
		{
			this->memset((void *)this->string_value, '\0', (length * sizeof(char)) + 1);
			this->memcpy((void *)this->string_value, (void *)str, length);
			this->string_length = length;
		}
	}

	return (unsigned char *)NULL;
}

/* Funções. (Private) */
unsigned int _strlen(const unsigned char *string)
{
	int length = 0;

	while (string[length] != 0) 
		length++;

	return length;
}

void *_memset(void *pointer, unsigned int value, unsigned int size)
{
	unsigned char *_ptr = (unsigned char *)pointer;

	while (size > 0)
	{
		*_ptr = value;
		_ptr++;
		size--;
	}

	return (void *)_ptr;
}

void *_memcpy(void *destination, const void *source, unsigned int size)
{
	unsigned char *ptr_a = (unsigned char *)destination;
	unsigned char *ptr_b = (unsigned char *)source;

	while (size--)
		*ptr_a++ = *ptr_b++;

	return destination;
}

void* _alloc (void* pointer, unsigned int size)
{
	void *ptr;

	if ((ptr = realloc(pointer, size)) != NULL)
		return ptr;

	return NULL;
}
