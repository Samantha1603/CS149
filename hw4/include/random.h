#include <stdbool.h>
#ifndef random
#define random



void runRandom(process** prolist, page** pagelist);


void swapWithRandomPage(page** pagelist, process* p1, int inMemoryTime, int pageNumber);


page* getRandomPage(page* pagelist);


bool isPageAlreadyInMemoryRandom(process* p1, int pageNumber);


void print_pagesRandom(page* llist);


bool isMemoryFullRandom(page* llist);


void removePageFromAProcessArrayRandom(process* p1, page* oldestPage);


void removePageFromFreeListRandom(page** pagelist, char nameOne, char nameTwo);


void printStatsRandom(int hitCount, int missCount, int numOfProcessesDone);

bool find4FreePagesRandom(page* llist);
#endif
