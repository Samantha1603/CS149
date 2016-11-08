#include <stdbool.h>
#ifndef LFU
#define LFU


void startLFU(process** processbyarrivial, page** pagellist);

page* getLowFreqAndHighTimePage(page* pagelist);

bool isPageAlreadyInMemory(process* p1, int pageNumber);

bool isMemoryFull(page* llist);

void print_pages(page* llist);

void swapWithLowFreqAndHighTimePage(page** pagelist, process* p1, int inMemoryTime, int pageNumber, int frequency);

void removePageFromAProcessArray(process* p1, page* oldestPage);

#endif