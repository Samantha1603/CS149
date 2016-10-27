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
	/*
	process* llist;
	generate_processes(&llist);
	print_ll(llist);
	printf("\n\nAfter sort\n\n");
	sort_pll(llist);
	print_ll(llist);*/

	page* pllist;
	generate_pageList(&pllist);
	print_pagesLL(pllist);

	printf("\n\n\n\n\n\n");
	removeAPage(&pllist, 4);
	print_pagesLL(pllist);

	return 0;
}
