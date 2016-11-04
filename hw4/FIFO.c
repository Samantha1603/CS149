#include <stdio.h>
#include <stdlib.h>
#include "shared.h"
#include "page_operations.h"
#include "FIFO.h"



int getOldestPageFIFO() {
	return 0;
}

void runFIFO(process** prolist, page** pagelist) {

	int currentQuanta = 0;
	int currentPageReference = 0;
	process* process_head = *prolist;
	page* page_head = *pagelist;

	// hm just solo process one at a time for now. we need threads for all the processes to run at once
	for (int i = 0; i < NUMBER_PROCESS; i++) {
		printf("\n\n COMPLETION TIME: %d \n", process_head->completion_time);

		while (process_head->completion_time > 0) {

			if (process_head->num_page_in_freelist <= 4) {

				addPageToMemory(pagelist, page_head, process_head, currentQuanta, currentPageReference);
				process_head->completion_time -= 1;
				currentQuanta++;
				currentPageReference = getPageReference(process_head->page_size, currentPageReference); // The next page to reference

				page_head = page_head->next;
			}
		}
		print_pagesLL(*pagelist);

		if (currentQuanta >= TOTAL_TIME) {
			break;
		}

		process_head = process_head->next;
	}
}


