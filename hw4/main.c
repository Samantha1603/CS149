#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "shared.h"
#include "process_operations.h"
#include "page_operations.h"
#include "FIFO.h"
#include "LFU.h"
#include "MFU.h"
#include "random.h"

/// Amount of memory in MB
#define MEMORY 100

///Page size in MB
#define PAGE_SIZE 1

int main(){
	
	srand(time(NULL));
	// Generate Processes
	process* llistFIFO;
	generate_processes(&llistFIFO);
	//sort_pll(&llist);

	page* pagelinkedlistFIFO;
	generate_pageList(&pagelinkedlistFIFO);


	process* llistLFU;
	generate_processes(&llistLFU);
	//sort_pll(&llist);

	page* pagelinkedlistLFU;
	generate_pageList(&pagelinkedlistLFU);


	process* llistMFU;
	generate_processes(&llistMFU);
	//sort_pll(&llist);

	page* pagelinkedlistMFU;
	generate_pageList(&pagelinkedlistMFU);

	//print_ll(llist);
	print_ll(llistFIFO);
	print_ll(llistLFU);
	print_ll(llistMFU);

	//print_ll(llist);
	printf("***********************");
	printf("\n\nHERE IS FIFO ALGORITHM\n\n" );
	printf("***********************");
	runFIFO(&llistFIFO, &pagelinkedlistFIFO);
	printf("\n***********************\n");
	printf("\n\nHERE IS LFU ALGORITHM\n\n" );
	printf("***********************");
	startLFU(&llistLFU, &pagelinkedlistLFU);
		printf("\n***********************\n");
	printf("\n\nHERE IS MFU ALGORITHM\n\n" );
	printf("***********************");
	startMFU(&llistMFU, &pagelinkedlistMFU);

	return 0;
}