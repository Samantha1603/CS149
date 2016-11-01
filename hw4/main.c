#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "shared.h"
#include "process_operations.h"
#include "page_operations.h"

/// Amount of memory in MB
#define MEMORY 100

///Page size in MB
#define PAGE_SIZE 1

int main(){
	
	srand(time(NULL));
	// Generate Processes
	process* llist;
	page* pagelinkedlist;
	generate_processes(&llist);
	sort_pll(&llist);
	generate_pageList(&pagelinkedlist);
	print_ll(llist);

	page* pllist;
	generate_pageList(&pllist);
	print_pagesLL(pllist);

	printf("\n\n\n");
	//removeAPage(&pllist, 4); // remove at position 4 test
	//print_pagesLL(pllist);

	printf("\nADDING NODE\n\n");
	page* newPage = malloc(sizeof(page));
	newPage->pageNumber = 100;
	addPageToMemory(&pllist, newPage, llist);
	print_pagesLL(pllist);

	return 0;
}
