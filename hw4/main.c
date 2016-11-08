#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "shared.h"
#include "process_operations.h"
#include "page_operations.h"
#include "FIFO.h"
#include "LFU.h"
#include "MFU.h"
#include "LRU.h"
#include "random.h"

/// Amount of memory in MB
#define MEMORY 100

///Page size in MB
#define PAGE_SIZE 1

int main() {
	
	srand(time(NULL));

	process* llist;
	generate_processes(&llist);
	sort_pll(&llist);
	print_ll(llist);

	
	process* llistFIFO;
	generate_processes(&llistFIFO);
	printf("\n\n\nUnsorted\n\n\n");
	print_ll(llistFIFO);
	page* pagelinkedlistFIFO;
	generate_pageList(&pagelinkedlistFIFO);
	printf("***********************");
	printf("\n\nHERE IS FIFO ALGORITHM\n\n" );
	printf("***********************");
	runFIFO(&llistFIFO, &pagelinkedlistFIFO);
	

	/*
	process* llistLFU;
	generate_processes(&llistLFU);
	printf("\n\n\nUnsorted\n\n\n");
	print_ll(llistLFU);
	page* pagelinkedlistLFU;
	generate_pageList(&pagelinkedlistLFU);
	printf("\n***********************\n");
	printf("\n\nHERE IS LFU ALGORITHM\n\n" );
	printf("***********************");
	startLFU(&llistLFU, &pagelinkedlistLFU);
	*/

	/*
	process* llistMFU;
	generate_processes(&llistMFU);
	printf("\n\n\nUnsorted\n\n\n");
	print_ll(llistMFU);
	page* pagelinkedlistMFU;
	generate_pageList(&pagelinkedlistMFU);
	printf("\n***********************\n");
	printf("\n\nHERE IS MFU ALGORITHM\n\n" );
	printf("***********************");
	startMFU(&llistMFU, &pagelinkedlistMFU);
	*/

	/*
	process* llistLRU;
	generate_processes(&llistLRU);
	printf("\n\n\nUnsorted\n\n\n");
	print_ll(llistLRU);
	page* pagelinkedlistLRU;
	generate_pageList(&pagelinkedlistLRU);
	printf("\n***********************\n");
	printf("\n\nHERE IS LRU ALGORITHM\n\n" );
	printf("***********************");
	runLRU(&llistLRU, &pagelinkedlistLRU);
	*/

	/*
	process* llistRANDOM;
	generate_processes(&llistRANDOM);
	printf("\n\n\nUnsorted\n\n\n");
	print_ll(llistRANDOM);
	page* pagelinkedlistRANDOM;
	generate_pageList(&pagelinkedlistRANDOM);
	printf("\n***********************\n");
	printf("\n\nHERE IS RANDOM ALGORITHM\n\n" );
	printf("***********************");
	runRandom(&llistRANDOM, &pagelinkedlistRANDOM);
	*/

	return 0;
}