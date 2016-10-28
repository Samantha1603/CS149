#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
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
	generate_pageList(&pagelinkedlist);
	printf("\nHere is our initial page list\n");
	print_pageLinkedList(pagelinkedlist);
	printf("\nEND OF PAGES\n");
	print_ll(llist);
	printf("\n\nAfter sort\n\n");
	sort_pll(llist);
	print_ll(llist);
	return 0;
}
