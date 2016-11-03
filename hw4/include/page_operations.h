#ifndef PAGE_OPERATIONS
#define PAGE_OPERATIONS

//generates linked list of pages.
void generate_pageList(page** list);

//Returns true if we find 4 free pages and we mark those 4 pages as not available. 
bool find_4FreePages(page* llist);

// Prints all 100 pages
void print_pagesLL(page* llist);

// Remove a page from the free memory list based on index
void removeAPage(page** list, int nodeIndex);

// Add a page to the free memory list
void addPageToMemory(page** list, page* pageToInsert, process* p1, int inMemoryTime);

// Returns true if we find 4 free pages and we mark those 4 pages as not available. 
bool find_4FreePages(page* llist);

// Generate page reference based on locality of reference
int getPageReference();
#endif