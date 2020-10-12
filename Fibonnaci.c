#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
int sequence[1000000];
void *fibonnacciGenerator(void* argNum) {
	int number = (int)argNum;
	for (int i = 0; i < number; i++) {
		if (i == 0) {
			sequence[i] = 0;
		}
		else if (i == 1) {
			sequence[i] = 1;
		}
		else {
			sequence[i] = sequence[i - 1] + sequence [i - 2];
		}
	}
}
int main(int argc, char *argv[]) {
	int number = atoi(argv[1]);
	pthread_t fibonacci;
	pthread_create(&fibonacci, NULL, fibonnacciGenerator, (void *)number);
	pthread_join(fibonacci, NULL);
	pthread_join(fibonacci, NULL);
	for (int i = 0; i < number; i++) {
		printf("%d\n", sequence[i]);
	}
}
