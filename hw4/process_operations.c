#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "shared.h"
#include "process_operations.h"

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
		head->name[0] = 'A' + ( x % 26 );
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
		printf("Name: %c Completion Time: %d Arrival Time: %02d\n", head->name[0], head->completion_time, head->arrival_time);
		head = head->next;
	}
}

void print_process(process p){
	printf("\n Completion Time: %d Arrival Time: %d Process Name: %c%c\n", p.completion_time, p.arrival_time, p.name[0], p.name[1]);
}

void sort_pll(process* list){
	process* b_list = list;
	process* head = b_list;
	process* p = &*head;
	process* lo = &*head; // no need for previous because lo doesnt compare, and next is already available in the struct
	process* lo_prev = NULL;
	int lo_count = 0;
	process* hi; int hi_count;
	process* hi_prev;
	int counter = 0;
	while(p != NULL){
		counter++;
		p = p->next;
	}
	counter -= 2;
	//free(p); needed?

	hi_prev = &*head;
	for(int x = 0; x < counter - 1; x++){
		hi_prev = &*(hi_prev->next);
		hi_count = x;
	}
	hi = &*(hi_prev->next);

	//initial swap, tests if the first and last members are incorrect. Special cases because
	//there is no previous to the beginning and the beginning of the list, b_list, must be set to the new value
	printf("Print hi and prev: HI - %c PREV: %c\n", hi->name[0], hi_prev->name[0]);
	if(hi->arrival_time < lo->arrival_time){
		printf("Test HI arrival: %d LO arrival: %d\n", hi->arrival_time, lo->arrival_time);
		hi_prev->next = &*lo;
		printf("hi_prev->next set to lo\n");
		p = &*(lo->next);
		printf("temp set to lo->next\n");
		lo->next = &*(hi->next);
		printf("lo->next set to hi->next\n");
		hi->next = &*p;
		printf("hi->next set to temp\n");
		if(lo_prev != NULL) lo_prev->next = &*hi;

		//switching pointer names. After this switch, we can count on lo, being the element with a lower arrival time
		// than the hi pointer
		p = hi;
		hi = lo;
		lo = p;
		b_list = lo;
	}	
	// All pointers should be set up start sorting. We will be comparing based on next.
	//  This eliminates the need for a "previous" pointer
	sort_pll_r(&b_list, 0, counter);
	//sort_pll_r(&b_list, (counter / 2), counter);
	print_ll(b_list);
	return;
}

void sort_pll_r(process** list, int lo, int hi){
	if(hi - lo <= 1) return;
	if(hi - lo == 2){
		process** p1;
		process** p2;
		process* p3 = *list;
		for(int x = 0; x < lo - 1; x++){
			p3 = p3->next;
		}
		p1 = &p3;
		p3 = *list;
		for(int x= 0; x < hi - 1; x++){
			p3 = p3->next;
		}
		p2 = &p3;
		if((*p1)->next->arrival_time > (*p2)->next->arrival_time){
			printf("swapping: ");
			print_process(*((*p2)->next));
			print_process(*((*p1)->next));

			p3 = (*p2)->next;
			(*p2)->next = (*p1)->next;
			(*p1)->next = p3->next;

			p3 = (*p1)->next->next;
			(*p1)->next->next = (*p2)->next->next;
			(*p2)->next->next = p3;
		}
		return;
	}
	printf("Hi: %d, Lo: %d\n", hi, lo);
	printf("Hi After %d Lo: %d\n", (hi-lo) / 2, lo);

	sort_pll_r(&(*list), lo, (hi+lo) / 2);
	sort_pll_r(&(*list), ((hi+lo) / 2) + 1, hi);
	return;
}