#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "shared.h"
#include "process_operations.h"
#include "page_operations.h"
#include "FIFO.h"

/// Amount of memory in MB
#define MEMORY 100

///Page size in MB
#define PAGE_SIZE 1

int main(){
	
	srand(time(NULL));
	// Generate Processes
	quanta = 0;
	process* llist;
	page* pagelinkedlist;
	generate_processes(&llist);
	sort_pll(&llist);
	generate_pageList(&pagelinkedlist);
	print_ll(llist);

	page* fp_list; // free page list
	generate_pageList(&fp_list);

	//sample insert
	//addPageToMemory(&fp_list, llist, quanta, 3);
	addPageToMemory(&fp_list, &llist[1], quanta, 3);
	addPageToMemory(&fp_list, &llist[1], quanta, 4);
	addPageToMemory(&fp_list, &llist[1], quanta, 3);
	print_process_pages(llist[1]);
	//end sample insert

	//print_pagesLL(fp_list);


	return 0;
}
