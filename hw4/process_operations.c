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
	printf("\n Arrival Time: %d Completion Time: %d Process Name: %c%c\n", p.arrival_time, p.completion_time, p.name[0], p.name[1]);
}

void sort_pll(process** list){
	process* b_list = *list;
	process* node = *list;
	process* p1;
	process* p2;
	int length = 0;
	while(node != NULL){
		node = node->next;
		length++;
	}
	length--;

	//p1 = sort_pll_r(b_list, 0, length / 2);
	//p2 = sort_pll_r(b_list, (length / 2) + 1, length);

	p1 = sort_pll_r(b_list, 0, length);

	printf("after sorted:\n");
	print_ll(p1);
	//print_ll(p2);


	printf("Sort done. Checking...\n");
	process* p_tot = malloc(sizeof(process) * length);
	int p2_bounds = length - (length / 2);
	int p1_bounds = length / 2;
	/*for(int x = 0; x < length; x++){
		if(p1 == NULL){
			p_tot[x] = *p2;
			p2_bounds--;
			p2 = p2->next;
		}
		else if(p2 == NULL){
			p_tot[x] = *p1;
			p1_bounds--;	
			p1 = p1->next;
		}
		else if(p1->arrival_time < p2->arrival_time && p1_bounds > 0){
			p_tot[x] = *p1;
			p1 = p1->next;
			p1_bounds--;
		}
		else if(p1->arrival_time > p2->arrival_time && p2_bounds > 0){
			p_tot[x] = *p2;
			p2 = p2->next;
			p2_bounds--;
		}
		else if(p1_bounds < 1){
			p_tot[x] = *p2;
			p2 = p2->next;
			p2_bounds--;
		}
		else{
		p_tot[x] = *p1;
		p1 = p1->next;
		p1_bounds--;
		}
		if( x > 0) p_tot[x - 1].next = &p_tot[x];
	}

	p_tot[length - 1].next = NULL;
	print_ll(p_tot);*/
	return;
}

process* sort_pll_r(process* list, int lo, int hi){
	process* p1 = list;
	if(hi - lo < 1) return p1;
	process* p2 = list;
	if(hi - lo == 1){
		process temp; process temp2;
		for(int x = 0; x < lo; x++) p1 = p1->next;
		for(int x = 0; x < hi; x++){
			 if(p2 == NULL){
			 	p1->next = NULL;
			 	return p1;
			 }
			 p2 = p2->next;
		}
		//printf("Acquire p1 and 2\n");
		//print_process(*p1);
		//print_process(*p2);
		if(p1->arrival_time > p2->arrival_time){
			swap(&*p1, &*p2);

			//printf("after swap:\n");
			//print_process(*p1);
			//print_process(*p2);	
		}
		return p1;
	}
	p1 = sort_pll_r(list, lo, (hi+lo) / 2);
	p2 = sort_pll_r(list, ((hi+lo) / 2), hi);
	int p1_bounds = ((hi+lo) / 2) - lo;
	int p2_bounds = hi - (((hi+lo) / 2));
	process* p_tot = malloc(sizeof(process) * (hi-lo));
	process temp;
	for(int x = 0; x < hi - lo; x++){
		if(p1 == NULL){
			p_tot[x] = *p2;
			p2_bounds--;
			p2 = p2->next;
		}
		else if(p2 == NULL){
			p_tot[x] = *p1;
			p1_bounds--;	
			p1 = p1->next;
		}
		else if(p1->arrival_time < p2->arrival_time && p1_bounds > 0){
			p_tot[x] = *p1;
			p1 = p1->next;
			p1_bounds--;
		}
		else if(p1->arrival_time > p2->arrival_time && p2_bounds > 0){
			p_tot[x] = *p2;
			p2 = p2->next;
			p2_bounds--;
		}
		else if(p1_bounds < 1){
			p_tot[x] = *p2;
			p2 = p2->next;
			p2_bounds--;
		}
		else{
		p_tot[x] = *p1;
		p1 = p1->next;
		p1_bounds--;
		}
		if( x > 0) p_tot[x - 1].next = &p_tot[x];
	}
	p_tot[(hi-lo) - 1].next = NULL;

	return p_tot;
}

static void swap(process* a, process* b){
	process temp = *a;
	a->name[0] = b->name[0];
	a->name[1] = b->name[1];
	a->page_size = b->page_size;
	a->arrival_time = b->arrival_time;
	a->completion_time = b->completion_time;

	b->name[0] = temp.name[0];
	b->name[1] = temp.name[1];
	b->page_size = temp.page_size;
	b->arrival_time = temp.arrival_time;
	b->completion_time = temp.completion_time;
}