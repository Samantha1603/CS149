
#ifndef LRU_h
#define LRU_h


/**
 * Runs Least recently used algorithm
 * @param prolist		linked list of all processes to be run
 * @param pagelist		free memory page list
 */
void runLRU(process** prolist, page** pagelist);

/**
 * if page is already in memory, it will make that page recently used by making it's frequency 1 and others frequencies +1 all.
 * @param pagelist			free memory page list
 * @param pageNumber		the page number to insert into free memory
 */
void swapPageToRecentlyUsed(page* pagelist, int pageNumber);

/**
 * Returns the the page that has been used the least so far
 * @param pagelist		free memory page list
 * @return 				the oldest page
 */
page* getLeastUsedPage(page* pagelist);

/**
 * Checks if a given page of a process is already in the memory of that process
 * @param p1			the process
 * @param pageNumber	the page number
 * @return				true if in memory. false if not
 */
bool isPageAlreadyInMemory(process* p1, int pageNumber);

/**
 * removes the least recently used page in the memory with the new page
 * @param pagelist			free memory page list
 * @param p1			the process
 * @param inMemoryTime		the time page inserted in memory
 * @param pageNumber	the page number
 */
void swapWithLRUPage(page** pagelist, process* p1, int inMemoryTime, int pageNumber);

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

/**
 * Remove a page from the free memory list when process is finished
 * @param pagelist		the page list linked list
 * @param nameOne		the first char of process name
 * @param nameTwo		the second char of process name
 */
void removePageFromFreeList(page** pagelist, char nameOne, char nameTwo);

/**
 * Prints the final statistics of the algorithm
 * @param hitCount					count of hits
 * @param missCount					count of misses
 * @param numOfProcessesDone		count total processes done
 */
void printStats(int hitCount, int missCount, int numOfProcessesDone);



#endif
