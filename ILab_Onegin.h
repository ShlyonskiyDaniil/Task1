#ifndef UNTITLED_ILAB_ONEGIN_H
#define UNTITLED_ILAB_ONEGIN_H
#include "string.h"
#include <stdio.h>
#include <mm_malloc.h>


typedef struct string_buffer
{
    unsigned long nchars ;
    char* buf;
    unsigned long  nstr;
} string_buffer;

typedef struct string
{
    char* str;
    unsigned int str_len;
}string;


#define NOTINRUSSIAN  99999
#define STRING_BUFFER_CREATE 100
#define DIVISION 101
#define ARRAY_CPY 102

int Encoding (void*);
int String_buffer_cmp (const void*, const void*);
int Vice_versa_cmp (const void*, const void*);

struct string_buffer* String_buffer_create (void);
struct string_buffer Formation (struct string_buffer);
string* Division (string_buffer*);

void* Array_cpy (string*, string_buffer*);
void Onegin_result (string*, char**, char**, string_buffer*);

#include "ILab_Onegin_file.c"

#endif


