#include <stdio.h>
#include <pthread.h>
#include "boundedbuffer.h"

void* func1(void* arg);
void* func2(void* arg);
void* func3(void* arg);
void* func4(void* arg);

BoundedBuffer buffer1, buffer2, buffer3;

int main() {
    init(&buffer1);
    init(&buffer2);
    init(&buffer3);

    pthread_t threads[4];

    int error;
    if(error = pthread_create(&threads[0], NULL, &func1, NULL)) return error;
    if(error = pthread_create(&threads[1], NULL, &func2, NULL)) return error;
    if(error = pthread_create(&threads[2], NULL, &func3, NULL)) return error;
    if(error = pthread_create(&threads[3], NULL, &func4, NULL)) return error;

    for(int i = 0; i < 4; i++) pthread_join(threads[i], NULL);
    return 0;
}

void* func1(void* arg) {
    char c = 'a';
    while(c != EOF) {
        c = getchar();
        put(&buffer1, c);
    }
}

void* func2(void* arg) {
    char c = 'a';
    while(c != EOF) {
        c = get(&buffer1);
        if(c == '\n') c = ' ';
        put(&buffer2, c);
    }
}

void* func3(void* arg) {
    char c = 'a';
    while(c != EOF) {
        c = get(&buffer2);
        if(c == '*') {
            c = get(&buffer2);
            if(c == '*') {
                c = '^';
            } else {
                put(&buffer3, '*');
            }
        }
        put(&buffer3, c);
    }
}

void* func4(void* arg) {
    char buffer[BUFFER_SIZE];
    int i;
    char c;

    c = get(&buffer3);

    while(c != EOF) {
        buffer[i] = c;
        i++;

        if(i >= BUFFER_SIZE) {
            for(i = 0; i < BUFFER_SIZE; i++) putchar(buffer[i]);
            putchar('\n');
            i = 0;
        }

        c = get(&buffer3);
    }
}