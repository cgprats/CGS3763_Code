#include <pthread.h>
#include <stdio.h>
void *primesUnder(void* argNum) {
	int number = (int) argNum;
	int prime = 1;
	for (int i = 1; i <= number; i++) {
		prime = 1;
		for (int j = 2; j < i; j++) {
			if ((i % j) == 0) {
				prime = 0;
			}
		}
		if (prime == 1) {
			printf("%d\n", i);
		}
	}
}
int main(int argc, char *argv[]) {
	int number = atoi(argv[1]);
	pthread_t primesThread;
	pthread_create(&primesThread, NULL, primesUnder, (void *) number);
	pthread_join(primesThread, NULL);
}
