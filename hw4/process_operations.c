#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "shared.h"

void generate_processes(process** list){
	process* b_list;
	process* head;
	b_list = malloc(sizeof(process));
	b_list->next = malloc(sizeof(process));
	b_list->name[0] = 'A';
	b_list->arrival_time = rand() % TOTAL_TIME;
	b_list->completion_time = (rand() % 5) + 1;
	head = b_list->next;
	for(int x = 1; x < NUMBER_PROCESS; x++){
		head->name[0] = 'A' + ( x % 24 );
		head->next = malloc(sizeof(process));
		head->arrival_time = rand() % TOTAL_TIME;
		head->completion_time = (rand() % 5) + 1;
		head = head->next;
	}
	head->next = NULL;
	//free(head); needed?
	*list = b_list;
	return;
}

void print_ll(process* list){
	process* head = list;
	for(int x = 0; x < NUMBER_PROCESS; x++){
		if(head == NULL) break;
		printf("Name: %c Completion Time: %d\n", head->name[0], head->completion_time);
		head = head->next;
	}
}

void print_process(process p){
	printf("\n Completion Time: %d Arrival Time: %d Process Name: %c%c\n", p.completion_time, p.arrival_time, p.name[0], p.name[1]);
}

void sort_pll(process* list){
	process* b_list = list;
	process* head = b_list;
	process* p = head;
	process* lo = head; // no need for previous because lo doesnt compare, and next is already available in the struct
	process* lo_prev;
	int lo_count = 0;
	process* hi; int hi_count;
	process* hi_prev;
	int counter = 0;
	while(p != NULL){
		counter++;
		p = p->next;
	}
	//free(p); needed?

	/*hi_prev = head;
	for(int x = 0; x < counter; x++){
		hi_prev = hi_prev->next;
		hi_count = x;
	}
	hi = hi_prev->next;

	// All pointers should be set up start sorting
	for(int x = 0; x < counter; x++){
		if(hi->arrival_time < lo->arrival_time){
			hi_prev->next = lo;
			p = lo->next;
			lo->next = hi->next;
			hi->next = p;
			if(lo_prev != NULL) lo_prev->next = hi;
		}
	}*/
	return;
}
