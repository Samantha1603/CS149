#include <stdio.h>
#include <stdlib.h>
#include "shared.h"
#include "page_operations.h"
#include "FIFO.h"



int getOldestPageFIFO() {
	return 0;
}

void runFIFO(process** prolist, page** pagelist) {

	int currentQuanta = 100;
	int currentPageReference = 0;
	process* process_head = *prolist;
	page* page_head = *pagelist;

	// hm just solo process one at a time for now. we need threads for all the processes to run at once

	for (int i = 0; i < NUMBER_PROCESS; i++) {
		printf("\n\n COMPLETION TIME: %d \n", process_head->completion_time);
		//printf("\nQUANTA: %f\n", currentQuanta);

		if (process_head->arrival_time <= currentQuanta) {

			if(find_4FreePages) {
				// Found 4 free pages. Can insert into free list.

				if (process_head->pagesowned[0].status == 0) { // First referencing made
					printf("\n\n FIRST REFERENCE \n\n");
					print_pagesLL(*pagelist);
					currentPageReference = 0;
				} else {
					print_pagesLL(*pagelist);
					currentPageReference = getPageReference(process_head->page_size, currentPageReference); // The next page to reference
				}

				addPageToMemory(pagelist, process_head, currentQuanta, currentPageReference);
				process_head->completion_time -= 0.1; 

			} else {
				printf("\n\n NO FREE FOUR PAGES \n\n");
				// Do replacement algorithm
			}
		} 
		
		currentQuanta += 0.1;
		//printf("\nQUANTA: %f\n", currentQuanta);
		page_head = page_head->next;
		process_head = process_head->next;

		if (currentQuanta >= TOTAL_TIME) {
			break;
		}
	}
}


