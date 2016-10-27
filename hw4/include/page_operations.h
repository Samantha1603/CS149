#ifndef PAGE_OPERATIONS
#define PAGE_OPERATIONS

//generates linked list of pages.
void generate_pages(page** list);


void print_pagesLL(page* llist);

//Returns true if we find 4 free pages and we mark those 4 pages as not available. 
bool find_4FreePages(page* llist);