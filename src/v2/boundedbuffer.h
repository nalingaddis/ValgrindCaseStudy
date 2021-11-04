#ifndef BOUNDED_BUFFER
#define BOUNDED_BUFFER
#define BUFFER_SIZE 80

#include <semaphore.h>

typedef struct BoundedBuffer {
    char buffer[BUFFER_SIZE];
    int put;
    int get;
    sem_t empty, full;
} BoundedBuffer;

void init(BoundedBuffer* buffer);
void put(BoundedBuffer* buffer, char c);
char get(BoundedBuffer* buffer);

#endif