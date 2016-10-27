#ifndef SHARED
#define SHARED

/// Total number of processes to create
#define NUMBER_PROCESS 150
#define NUMBER_PAGES 10
#define TOTAL_TIME 100

#include <stdbool.h>

struct process{
	char name[2];			// 1 Char per MB? only 1 Char per name?
	int page_size; 			// Can be 5, 11, 17, and 31
	int arrival_time; 		// 
	int completion_time;	// Can be 1, 2, 3, 4, or 5
	struct process* next;   // makes possible to create linked list
};

typedef struct process process;


struct page{
	int status;			//All 100 pages are initially set to available which is 0 when created
						//Set status to 1 for not available page.
	int pageNumber; 	// Page number when added to free memory
	int inMemoryTime; 	// Time when added to free memory
	bool isInMemory;	// Check to see if this page is in memory 
	struct page* next; 
};

typedef struct page page;


#endif