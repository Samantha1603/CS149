#include <stdbool.h>
#ifndef LFU
#define LFU


void startLFU(process** prolist, page** pagelist);

page* getLowFreqAndHighTimePage(page* pagelist);

bool isPageAlreadyInMemoryLFU(process* p1, int pageNumber);

bool isMemoryFullLFU(page* llist);

void print_pagesLFU(page* llist);

void swapWithLowFreqAndHighTimePage(page** pagelist, process* p1, int inMemoryTime, int pageNumber);

void removePageFromAProcessArrayLFU(process* p1, page* oldestPage);

void removePageFromFreeListLFU(page** pagelist, char pageToRemove1, char pageToRemove2);

#endif