#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
int main() {
	pid_t pid = fork();
	if (pid > 0) {
		printf("I am the Parent. I will sleep for 10 seconds\n");
		sleep(10);
	}
	else {
		printf("I am the child. I will exit while my parent is sleeping and become a zombie\n");
		exit(0);
	}
}
