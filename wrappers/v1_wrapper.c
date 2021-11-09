#include <stdio.h>
#include "../valgrind/include/valgrind.h"

char I_WRAP_SONAME_FNNAME_ZU(Za, getchar)()
{
    char result;
    OrigFn fn;
    VALGRIND_GET_ORIG_FN(fn);
    CALL_FN_W_v(result, fn);
    printf("getchar -> %c\n", result);
    return result;
}

void I_WRAP_SONAME_FNNAME_ZU(Za, putchar)(char input)
{
    OrigFn fn;
    VALGRIND_GET_ORIG_FN(fn);
    printf("putchar -> %c\n", input);
    //CALL_FN_v_W(fn, input);
}