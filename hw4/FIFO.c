#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "shared.h"
#include "page_operations.h"
#include "FIFO.h"



page* swapWithOldestPageFIFO(page** pagelist, process* p1, int inMemoryTime, int pageNumber) {

	page* head = *pagelist;
	page* oldestPage = malloc(sizeof(page));
	oldestPage->inMemoryTime = 50; //max deafult

	page insert;
	insert.status=1;
	insert.inMemoryTime = inMemoryTime;
	insert.process_owner = p1;
	insert.pageNumber = pageNumber;
	//printf("\nCCCCCC\n");

	for (int i = 0; i < NUMBER_PAGES; i++) {
		//printf("\nddd\n");

		if (head->inMemoryTime < oldestPage->inMemoryTime) {
			oldestPage = head;
		}
		head = head->next;
		if (head->next == NULL) head = *pagelist;
	}

	printf("\nOLDEST PAGE: %d FROM PROCESS %c\n", oldestPage->inMemoryTime, oldestPage->process_owner->name[0]);
	head = *pagelist;
	for (int i = 0; i < NUMBER_PAGES; i++) {
		printf("\n%d\n", i);
		if (head->process_owner->name[0] == oldestPage->process_owner->name[0] &&
			head->inMemoryTime == oldestPage->inMemoryTime) {
			printf("\nMEM TIME IS: %d, \n", inMemoryTime);
			(*head).status = 1;
			(*head).inMemoryTime = inMemoryTime;
			(*head).process_owner = p1;
			(*head).pageNumber = pageNumber;
			//insert.next = head->next;
			return oldestPage;
		}
		head = head->next;
	}
	//print_pages(*pagelist);
	printf("\nOUT OF LOOP\n");
	return oldestPage;
}

void runFIFO(process** prolist, page** pagelist) {

	int currentQuanta = 0;
	bool done = false;
	int isDone = 0;
	process* process_head = *prolist;
	page* page_head = *pagelist;

	// hm just solo process one at a time for now. we need threads for all the processes to run at once

	while (currentQuanta < 600) { // 600 quanta = 1 minute (max)

		for (int i = 0; i < NUMBER_PROCESS; i++) {

			if (process_head->arrival_time <= currentQuanta) {
				printf("\nQUANTA: %d\n", currentQuanta);
				printf("\n\n COMPLETION TIME: %d \n", process_head->completion_time);

				if (process_head->pagesowned[0].status == 1) { // Not first referencing made
					process_head->last_reference = getPageReference(process_head->page_size, process_head->last_reference); // The next page to reference
				}

				if (!isPageAlreadyInMemory(process_head, process_head->last_reference)) {
					// Page in not yet in memory. Add to free list


					//if(find_4FreePages(*pagelist)) {
						// Found 4 free pages. Can insert into free list.

						if (!isMemoryFull(*pagelist)) {
							addPageToMemory(pagelist, process_head, currentQuanta, process_head->last_reference);
							page_head = page_head->next;
						} else {	
							printf("\n\n MEMORY FULL, DO SWAP \n\n");	
							swapWithOldestPageFIFO(pagelist, process_head, currentQuanta, process_head->last_reference);
						}
					//} else {
						// WAIT for process to finish
						//print_pagesLL(*pagelist);
						//printf("\n\n NO FREE FOUR PAGES \n\n");
						//break;
					//}
				} else {
					// Page is already in memory. a hit
					printf("\nPAGE ALREADY IN MEMORY\n\n");
				}

				process_head->completion_time -= 1;

				if (process_head->completion_time <= 0) {
					// Remove process
					printf("\nPROCESS DONE\n\n");
				} 

				printf("\nQUANTA here: %d\n", currentQuanta);
				printf("\nPRINTING1:\n");
				process_head = process_head->next;
				print_pages(*pagelist);
				if (process_head->next == NULL) process_head = *prolist; // wrap around to head process again..
			} 			
		}
		if (currentQuanta >= 200) {
			break;
		}
		currentQuanta += 1;


	}
}

bool isPageAlreadyInMemory(process* p1, int pageNumber) {

	bool isInMemory = false;

	for(int x = 0; x < p1->num_page_in_freelist ; x++){
		if(p1->pagesowned[x].pageNumber == pageNumber) isInMemory = true;
	}
	return isInMemory;
}


bool isMemoryFull(page* llist){
	int pagesFound = 0;
	page* head = llist;
	bool isMemFull = false;

	for (int x = 0; x < NUMBER_PAGES; x++) {
	    if(head->status == 1) {
	        pagesFound++;
	    }
	    head = head->next;
	}
	
	if (pagesFound >= NUMBER_PAGES){
		isMemFull = true;
	} 

	return isMemFull;
}


void print_pages(page* llist) {
	
	page* head = llist;
	for(int x = 0; x < NUMBER_PAGES; x++){
		if(head == NULL) break;

		printf("[(#: %d),", head->pageNumber);
		if (head->status == 1) {
			printf("(P: %c%c)] ", head->process_owner->name[0], head->process_owner->name[1]);
		} else {
			printf("(P:.)] ");
		}
		
		//printf("Status: %d \t Page Number: %d", head->status, head->pageNumber);
		//if(head->status == 1) printf(" Page Owner: %c\n", head->process_owner->name[0]);
		//else printf(" Page Owner: Free\n");
		head = head->next;
	}
}

