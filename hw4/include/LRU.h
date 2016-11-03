
#ifndef LRU_h
#define LRU_h

struct memoryHelper{
    int last_used;
    struct page** pageInMemory; //pointer to the current page in memeory
    };

typedef struct memoryHelper memoryHelper;

//get the least used page
int getLeastUsedPageLRU();
void runLRU(process **processList, page **pageList);

#endif /* LRU_h */
