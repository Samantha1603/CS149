#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "shared.h"
#include "page_operations.h"
#include "FIFO.h"


void runFIFO(process** prolist, page** pagelist) {

	int currentQuanta = 0;
	process* process_head = *prolist;
	page* page_head = *pagelist;

	while (currentQuanta < 600) { // 600 quanta = 1 minute (max)

		for (int i = 0; i < NUMBER_PROCESS; i++) {

			if (process_head->completion_time > 0 && process_head->arrival_time <= currentQuanta) { // Only run that process if its completition if > 0

				//printf("\nPROCESS %c RUNNING \n\n",process_head->name[0]);

				printf("\nQUANTA: %d\n", currentQuanta);
				printf("\n\n COMPLETION TIME: %d \n", process_head->completion_time);

				if (process_head->pagesowned[0].process_owner != NULL) { // Not first referencing made
					printf("\nNOT FIRST TIME IN MEMORY\n");
					process_head->last_reference = getPageReference(process_head->page_size, process_head->last_reference); // The next page to reference
				}

				if (!isPageAlreadyInMemory(process_head, process_head->last_reference)) {
					// Page in not yet in memory. Add to free list

					printf("\nENTER - PAGE %d OF PROCESS %c\n", process_head->last_reference, process_head->name[0]);

					//if(find_4FreePages(*pagelist)) {
						// Found 4 free pages. Can insert into free list.

						if (!isMemoryFull(*pagelist)) {
							addPageToMemory(pagelist, process_head, currentQuanta, process_head->last_reference);
							page_head = page_head->next;
							print_pages(*pagelist);
						} else {	
							printf("\n\n MEMORY FULL, DO SWAP \n\n");	
							swapWithOldestPageFIFO(pagelist, process_head, currentQuanta, process_head->last_reference);
							print_pages(*pagelist);
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
				/*
				printf("\nSIZE CHECKING %d\n", process_head->page_size);
				for(int y = 0; y < process_head->page_size; y++){ // Loop through that process's free array list
					printf("PROCESS %c OWNS PAGE # %d\n", process_head->name[0], process_head->pagesowned[y].pageNumber);
				}*/
				
				process_head->completion_time -= 1;
				 			

				printf("\nSIZE CHECKING %d\n", process_head->page_size);
				for(int y = 0; y < process_head->page_size; y++){ // Loop through that process's free array list
					printf("PROCESS %c OWNS PAGE # %d\n", process_head->name[0], process_head->pagesowned[y].pageNumber);
				}
			}
			process_head = process_head->next;
			if (process_head == NULL) process_head = *prolist; // wrap around to head process again..
		}
		currentQuanta += 1; // Increment 1 quanta, which is
	}
}

void swapWithOldestPageFIFO(page** pagelist, process* p1, int inMemoryTime, int pageNumber) {

	page* head = *pagelist;
	page* oldestPage = getOldestPage(*pagelist);
	page insert;
	insert.status=1;
	insert.inMemoryTime = inMemoryTime;
	insert.process_owner = p1;
	insert.pageNumber = pageNumber;

	for (int i = 0; i < NUMBER_PAGES; i++) {
		if (head->process_owner->name[0] == oldestPage->process_owner->name[0] &&
			head->inMemoryTime == oldestPage->inMemoryTime) {

			removePageFromAProcessArray(oldestPage); // remove that page from that process's free list first
			(*head).status = 1;
			(*head).inMemoryTime = inMemoryTime;
			(*head).process_owner = p1;
			(*head).pageNumber = pageNumber;
		}
		head = head->next;
	}
}

page* getOldestPage(page* pagelist) {

	page* head = pagelist;

	page* oldestPage = malloc(sizeof(page));
	oldestPage = head; //set first page as oldest by default

	for (int i = 0; i < NUMBER_PAGES; i++) {
		if (head->inMemoryTime < oldestPage->inMemoryTime) {
			oldestPage = head;
		}
		head = head->next;
	}
	return oldestPage;
}

bool isMemoryFull(page* llist){
	int pagesFound = 0;
	page* head = llist;
	bool isMemFull = false;

	for (int x = 0; x < NUMBER_PAGES; x++) {
	    if(head->status == 1) {
	        pagesFound++; // Status 1 means page is taken so increment pagesFound
	    }
	    head = head->next;
	}
	
	if (pagesFound >= NUMBER_PAGES){ 
		isMemFull = true;
	} 
	return isMemFull;
}

bool isPageAlreadyInMemory(process* p1, int pageNumber) {

	bool isInMemory = false;

	for(int x = 0; x < p1->page_size; x++){ // Loop through that process's free array list
		//printf("\nPROCESS %c has page number %d\n", p1->name[0], p1->pagesowned[x].pageNumber);
		if(p1->pagesowned[x].pageNumber == pageNumber) {
			//printf("\nPROCESS %c of page number %d is ALREADY IN MEMORY \n", p1->name[0], p1->pagesowned[x].pageNumber);
			isInMemory = true; 
			break;
		}
	}
	return isInMemory;
}

void removePageFromAProcessArray(page* pagelist) {

	page* head = pagelist;
	printf("\n NEED TO EVICT\n");

	for(int x = 0; x < head->process_owner->page_size; x++) {
		if(head->process_owner->pagesowned[x].pageNumber == head->pageNumber && 
			head->process_owner->pagesowned[x].inMemoryTime == head->inMemoryTime) {

			printf("\nEVICTING page# %d from process %c\n", head->process_owner->pagesowned[x].pageNumber, head->process_owner->name[0]);
			
			head->process_owner->pagesowned[x].status = 0; // Set the process's free page list of that page to free
			head->process_owner->pagesowned[x].pageNumber = -1; // Set back to free default value
			head->process_owner->num_page_in_freelist--;
			break;
		}
	} 
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
		head = head->next;
	}
	printf("\n\n");
}

