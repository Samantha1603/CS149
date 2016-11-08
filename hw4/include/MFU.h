
void startMFU(process** prolist, page** pagelist);

page* getHighFreqAndHighTimePage(page* pagelist);

bool isPageAlreadyInMemoryMFU(process* p1, int pageNumber);

bool isMemoryFullMFU(page* llist);

void print_pagesMFU(page* llist);

void swapWithHighFreqAndHighTimePage(page** pagelist, process* p1, int inMemoryTime, int pageNumber);

void removePageFromAProcessArrayMFU(process* p1, page* highFreqPage);

void removePageFromFreeListMFU(page** pagelist, char pageToRemove1, char pageToRemove2);

void printStatsMFU(int hitCount, int missCount, int numOfProcessesDone);