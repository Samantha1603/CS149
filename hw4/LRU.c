#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "include/shared.h"
#include "include/page_operations.h"
#include "include/process_operations.h"
#include "include/LRU.h"
#include "include/FIFO.h"

void swapPageToRecentlyUsed(page* pagelist, int pageNumber)
{
    while(pagelist != NULL)
    {
        if(pagelist->pageNumber == pageNumber)
            pagelist->frequency = 0;
        pagelist->frequency++;
        pagelist = pagelist->next;
    }  
}


page* getLeastUsedPage(page* pagelist) {
    
    page* head = pagelist;
    
    page* leastUsedPage = malloc(sizeof(page));
    leastUsedPage = head; //set first page as oldest by default
    
    for (int i = 0; i < NUMBER_PAGES; i++) {
        if (head->frequency < leastUsedPage->frequency) {
            leastUsedPage = head;
            break;
        }
        head = head->next;
    }
    
    return leastUsedPage;
}


void swapWithLRUPage(page** pagelist, process* p1, int inMemoryTime, int pageNumber) {
    
    page* head = *pagelist;
    page* leastUsedPage = getLeastUsedPage(*pagelist);
    page insert;
    insert.status=1;
    insert.inMemoryTime = inMemoryTime;
    insert.process_owner = p1;
    insert.pageNumber = pageNumber;
    
    for (int i = 0; i < NUMBER_PAGES; i++) {
        if (head->process_owner->name[0] == leastUsedPage->process_owner->name[0] &&
            head->process_owner->name[1] == leastUsedPage->process_owner->name[1] &&
            head->inMemoryTime == leastUsedPage->inMemoryTime) {
            
            removePageFromAProcessArray(head->process_owner, leastUsedPage); // remove that page from that process's free list first
            (*head).status = 1;
            (*head).inMemoryTime = inMemoryTime;
            (*head).process_owner = p1;
            (*head).pageNumber = pageNumber;
            break;
        }
        head = head->next;
    }
    
    // Add to the process's free memory array list
    for(int x = 0; x < p1->page_size; x++) {
        if(p1->pagesowned[x].status != 1){
            p1->pagesowned[x] = insert;
            p1->num_page_in_freelist++;
            break;
        }
    }
}

void runLRU(process **prolist, page **pagelist)
{
    
    int currentQuanta = 0;
    int hitCount = 0;
    int missCount = 0;
    int numOfProcessesDone = 0;
    process* process_head = *prolist;
    page* page_head = *pagelist;
    int i = 1;
    
    printf("\n\nLRU\n");
    while (page_head != NULL)
    {
        page_head->frequency = i; //frequence is used as the last time page was used
        i++;
        page_head = page_head->next;
    }
    
    page_head = *pagelist; // resetting page_head
    
    printf("\n\n****************************\n");
    while (currentQuanta < 600) { // 600 quanta = 1 minute (max)
        for (int i = 0; i < NUMBER_PROCESS; i++) {
            
            
            if (process_head->completion_time > 0 && process_head->arrival_time <= currentQuanta) { // Only run that process if its completition if > 0
                
                printf("\nQUANTA: %d\n", currentQuanta);
                
                if (process_head->pagesowned[0].process_owner != NULL) { // Not first referencing made
                    process_head->last_reference = getPageReference(process_head->page_size, process_head->last_reference); // The next page to reference
                }
                
                if (isPageAlreadyInMemory(process_head, process_head->last_reference)) {
                    hitCount++;
                    swapPageToRecentlyUsed(page_head, process_head->last_reference);
                    
                } else {
                    // Page in not yet in memory. Add to free list
                    printf("PAGE REFERENCED # %d\n", process_head->last_reference);
                    printf("\n----INSERT - PAGE# %d OF PROCESS %c%c----\n", process_head->last_reference, process_head->name[0], process_head->name[1]);
                    
                    if(find4FreePages(*pagelist)) {
                    // Found 4 free pages. Can insert into free list.
                    
                    if (!isMemoryFull(*pagelist)) {
                        addPageToMemory(pagelist, process_head, currentQuanta, process_head->last_reference);
                        if (page_head != NULL) page_head = page_head->next;
                        print_pages(*pagelist);
                    } else {
                        // Memory is full. Do swap with oldest page.
                        swapWithLRUPage(pagelist, process_head, currentQuanta, process_head->last_reference);
                        print_pages(*pagelist);
                    }
                    missCount++;
		    }
                }
                
                process_head->completion_time -= 1;
                
                if (process_head->completion_time <= 0) {
                    
                    printf("\nPROCESS %c%c DONE. REMOVING PAGES\n", process_head->name[0], process_head->name[1]);
                    // Process if finished, removing its free list from free memory
                    removePageFromFreeList(pagelist, process_head->name[0], process_head->name[1]);
                    numOfProcessesDone++;
                }
            }
            process_head = process_head->next;
            if (process_head == NULL) process_head = *prolist; // wrap around to head process again..
        }
        currentQuanta += 1; // Increment 1 quanta, which is
    }
    
    printStats(hitCount, missCount, numOfProcessesDone);
}