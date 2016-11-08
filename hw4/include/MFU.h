#include <stdbool.h>
#ifndef MFU
#define MFU


void startMFU(process** prolist, page** pagelist);

page* getHighFreqAndHighTimePage(page* pagelist, int* freqArray);

bool isPageAlreadyInMemoryMFU(process* p1, int pageNumber);

bool isMemoryFullMFU(page* llist);

void print_pagesMFU(page* llist);

void swapWithHighFreqAndHighTimePage(page** pagelist, process* p1, int inMemoryTime, int pageNumber, int* freqArray);

void removePageFromAProcessArrayMFU(process* p1, page* oldestPage);

void removePageFromFreeListMFU(page** pagelist, char pageToRemove1, char pageToRemove2, int* freqArray);

void printStatsMFU(int hitCount, int missCount, int numOfProcessesDone);
#endif