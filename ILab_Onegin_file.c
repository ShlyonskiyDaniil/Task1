#include "ILab_Onegin.h"

int Encoding (void* str)
{
    const int OUTENC = 0;

    char alph[] = {"АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯабвгдеёжзийклмнопрстуфхцчшщъыьэюя"};

    for (int i = 0; i < strlen(alph) - 1; i++)
    {
        if (*((char*)str) == alph[i]) return i + 1;
    }

    return OUTENC;
}



int String_buffer_cmp (const void* struct1_ptr, const void* struct2_ptr)
{
    string* struct_str1 = (string*)struct1_ptr;
    string* struct_str2 = (string*)struct2_ptr;

    char* str1 = struct_str1->str;
    char* str2 = struct_str2->str;

    for(int i = 0; i > -1; i++)
    {
        if(*str1 == '\0')
        {
            return -1;
        }

        if(*str2 == '\0')
        {
            return 1;
        }

        while (Encoding(str1) == 0) str1++;
        while (Encoding(str2) == 0) str2++;

        if (Encoding(str1) != Encoding(str2))
        {
            return Encoding(str1) - Encoding(str2);
        }

        str1++;
        str2++;
    }
    return NOTINRUSSIAN;
}





int Vice_versa_cmp (const void* struct1_ptr, const void* struct2_ptr)
{
    string* struct_str1 = (string*)struct1_ptr;
    string* struct_str2 = (string*)struct2_ptr;

    unsigned int len1 = struct_str1->str_len;
    unsigned int len2 = struct_str2->str_len;

    char* str1 = struct_str1->str + len1 - 1;
    char* str2 = struct_str2->str + len2 - 1;

    while (str1 != struct_str1->str && str2 != struct_str2->str)
    {
        while (Encoding(str1) == 0)
        {
            str1--;
        }

        while (Encoding(str2) == 0)
        {
            str2--;
        }

        if (Encoding(str1) != Encoding(str2))
        {
            return Encoding(str1) - Encoding(str2);
        }

        str1--;
        str2--;
    }

    return NOTINRUSSIAN;
}



struct string_buffer* String_buffer_create (void)
{
    string_buffer bufpar;
    string_buffer* bufpar_ptr = &bufpar;

    bufpar.nchars = 0;
    bufpar.buf = NULL;


    FILE* Onegin = fopen("Data/Onegin.txt", "r");

    if (Onegin == NULL)
    {
        printf("File Onegin can't be opened!\n");
        return NULL;
    }


    // Finding buf size.
    fseek(Onegin, 0, SEEK_END);
    bufpar_ptr->nchars = (unsigned int) ftell(Onegin);


    // Text transfering to buf.
    bufpar_ptr->buf = (char*) calloc(bufpar_ptr->nchars, sizeof(char));

    if (bufpar_ptr->buf == NULL)
    {
        return NULL;
    }

    if (bufpar_ptr->buf == NULL)
    {
        return NULL;
    }

    fseek(Onegin, 0, SEEK_SET);

    if (fread (bufpar_ptr->buf, sizeof(char), bufpar_ptr->nchars, Onegin) != bufpar_ptr->nchars)
    {
        if (feof(Onegin) == 0)
        {
            printf("Premature file ending!\n");
        }
        else printf("File read error!\n");

        return NULL;
    }


    return bufpar_ptr;
}



struct string_buffer Formation (struct string_buffer bufpar)
{
    bufpar.nstr = 0;

    for (int i = 0; i < bufpar.nchars; i++)
    {
        if (bufpar.buf[i] == '\n')
            bufpar.nstr++;

        while (bufpar.buf[i] == '\n')
        {
            bufpar.buf[i] = '\0';
            i++;
        }
    }

    return bufpar;
}



string* Division (string_buffer* bufpar)
{
    struct string* text = (struct stirng*) calloc(bufpar->nstr, sizeof(struct string));

    if (text == NULL)
    {
        return NULL;
    }

    // Заполняем text адресами начала строк и находим длину каждой из них.
    text[0].str = bufpar->buf;
    int j = 1;
    unsigned int length = 0;

    for (int i = 0; i < bufpar->nchars; i++)
    {
        if (bufpar->buf[i] == '\0')
        {
            text[j - 1].str_len = length;

            while (bufpar->buf[i] == '\0') i++;
            text[j].str = bufpar->buf + i;

            j++;

            length = 0;
            continue;
        }

        length++;
    }

    return text;
}



void* Array_cpy (string* text, string_buffer* bufpar)
{
    char** new_array = (char**) calloc(bufpar->nstr, sizeof(char*));

    if (new_array == NULL)
    {
        return NULL;
    }

    for (int i = 0; i < bufpar->nstr; i++)
    {
        new_array[i] = text[i].str;
    }

    return new_array;
}



void Onegin_result (string* text, char** sort1, char** sort_alpha, string_buffer* bufpar)
{
    FILE* result = fopen ("Data/Onegin_result.txt", "w");

    if (result == NULL) printf("Result can not be opened.\n");

    fprintf (result, "--Rhyme sorting:\n\n\n");

    for (int i = 0; i < bufpar->nstr; i++)
    {
        fprintf (result, "%s\n", text[i].str);
    }

    fprintf (result, "\n\n--Alphabet sorting:\n\n\n");

    for (int i = 0; i < bufpar->nstr; i++)
    {
        fprintf (result, "%s\n", sort_alpha[i]);
    }

    fprintf (result, "\n\n--Original:\n\n\n");

    for (int i = 0; i < bufpar->nstr; i++)
    {
        fprintf (result, "%s\n", sort1[i]);
    }

    fclose (result);
}