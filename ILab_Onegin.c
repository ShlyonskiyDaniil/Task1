#include "ILab_Onegin.h"


int main() {
    string_buffer* bufpar_ptr = String_buffer_create();

    if (bufpar_ptr == NULL)
    {
        return STRING_BUFFER_CREATE ;
    }

    string_buffer bufpar = *bufpar_ptr;
    bufpar = Formation(bufpar);

    string *text = Division(&bufpar);

    if (text == NULL)
    {
        return DIVISION;
    }

    char** sort1 = (char**) Array_cpy(text, &bufpar);

    qsort(text, bufpar.nstr, sizeof(string), String_buffer_cmp);
    char** sort_alpha = (char**) Array_cpy(text, &bufpar);

    if (sort_alpha == NULL)
    {
        return ARRAY_CPY;
    }


    qsort(text, bufpar.nstr, sizeof(string), Vice_versa_cmp);

    Onegin_result (text, sort1, sort_alpha, &bufpar);

    free(bufpar.buf);
    free(text);
    free(sort1);
    free(sort_alpha);
}