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
	process* llist;
	page* pagelinkedlist;
	generate_processes(&llist);
	sort_pll(&llist);
	generate_pageList(&pagelinkedlist);
	print_ll(llist);

	page* pllist;
	generate_pageList(&pllist);
	print_pagesLL(pllist);


	return 0;
}
