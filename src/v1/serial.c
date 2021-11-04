/* Serial Solution

Problem: Given a string input, replace all ' ' with newlines and all '**' with '^' then print the processed output in lines of length 80

*/

#include <stdio.h>

#define TRUE 1
#define FALSE 0
#define LINE_LENGTH 80

void flush(char* buffer) {
	for(int i=0; i<LINE_LENGTH; i++) {
		putchar(*buffer);
		buffer++;
	}
	putchar('\n');
}

int main() {
	char buffer[LINE_LENGTH], c;
	int i = 0;

	c = getchar();
	while(TRUE) {		
		switch(c) {
			case EOF: 
				return 0;
			case '\n': 
				buffer[i] = ' '; 
				break;
			case '*': 
				if(i > 0 && buffer[i-1] == '*') { 
					i--; 
					buffer[i] = '^';
				} else {
					buffer[i] = '*';
				}
				break;
			default: 
				buffer[i] = c;
				break;
		}
		i++;

		c = getchar();
		if(i >= LINE_LENGTH) {
			if(buffer[LINE_LENGTH-1] == '*' && c == '*') {
				buffer[LINE_LENGTH-1] = '^';
				c = getchar();
			}

			flush(buffer);
			i = 0;
		}
	}
}

