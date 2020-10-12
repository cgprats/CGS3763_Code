#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
int main() {
	pid_t pid;
	int inPipe[2];
	int outPipe[2];
	char inputStr[100];
	scanf("%s", inputStr);
	pipe(inPipe);
	pipe(outPipe);
	pid = fork();
	if (pid > 0) {
		char outputStr[100];
		close(inPipe[0]);
		write(inPipe[1], inputStr, strlen(inputStr) + 1);
		close(inPipe[1]);
		wait(NULL);
		close (outPipe[1]);
		read(outPipe[0], outputStr, strlen(inputStr) + 1);
		printf("%s\n", outputStr);
	}
	else if (pid == 0) {
		char outputStr[100];
		close(inPipe[1]);
		read(inPipe[0], outputStr, strlen(inputStr) + 1);
		for (unsigned int i = 0; i < strlen(outputStr); i++) {
			if (inputStr[i] >= 'A' && inputStr[i] <='Z') {
				outputStr[i] = inputStr[i] + 32;
			}
			else {
				outputStr[i] = inputStr[i] - 32;
			}
		}
		close(inPipe[0]);
		close(outPipe[0]);
		write(outPipe[1], outputStr, strlen(outputStr) + 1);
		close(outPipe[1]);
		exit(0);
	}
}
