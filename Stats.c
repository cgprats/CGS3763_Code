#include <stdio.h>
#include <pthread.h>
int numbers[1000];
int numberCount;
void *average() {
	int sum = 0;
	for (int i = 0; i < numberCount; i++) {
		sum += numbers[i];
	}
	int average = sum / numberCount;
	printf("The average value is %d\n", average);
}
void *max() {
	int max = numbers[0];
	for (int i = 0; i < numberCount; i++) {
		if (numbers[i] > max) {
			max = numbers[i];
		}
	}
	printf("The maximum value is %d\n", max);
}
void *min() {
	int min = numbers[0];
	for (int i = 0; i < numberCount; i++) {
		if (numbers[i] < min) {
			min = numbers[i];
		}
	}
	printf("The minimum value is %d\n", min);
}
int main(int argc, char *argv[]) {
	numberCount = argc - 1;
	for (int i = 0; i < numberCount; i++) {
		numbers[i] = atoi(argv[i + 1]);
	}
	pthread_t averageThread;
	pthread_t maxThread;
	pthread_t minThread;
	pthread_create(&averageThread, NULL, average, NULL);
	pthread_create(&maxThread, NULL, max, NULL);
	pthread_create(&minThread, NULL, min, NULL);
	pthread_join(averageThread, NULL);
	pthread_join(maxThread, NULL);
	pthread_join(minThread, NULL);
}
