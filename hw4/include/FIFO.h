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
bool isPageAlreadyInMemoryFIFO(process* p1, int pageNumber);

/**
 * Prints the current pages in the free list
 * @param llist		free memory page list
 */
void print_pagesFIFO(page* llist);

/**
 * Checks if the free list is full
 * @param llist		free memory page list
 * @return 			true is full. false if not
 */

bool isMemoryFullFIFO(page* llist);

/**
 * Remove a page from a process's page array
 * @param p1				the process that holds the free list array 
 * @param oldestPage		the oldest page to be removed
 */
void removePageFromAProcessArrayFIFO(process* p1, page* oldestPage);

/**
 * Remove a page from the free memory list when process is finished
 * @param pagelist		the page list linked list 
 * @param nameOne		the first char of process name
 * @param nameTwo		the second char of process name
 */
void removePageFromFreeListFIFO(page** pagelist, char nameOne, char nameTwo);

/**
 * Prints the final statistics of the algorithm
 * @param hitCount		count of hits
 * @param missCount		count of misses
 */
 void printStatsFIFO(int hitCount, int missCount);

#endif

