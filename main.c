#include <stdio.h>
#include <stdlib.h>
#include "FCFS.h"
#include "RR.h"
#include "process_producer.h"
#include "Sorter.h"
#include "Calculation.h"
#include "ShortestJobFirst.h"
#include <time.h>
//TODO: CONGREGATE DEFINE DEFINTIONS IN OWN HEADERFILE

void printProcessTracker();
void printFCFSOrder(struct process* plist);

int main(){
	int seed = time(NULL);
	float runtime;
	srand(seed);
	struct process* list;
	struct process* copy_list = malloc(sizeof(struct process) * NUM_PROCESS);
	CreateProcesses(&list);
	PrintProcessList(list);
	memcpy(copy_list, list, sizeof(struct process) * NUM_PROCESS);
	SortBy(&copy_list, 0); //The input num decides what field to sort by 0 - arrival time; 1 - service time; 2 - priority; 3 - actual start; 4 - end time
	
	
	printf("\n\n***********FCFS****************\n\n");
	printProcessTracker();
	printFCFSOrder(copy_list);

	printf("\n\n***********Round Robin**************\n\n");
	RoundRobin(list);

	shortestJobFirst(list);
	return 1;
}

/*
* Blueprint to track where each process is during the 100 quatum time frame
* Can tell some processes don't start at arrival time because another process is still running
*/
void printProcessTracker() {
	printf("\nProcess Tracker (Hold control key and hit - key to zoom out in terminal to see)\n"); // need a more elegant solution than this
	for (int i = 0; i < MAX_QUANTA; i++) {
		printf("%d ", i);
	}
	printf("\n");
}


void printFCFSOrder(struct process* plist) {

	int process_ran;
	char* charArray = getFCFSOrder(&plist, &process_ran);

	// Adjust to add extra spaces to match printProcessTracker();
	// Char array doesn't have extra spaces to accommodate the difference
	for (int i = 0; i < CHAR_ARRAYMAX; i++) {
		if (charArray[i] == ' ' && i < 10) { 
			printf("  ");
		} else if (charArray[i] == ' ' && i >= 10) {
			printf("   ");
		} else if (i < 10) {
			printf("%c ", charArray[i]);
		} else {
			printf("%c  ", charArray[i]);
		}
	}
	printf("\n");
	// Size is now the # of processes that completed its process 
	printf("Average response time: %.2f\n", calAverageResponse(plist, process_ran));
	printf("Average waiting time: %.2f\n", calAverageWaiting(plist, process_ran));
	printf("Average turnaround time: %.2f\n", calAverageTurnaround(plist, process_ran));
	printf("Throughput: %d\n", process_ran);
	free(charArray);
}

void printShortestJobFirstOrder(struct process plist) {

	int process_ran;
	char* charArray = shortestJobFirst(&plist);

	// Adjust to add extra spaces to match printProcessTracker();
	// Char array doesn't have extra spaces to accommodate the difference
	for (int i = 0; i < CHAR_ARRAYMAX; i++) {
		if (charArray[i] == ' ' && i < 10) { 
			printf("  ");
		} else if (charArray[i] == ' ' && i >= 10) {
			printf("   ");
		} else if (i < 10) {
			printf("%c ", charArray[i]);
		} else {
			printf("%c  ", charArray[i]);
		}
	}
	free(charArray);
}