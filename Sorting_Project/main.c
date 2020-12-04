#include <stdio.h>
#include <pthread.h>
//Declare the List and Calculate its Size
int list[] = {7, 12, 19, 3, 18, 4, 2, 6, 15, 8};
int listSize = sizeof(list) / sizeof(list[0]);
//Function for the Two Sorting Threads
void *SortingThread(void *startIndex) {
	//Declare Variables Needed for Sorting
	int currentIndex = (int)startIndex;
	//int stopIndex = (int)startIndex + (listSize / 2) - 1;
	int stopIndex = listSize - (int)startIndex - 1;
	int temp;
	//Run Sort
	for (; currentIndex < stopIndex; currentIndex++) {
		for (int i = (int)startIndex; i < stopIndex - currentIndex + (int)startIndex; i++) {
			//If Current Item is Larger than the Next One, Swap Them
			if (list[i] > list[i + 1]) {
				temp = list[i];
				list[i] = list[i + 1];
				list[i + 1] = temp;
			}
		}
	}
}
//Function for the Post-Sort Merge Thread
void *MergeThread() {
	//Declare Variables Needed for Merging
	int temp[listSize];
	int i = 0, j = listSize / 2, k = 0;
	//Run Merge
	while (i < (listSize / 2) && j < listSize) {
		//If value in First Half is Less than Corresponding Value in Second Half, Use its Value
		if (list[i] < list[j]) {
			temp[k++] = list[i++];
		}
		//If value in Second Half is Less than Corresponding Value in First Half, Use its Value
		else {
			temp[k++] = list[j++];
		}
	}
	//Add Remaining Elements in First Half
	while (i < (listSize / 2)) {
		temp[k++] = list[i++];
	}
	//Add Remaining Elements in Second Half
	while (j < listSize) {
		temp[k++] = list[j++];
	}
	//Replace the Values in the List with those from the Temporary Array
	for (int i = 0; i < listSize; i++) {
		list[i] = temp[i];
	}
}
//The Main Program
int main() {
	//Declare Initial Variables
	pthread_t sortingThreads[2], mergeThread;
	//Print the Original (Unsorted) Array
	printf("Original (Unsorted) Array: \n");
	for (int i = 0; i < listSize; i++) {
		printf("%d ", list[i]);
	}
	//Run the Sorting Threads
	pthread_create(&sortingThreads[0], NULL, SortingThread, (void *) 0);
	pthread_create(&sortingThreads[1], NULL, SortingThread, (void *) (listSize / 2));
	//Wait for Sorting Threads to Finish
	pthread_join(sortingThreads[0], NULL);
	pthread_join(sortingThreads[1], NULL);
	//Run the Merge Thread
	pthread_create(&mergeThread, NULL, MergeThread, NULL);
	//Wait for Merge Thread to Finish
	pthread_join(mergeThread, NULL);
	//Print the Sorted Array
	printf("\nSorted Array: \n");
	for (int i = 0; i < listSize; i++) {
		printf("%d ", list[i]);
	}
	printf("\n");
	//Return 0 to Cleanly Exit
	return 0;
}
