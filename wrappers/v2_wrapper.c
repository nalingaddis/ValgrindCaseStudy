#include <stdio.h>
#include <pthread.h>
#include <stdarg.h>

#include "../valgrind/include/valgrind.h"
#include "../src/v2/boundedbuffer.h"

void trace(const char* format, ...) {
    printf("%ld - Thread: %lu - ",
        time(NULL),
        pthread_self()
    );

    va_list args;
    va_start(args, format);
    vprintf(format, args);

    printf("\n");
}

// pthread_create
// ZZ enables Z encoding (i.e. Za ==> '*', Zd ==> '.'), ZU includes no encoding
int I_WRAP_SONAME_FNNAME_ZZ(libpthreadZdsoZd0, pthreadZucreateZAZa)
(pthread_t *restrict thread, const pthread_attr_t *restrict attr, void *(*start_routine)(void *), void *restrict arg) 
{
    OrigFn fn;
    VALGRIND_GET_ORIG_FN(fn);

    int result;
    CALL_FN_W_WWWW(result, fn, thread, attr, start_routine, arg);

    trace("pthread_create -> %u", *thread);
    return result;
}

int I_WRAP_SONAME_FNNAME_ZZ(libpthreadZa, pthreadZujoinZa)
(pthread_t thread, void **retval) 
{
    OrigFn fn;
    VALGRIND_GET_ORIG_FN(fn);

    int result;
    CALL_FN_W_WW(result, fn, thread, retval);

    trace("pthread_join -> %u", thread);
    return result;
}

// init
void I_WRAP_SONAME_FNNAME_ZU(NONE, init)
(BoundedBuffer* buffer) 
{
    OrigFn fn;
    VALGRIND_GET_ORIG_FN(fn);

    trace("init");

    CALL_FN_v_W(fn, buffer);
}

// put
void I_WRAP_SONAME_FNNAME_ZU(NONE, put)
(BoundedBuffer* buffer, char c) 
{
    OrigFn fn;
    VALGRIND_GET_ORIG_FN(fn);

    trace("put -> %c", c);

    CALL_FN_v_WW(fn, buffer, c);
}

// get
char I_WRAP_SONAME_FNNAME_ZU(NONE, get)
(BoundedBuffer* buffer) 
{
    OrigFn fn;
    VALGRIND_GET_ORIG_FN(fn);

    char result;

    CALL_FN_W_W(result, fn, buffer);

    trace("get -> %c", result);

    return result;
}

// sem_init
int I_WRAP_SONAME_FNNAME_ZU(Za, sem_init)
(sem_t *sem, int pshared, unsigned int value) 
{
    OrigFn fn;
    VALGRIND_GET_ORIG_FN(fn);

    int result;

    trace("sem_init -> id: %p, value: %u", sem, value);

    CALL_FN_W_WWW(result, fn, sem, pshared, value);
    return result;
}

// sem_wait
int I_WRAP_SONAME_FNNAME_ZU(Za, sem_wait)
(sem_t *sem) 
{
    OrigFn fn;
    VALGRIND_GET_ORIG_FN(fn);

    int result;

    sem_getvalue(sem, &result);
    trace("sem_wait -> id: %p, value: %u", sem, result);

    CALL_FN_W_W(result, fn, sem);
    return result;
}

// sem_post
int I_WRAP_SONAME_FNNAME_ZU(Za, sem_post)
(sem_t *sem) 
{
    OrigFn fn;
    VALGRIND_GET_ORIG_FN(fn);

    int result;

    sem_getvalue(sem, &result);
    trace("sem_post -> id: %p, value: %u", sem, result);

    CALL_FN_W_W(result, fn, sem);
    return result;
}