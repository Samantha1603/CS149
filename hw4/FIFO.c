#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "shared.h"
#include "page_operations.h"
#include "FIFO.h"



int getOldestPageFIFO() {
	return 0;
}

void runFIFO(process** prolist, page** pagelist) {

	int currentQuanta = 1;
	bool done = false;
	int currentPageReference = 0;
	int isDone = 0;
	process* process_head = *prolist;
	page* page_head = *pagelist;

	// hm just solo process one at a time for now. we need threads for all the processes to run at once

	while (!done) {

		for (int i = 0; i < NUMBER_PROCESS; i++) {

			if (process_head->arrival_time <= currentQuanta) {
				printf("\nQUANTA: %d\n", currentQuanta);
				printf("\n\n COMPLETION TIME: %d \n", process_head->completion_time);

				if(find_4FreePages(*pagelist)) {
					// Found 4 free pages. Can insert into free list.

					if (process_head->pagesowned[0].status == 0) { // First referencing made
						printf("\n\n FIRST REFERENCE \n\n");
						currentPageReference = 0;
					} else {
						currentPageReference = getPageReference(process_head->page_size, currentPageReference); // The next page to reference
					}

					addPageToMemory(pagelist, process_head, currentQuanta, currentPageReference);
					process_head->completion_time -= 1; 

					printf("\nQUANTA: %d\n", currentQuanta);
					page_head = page_head->next;
					process_head = process_head->next;
					print_pagesLL(*pagelist);

				} else {
					//print_pagesLL(*pagelist);
					printf("\n\n NO FREE FOUR PAGES \n\n");
					done = true;
					break;
					// Do replacement algorithm
				}
			} 			
		}

		if (currentQuanta >= 200) {
			break;
		}
		currentQuanta += 1;
	}
}


