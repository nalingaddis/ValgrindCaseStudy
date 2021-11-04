/* Pipes Solution

Problem: Given a string input, replace all ' ' with newlines and all '**' with '^' then print the processed output in lines of length 80
*/

#include <stdio.h>
#include <unistd.h>

#define READ 0
#define WRITE 1
#define BUFFER_LENGTH 80

void process1(int output);
void process2(int input, int output);
void process3(int input, int output);
void process4(int input);

int main() { 
    int pipe1[2], pipe2[2], pipe3[3];

    int error;

    if(error = pipe(pipe1)) return error;
    if(error = pipe(pipe2)) return error;
    if(error = pipe(pipe3)) return error;

    int pid;
    if(pid = fork()) { process1(pipe1[WRITE]); return 0; }
        else if(pid < 0) return pid;
    if(pid = fork()) { process2(pipe1[READ], pipe2[WRITE]); return 0; } 
        else if(pid < 0) return pid;
    if(pid = fork()) { process3(pipe2[READ], pipe3[WRITE]); return 0; }
        else if(pid < 0) return pid;
    if(pid = fork()) { process4(pipe3[READ]); return 0; }
        else if(pid < 0) return pid;
    
    return 0;
}

void process1(int output) {
    char c;
    while(1) {
        c = getchar();
        write(output, &c, sizeof(char));

        if(c == EOF) return;
    }
}

void process2(int input, int output) {
    char c;
    while(1) {
        read(input, &c, sizeof(char));
        if(c == '\n') c = ' ';
        write(output, &c, sizeof(char));
        
        if(c == EOF) return;
    }
}

void process3(int input, int output) {
    char c;
    const char ast = '*';
    while(1) {
        read(input, &c, sizeof(char));

        if(c == '*') {
            read(input, &c, sizeof(char));
            if(c == '*') {
                c = '^';
            } else {
                write(output, &ast, sizeof(char));
            }
        }

        write(output, &c, sizeof(char));

        if(c == EOF) return;
    }
}

void process4(int input) {
    char buffer[BUFFER_LENGTH];
    char c;
    int i;

    while(1) {
        read(input, &c, sizeof(char));

        buffer[i] = c;
        i++; 

        if(i >= BUFFER_LENGTH) {
            for(i = 0; i<BUFFER_LENGTH; i++) putchar(buffer[i]);
            putchar('\n');
            i = 0;
        }

        if(c == EOF) return;
    }
}