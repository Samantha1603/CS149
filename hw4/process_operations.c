#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "shared.h"
#include "process_operations.h"
#include "page_operations.h"

void generate_processes(process** list){
	process* b_list;
	process* head;
	b_list = malloc(sizeof(process));
	b_list->next = malloc(sizeof(process));
	//b_list->name[0] = 'A';
	//b_list->arrival_time = rand() % TOTAL_TIME;
	//b_list->completion_time = (rand() % 5) + 1;
	//b_list->num_page_in_freelist = 0;
	head = b_list;//->next?
	for(int x = 0; x < NUMBER_PROCESS; x++){
		head->name[0] = 'A' + ( x % 26 );
		head->next = malloc(sizeof(process));
		head->arrival_time = (rand() % TOTAL_TIME) * 10; // Unit of quanta. 1 quata = 100ms
		head->page_size = rand() % 4;
		head->num_page_in_freelist = 0;
		switch(head->page_size){
			case 0: head->page_size = 5;
					break;
			case 1: head->page_size = 11;
					break;
			case 2: head->page_size = 17;
					break;
			case 3: head->page_size = 31;
					break;
			default: head->page_size = 5;
					break;
		}
		head->last_reference = 0;
		head->completion_time = ((rand() % 5) + 1) * 10; // Unit of quanta. 1 quata = 100ms
		head->pagesowned = calloc(head->page_size, sizeof(page));
		head = head->next;
	}
	head->next = NULL;
	//free(head); needed?
	*list = b_list;
	return;
}

void executeProcesses(process* list, page* list)
{
	process* head = list;
	for(int i = 0; i < NUMBER_PROCESS; i++)
	{
		if( process_head->completion_time > 0 && currentQuanta >= Process.arrival_time &&){
			if(find_4FreePages){
				startProcess();
				currentQuanta++;
			}
			else{
				blockAllOtherProcesses();
				currentQuanta++;
			}
		}
		else{
			currentQuanta++;
		}
	}
}

//When ever a process finishes, it releases its pages. 
void whenProcessFinishes()
{
//release pages from this passed in process
}

//if there are not 4 available pages, then block all other processes until a process finishes.
//Call this function from 4 available pages?
void blockAllOtherProcesses(process* list)
{
	process* head = list;
	//iterate through processes that have arrival_time <= currentQuanta
	for(int i = 0; i < NUMBER_PROCESS; i++)
	{
		head->blocked = 1;
		head = head->next;
		//if(traverse->arrival_time <= currentQuanta){}
		//currentQuanta++;
	}
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
	int length = 0;
	while(node != NULL){
		node = node->next;
		length++;
	}
	length--;

	//p1 = sort_pll_r(b_list, 0, length / 2);
	//p2 = sort_pll_r(b_list, (length / 2) + 1, length);

	p1 = sort_pll_r(b_list, 0, length);
	*list = p1;
	return;
}

process* sort_pll_r(process* list, int lo, int hi){
	process* p1 = list;
	if(hi - lo < 1) return p1;
	process* p2 = list;
	if(hi - lo == 1){
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

void print_process_pages(process p){
	for(int x = 0; x < p.num_page_in_freelist; x++){
		printf("page number: %d\n", p.pagesowned[x].pageNumber);
	}
	return;
}

static void swap(process* a, process* b){
	if(a->completion_time == 0 || b->completion_time == 0) return;
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