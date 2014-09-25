
#include "sstring.h"
#include <Windows.h>       /* Use TRUE and FALSE. */
#include <stdlib.h>        /* Use realloc and free. */

/* Checking. */
int sstring_isok(sstring *this)
{
    if (this != (sstring *)NULL)
        if (this->error(this) == SS_OK)
            return TRUE;
        else
            return this->error(this);
    
    return FALSE;
}

int sstring_array_isok(sstring *this[], int limit)
{
    int control [2] = { 0, 0 };

    if (limit > 0)
    {
        for (control[0] = 0; control[0] <= limit; control[0]++)
        {
            if (this[control[0]] != (sstring *)NULL)
                if (this[control[0]]->error(this[control[0]]) == SS_OK)
                    control[1]++;                    
        }

        if (control[1] == limit)
            return TRUE;
    }

    return FALSE;
}

/* Constructor. */
sstring *new_sstring (const unsigned char *string_initialization)
{
    sstring *string;

    if ((string = (sstring *)smalloc(sizeof(sstring))) != NULL)
    {
        smemset(string, 0, sizeof(sstring));

        /* Default values. */
        string->last_error      = SS_UNKNOWN;
        string->string_value    = NULL;
        string->string_length   = 0;

        /* Public. */
        string->error           = _error;
        string->string          = _string;
        string->length          = _length;
        string->value           = _value;
        string->delete          = _delete;
        string->concat          = _concat;
        string->zero            = _zero;
        string->compare         = _compare;
        string->search          = _search;
        string->set_value       = _set_value;
        string->replace         = _replace;
		
        /* Private. */
        string->len             = _len;
        string->set             = _set;
        string->copy            = _copy;
        string->alloc           = _alloc;
        string->clear           = _clear;

        /* Checking 'Is OK'. */
        if (string->error   && string->string && string->length  && string->value  && string->delete    &&
            string->concat  && string->zero   && string->compare && string->search && string->set_value &&
            string->replace &&  string->len   && string->set     && string->copy   && string->alloc     && 
			string->clear)
        {
            string->last_error = SS_OK;

            /* Initialization. */
            if (string_initialization != (char *)NULL)
                string->value(string, string_initialization);
        }

        return string;
    }

    return (sstring *)NULL;
}

/* Functions. (Public) */
unsigned int _error(struct sstring *this)
{
    return this->last_error;
}

unsigned char *_string (struct sstring *this)
{
    return this->string_value;
}
    
unsigned int _length(struct sstring *this)
{
    return this->string_length;
}

unsigned char *_value(sstring *this, const unsigned char *string)
{
    unsigned int length = 0;
    this->last_error = SS_UNKNOWN;

    if ((length = this->len(string)) > 0)
    {
        if ((this->string_value = (unsigned char *)this->alloc(this->string_value, 
            (length * sizeof(char)) + 1)) != NULL)
        {
            this->set((void *)this->string_value, '\0', (length * sizeof(char)) + 1);
            this->copy((void *)this->string_value, (void *)string, length);
            this->last_error = SS_SET_VALUE;
            this->string_length = length;
        }
    }
    else
        this->last_error = SS_INVALID_BUFFER;

    return (unsigned char *)NULL;
}

void _delete(sstring *this)
{
    if (this->string_value && this->string_length > 0)
    {
        this->clear(this->string_value, this->string_length);
        this->last_error = SS_DELETED;
        this->string_length = 0;
    }
    else
        this->last_error = SS_INVALID_BUFFER;
}

unsigned char *_concat(sstring *this, const unsigned char *string)
{
    unsigned char *pointer = (unsigned char *)string;
    int length = 0, index = 0;
    this->last_error = SS_UNKNOWN;

    if (this->string_length > 0 && this->string_value && string)
    {
        if ((length = this->len(string)) > 0)
        {
            if ((this->string_value = (unsigned char *)this->alloc(this->string_value, 
                ((this->string_length + length) * sizeof(char)) + 1)) != NULL)
            {
                for (index = 0; index < length; index++)
                    this->string_value[this->string_length + index] = string[index];
                
                this->string_value[this->string_length + index] = '\0';
                this->string_length += index;
                
                this->last_error = SS_CONCATENATED;
                return this->string_value;
            }
        }
    }
    else
        this->last_error = SS_INVALID_BUFFER;

    return (unsigned char *)NULL;
}

