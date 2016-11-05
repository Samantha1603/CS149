#include <stdbool.h>
#ifndef FIFO
#define FIFO

// Generate page reference based on locality of reference
page* swapWithOldestPageFIFO(page** pagelist, process* p1, int inMemoryTime, int pageNumber);
void runFIFO(process** prolist, page** pagelist);
bool isPageAlreadyInMemory(process* p1, int pageNumber);
void print_pages(page* llist);
bool isMemoryFull(page* llist);

#endif