#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "shared.h"
#include "process_operations.h"
#include "page_operations.h"
#include "FIFO.h"
#include "LFU.h"

/// Amount of memory in MB
#define MEMORY 100

///Page size in MB
#define PAGE_SIZE 1

int main(){
	
	srand(time(NULL));
	// Generate Processes
	process* llist;
	generate_processes(&llist);
	//sort_pll(&llist);
	page* pagelinkedlist;
	generate_pageList(&pagelinkedlist);

	//print_ll(llist);
	print_ll(llist);

	//print_ll(llist);
	printf("***********************");
	printf("\n\nHERE IS FIFO ALGORITHM\n\n" );
	printf("***********************");
	//runFIFO(&llist, &pagelinkedlist);
	printf("\n***********************\n");
	printf("\n\nHERE IS LFU ALGORITHM\n\n" );
	printf("***********************");
	startLFU(&llist, &pagelinkedlist);


	return 0;
}