void _zero(sstring *this)
{
    if (this->string_value && this->string_length > 0)
    {
        this->set(this->string_value, '\0', this->string_length);
        this->last_error = SS_ZEROED;
    }
    else
        this->last_error = SS_INVALID_BUFFER;
}

int _compare(sstring *this, const unsigned char *string)
{
    int control = 0;
    this->last_error = SS_UNKNOWN;

    if (string && this->string_value && this->string_length > 0)
    {
        while (string[control] == this->string_value[control])
            control++;

        if ((control - 1) == this->string_length && (control - 1) == this->len(string))
            this->last_error = SS_EQUAL;
        else
            this->last_error = SS_NOT_EQUAL;
    }
    else
        this->last_error = SS_INVALID_BUFFER;

    return this->last_error;
}

unsigned char *_search(struct sstring *this, const unsigned char *delimiter)
{
    unsigned char *pointer = NULL;
    int control [4] = { 0, 0, 0, 0 };

    if (delimiter && this->string_value && this->string_length > 0)
    {
        control[0] = this->len(delimiter);
        pointer = this->string_value;

        for (;*pointer++; control[3]++)
        {
            for (control[1] = 0; control[1] <= control[0]; control[1]++)
                if (this->string_value[control[3] + control[1]] == delimiter[control[1]])
                    control[2]++;
                else
                    break;
            
            if (control[2] == control[0]) 
            {
                this->last_error = SS_STRING_FOUND;
                break;
            }
            else
                this->last_error = SS_STRING_NOT_FOUND;
        }

        return pointer - 1;
    }
    else
        this->last_error = SS_INVALID_BUFFER;

    return pointer;
}

unsigned char *_set_value(struct sstring *this, const unsigned char *string, unsigned int startup)
{
    int length = 0, index = 0;
    this->last_error = SS_UNKNOWN;

    if (string && this->string_value && this->string_length > 0)
    {
        length = this->len(string);
        if ((startup + length) - 1 < this->string_length)
        {
            for (index = 0; index < length; index++)
                this->string_value[startup + index] = string[index];
            
            this->last_error = SS_STRING_COPIED;
            return &this->string_value[startup];
        }
        else
            this->last_error = SS_VERY_LARGE_STRING;
    }
    else
        this->last_error = SS_INVALID_BUFFER;

    return (unsigned char *)NULL;
}

unsigned char *_replace(struct sstring *this, const unsigned char *old_string, const unsigned char *new_string)
{
    // Here...
}

/* Functions. (Private) */
unsigned int _len(const unsigned char *string)
{
    unsigned int length = 0;

    while (*string++)
        length++;

    return length;
}

void *_set(void *pointer, unsigned int value, unsigned int length)
{
    unsigned char *_pointer = (unsigned char *)pointer;

    while (length > 0)
    {
        *_pointer = value;
        _pointer++;
        length--;
    }

    return (void *)_pointer;
}

void *_copy(void *destination, const void *source, unsigned int length)
{
    unsigned char *pointer_a = (unsigned char *)destination;
    unsigned char *pointer_b = (unsigned char *)source;

    while (length--)
        *pointer_a++ = *pointer_b++;

    return destination;
}

void *_alloc (void* pointer, unsigned int length)
{
    void *_pointer;

    if ((_pointer = realloc(pointer, length)) != NULL)
        return _pointer;

    return NULL;
}

void _clear(void *pointer, unsigned int length)
{
    smemset(pointer, '\0', length);
    free(pointer);
}

/* Functions. (Extras) */
void *smalloc(unsigned int length)
{
    void *pointer;

    if (length)
    {
        pointer = malloc(length);
        if (pointer) 
            return pointer;        
    }

    return NULL;
}

void *smemset(void *pointer, unsigned int value, unsigned int length)
{
    unsigned char *_pointer = (unsigned char *)pointer;

    while (length > 0)
    {
        *_pointer = value;
        _pointer++;
        length--;
    }

    return pointer;
}
