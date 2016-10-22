#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "shared.h"

/// Amount of memory in MB
#define MEMORY 100

///Page size in MB
#define PAGE_SIZE 1

/**
 * Prints a single process
 * @param p single process to print
 */
void print_process(process p){
	printf("\n Completion Time: %d Arrival Time: %d Process Name: %c%c\n", p.completion_time, p.arrival_time, p.name[0], p.name[1]);
}

/**
 * prints a linked list of processes
 * @param llist beginning of linked list to print
 */
void print_ll(process* llist);

/**
 * Generates a linked list of processes. Arrival time is according to shared.h variables
 * TODO: Add more characters to the alphabet to limit repitition
 * @param list pointer that will point to the beginning of the linkedl ist
 */
void generate_processes(process** list);

int main(){
	srand(time(NULL));
	// Generate Processes
	process* llist;
	generate_processes(&llist);
	print_ll(llist);
	return 0;
}
void generate_processes(process** list){
	process* b_list;
	process* head;
	b_list = malloc(sizeof(process));
	b_list->node = malloc(sizeof(process));
	b_list->name[0] = 'A';
	b_list->arrival_time = rand() % TOTAL_TIME;
	b_list->completion_time = (rand() % 5) + 1;
	head = b_list->node;
	for(int x = 1; x < NUMBER_PROCESS; x++){
		head->name[0] = 'A' + ( x % 24 );
		head->node = malloc(sizeof(process));
		head->arrival_time = rand() % TOTAL_TIME;
		head->completion_time = (rand() % 5) + 1;
		head = head->node;
	}
	free(head);
	*list = b_list;
	return;
}

void print_ll(process* list){
	process* head;
	for(int x = 0; x < NUMBER_PROCESS; x++){
		if(list == NULL) break;
		printf("Name: %c Completion Time: %d\n", head->name[0], head->completion_time);
		head = head->node;
	}
}