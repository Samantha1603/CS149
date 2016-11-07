#include <stdbool.h>
#ifndef FIFO
#define FIFO


/**
 * Runs First In First Out 
 * @param prolist		linked list of all processes to be run
 * @param pagelist		free memory page list
 */
void runFIFO(process** prolist, page** pagelist);

/**
 * Swaps a page with another page using FIFO
 * @param pagelist			free memory page list
 * @param p1 				the process owner to link the page to
 * @param inMemoryTime 		the time a page gets into free memory
 * @param pageNumber		the page number to insert into free memory
 */
void swapWithOldestPageFIFO(page** pagelist, process* p1, int inMemoryTime, int pageNumber);

/**
 * Returns the oldest page based on insertion time from free memory list
 * @param pagelist		free memory page list
 * @return 				the oldest page
 */
page* getOldestPage(page* pagelist);

/**
 * Checks if a given page of a process is already in the memory of that process
 * @param p1			the process
 * @param pageNumber	the page number
 * @return				true if in memory. false if not
 */
bool isPageAlreadyInMemory(process* p1, int pageNumber);

/**
 * Prints the current pages in the free list
 * @param llist		free memory page list
 */
void print_pages(page* llist);

/**
 * Checks if the free list is full
 * @param llist		free memory page list
 * @return 			true is full. false if not
 */

bool isMemoryFull(page* llist);

/**
 * Remove a page from a process's page array
 * @param p1				the process that holds the free list array 
 * @param oldestPage		the oldest page to be removed
 */
void removePageFromAProcessArray(process* p1, page* oldestPage);

void removePageFromFreeList(page** pagelist, char pageToRemove1, char pageToRemove2);

#endif


