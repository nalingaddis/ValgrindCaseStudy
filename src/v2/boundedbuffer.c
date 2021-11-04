#include <semaphore.h>
#include <stdio.h>
#include "boundedbuffer.h"

void init(BoundedBuffer* buffer) {
    buffer->put = 0;
    buffer->get = 0;
    sem_init(&(buffer->empty), 0, BUFFER_SIZE);
    sem_init(&(buffer->full), 0, 0);
}

void put(BoundedBuffer* buffer, char c) {
    sem_wait(&(buffer->empty));

    buffer->buffer[buffer->put] = c;
    buffer->put = (buffer->put + 1) % BUFFER_SIZE;

    sem_post(&(buffer->full));
}

char get(BoundedBuffer* buffer) {
    sem_wait(&(buffer->full));

    char result = buffer->buffer[buffer->get];
    buffer->get = (buffer->get + 1) % BUFFER_SIZE;

    sem_post(&(buffer->empty));

    return result;
}