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

	for (int i = 0; i < NUMBER_PROCESS; i++) {
		printf("\n\n COMPLETION TIME: %d \n", process_head->completion_time);

		while (process_head->completion_time > 0) {
			addPageToMemory(pagelist, page_head, process_head, currentQuanta);
			process_head->completion_time -= 1;
			page_head = page_head->next;
			currentQuanta++;
		}
		print_pagesLL(*pagelist);


		if (currentQuanta >= TOTAL_TIME) {
			break;
		}

		process_head = process_head->next;
	}
}


