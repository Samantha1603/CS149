#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "shared.h"
#include "page_operations.h"
#include "process_operations.h"
#include "LFU.h"

//while(memory is full) do this algorithm
//We only use algorithm when memory is full.
//Increment the frequency for that page that comes into memory.
//Lowest frequency page is kicked out of memory.
//If there are 2 or more pages with the same lowest frequency, then kick out the oldest page.
//When page is kicked out, reset that pages frequency to 0.

//this is the function call to start the algorithm. This function uses all functions underneath it
void startLFU(process** prolist, page** pagelist) {

	int currentQuanta = 0;
	int hitCount = 0;
	int missCount = 0;
	process* process_head = *prolist;
	page* page_head = *pagelist;

	while (currentQuanta < 600) { // 600 quanta = 1 minute (max)

		for (int i = 0; i < NUMBER_PROCESS; i++) {


			if (process_head->completion_time > 0 && process_head->arrival_time <= currentQuanta) { // Only run that process if its completition if > 0

				printf("\nQUANTA: %d\n", currentQuanta);
				//printf("COMPLETION TIME: %d \n", process_head->completion_time);

				if (process_head->pagesowned[0].process_owner != NULL) { // Not first referencing made
					process_head->last_reference = getPageReference(process_head->page_size, process_head->last_reference); // The next page to reference
				}

				if (!isPageAlreadyInMemory(process_head, process_head->last_reference)) {

					// Page in not yet in memory. Add to free list
					printf("\nPAGE REFERENCED # %d\n", process_head->last_reference);
					printf("\n----ENTER - PAGE# %d OF PROCESS %c%c----\n", process_head->last_reference, process_head->name[0], process_head->name[1]);

					//if(find_4FreePages(*pagelist)) {
						// Found 4 free pages. Can insert into free list.

						if (!isMemoryFull(*pagelist)) {
							addPageToMemory(pagelist, process_head, currentQuanta, process_head->last_reference);
							if (page_head != NULL) page_head = page_head->next;
							print_pages(*pagelist);
						} else {	
							// Memory is full. Do swap with oldest page.
							swapWithLowFreqAndHighTimePage(pagelist, process_head, currentQuanta, process_head->last_reference);
							print_pages(*pagelist);
						}
						missCount++;
					//} //else {
						// WAIT for process to finish
						//print_pagesLL(*pagelist);
						//printf("\n\n NO FREE FOUR PAGES \n\n");

						//while (!find_4FreePages(*pagelist)) {

						//}
						//break;
					//}
				} else {
					// Page is already in memory. a hit
					hitCount++;
				}
				process_head->completion_time -= 1;

				if (process_head->completion_time <= 0) {
					//printf("\nCOMPLETION TIME %d\n", process_head->completion_time);
					printf("\nPROCESS %c%c DONE. REMOVING PAGES\n", process_head->name[0], process_head->name[1]);
					// Process if finished, removing its free list from free memory
					removePageFromFreeList(pagelist, process_head->name[0], process_head->name[1]);
				}
			}
			process_head = process_head->next;
			if (process_head == NULL) process_head = *prolist; // wrap around to head process again..
		}
		currentQuanta += 1; // Increment 1 quanta, which is
	}

	printf("\n\n****************************\n");
	printf("         HIT: %d         \n", hitCount);
	printf("         MISS: %d        \n", missCount);
	printf("      HIT RATIO: %.2f     \n", (float) hitCount / missCount);
	printf("****************************\n\n\n");
}


page* getLowFreqAndHighTimePage(page* pagelist) //this function returns the page that needs to be taken out of memory.
{
	page* head = pagelist;

	page* lowFreqAndHighTime = malloc(sizeof(page));
	lowFreqAndHighTime->frequency = head->frequency;

	for(int i =0; i < NUMBER_PAGES; i++)
	{
		if(head->frequency < lowFreqAndHighTime->frequency)
		{
			lowFreqAndHighTime = head;
		}
		else if (head->frequency == lowFreqAndHighTime->frequency){
			if(head->inMemoryTime < lowFreqAndHighTime->inMemoryTime){
				lowFreqAndHighTime = head;
			}
		}
		head = head->next;
	}
	return lowFreqAndHighTime;
}

void swapWithLowFreqAndHighTimePage(page** pagelist, process* p1, int inMemoryTime, int pageNumber)
{
page* head = *pagelist;
page* lowestFreqAndHighestTimePage = getLowFreqAndHighTimePage(*pagelist);
page insert;
insert.status = 1;
insert.inMemoryTime = inMemoryTime;
insert.process_owner = p1;
insert.pageNumber = pageNumber;
insert.frequency = 1;

for(int i = 0; i < NUMBER_PAGES; i++){
if(head->process_owner->name[0] == lowestFreqAndHighestTimePage->process_owner->name[0] && head->inMemoryTime == lowestFreqAndHighestTimePage->inMemoryTime)
{
	removePageFromAProcessArray(head->process_owner, lowestFreqAndHighestTimePage);
	(*head).status = 1;
	(*head).inMemoryTime = inMemoryTime;
	(*head).process_owner = p1;
	(*head).pageNumber = pageNumber;
	(*head).frequency = 1;
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



//Swapping pages algorithm, processes are sorted by arrival time
/*
page* kickOutLFUPage(page** pagelist, process* p1, int inMemoryTime, int frequency,int pageNumber)
{
	page* head = *pagelist;
	page* leastFrequentPage = malloc(sizeof(page)); 
	leastFrequentPage->frequency = 1; //this is the lowest default and all pages start at 1 frequency when put in list

	page insert;
	insert.status = 1;
	insert.inMemoryTime = inMemoryTime;
	insert.frequency = frequency;
	insert.process_owner = p1;
	insert.pageNumber = pageNumber;

	//have to iterate through to find the page with lowest frequency and if multiple pages have the same lowest then need to
	//which of the lowest frequency pages were in memory for the longest time. Then you kick that one out.
	//
	for(int i = 0; i < NUMBER_PAGES; i++)
	{
		if(head->frequency > leastFrequentPage->frequency)
		{
			leastFrequentPage = head;
		}
		head = head->next;
		if(head->next == NULL) head = *pagelist;
	} //at this point we have the leastfrequent page in memory.

	//now we need to find the oldest page if there are multiple leastFrequent
	printf("\nLEAST FREQUENT PAGE: %d FROM PROCESS %c\n", leastFrequentPage->frequency, leastFrequentPage->process_owner->name[0]);
	head = *pagelist; //start at beginning of pagelist to iterate through again
	for(int i = 0; i < NUMBER_PAGES; i++)
	{
		if(head->frequency == leastFrequentPage.frequency && head->inMemoryTime > leastFrequentPage->inMemoryTime)
		{
			//found our new lowest frequency but older page to kick out.
			leastFrequentPage = head;
		}
		head = head->next;
		//if(head -> next == NULL) head = *pagelist;

	}
	//At this point we should have the page we want to kick out as leastFrequentPage.
	


}*/



void removePageFromAProcessArray(process* p1, page* oldestPage) {

	for(int x = 0; x < p1->page_size; x++) {
		if(oldestPage->pageNumber == p1->pagesowned[x].pageNumber) {

			printf("\n****EVICTING - PAGE# %d OF PROCESS %c****\n\n", p1->pagesowned[x].pageNumber, p1->name[0]);
			p1->pagesowned[x].status = 0; // Set the process's free page list of that page to free
			p1->pagesowned[x].pageNumber = -1; // Set back to free default value
			p1->num_page_in_freelist--;
			break;
		}
	} 
}


void removePageFromFreeList(page** pagelist, char pageToRemove1, char pageToRemove2) {

	page* head = *pagelist;
	bool isRemovalExists = false;

	for (int x = 0; x < NUMBER_PAGES; x++) {
		if (head->process_owner == NULL) break;
		// Setting the page to be available for other pages to take its spot
		if (head->process_owner->name[0] == pageToRemove1 && head->process_owner->name[1] == pageToRemove2) {
			head->pageNumber = 0;
			head->status = 0;
			isRemovalExists = true; // For process name removal
		} 
		head = head->next;			
	}

	head = *pagelist;
	if (isRemovalExists) {
		// Change process name to '.' for all pages referenced to it
		for (int x = 0; x < NUMBER_PAGES; x++) {
			if (head->process_owner == NULL) break;
			if (head->process_owner->name[0] == pageToRemove1 && head->process_owner->name[1] == pageToRemove2) head->process_owner->name[0] = '.';
			head = head->next;			
		}
	}
	printf("AFTER REMOVAL\n");
	print_pages(*pagelist);
}



//check if page is currently in memory
bool isPageAlreadyInMemory(process* p1, int pageNumber)
{
	bool isInMemory = false;
	for(int x =0; x < p1->num_page_in_freelist; x++)
	{
		if(p1->pagesowned[x].pageNumber == pageNumber) isInMemory = true;
	}
	return isInMemory;
}

//check if memory is full
bool isMemoryFull(page* llist)
{
int pagesFound = 0;
page* head = llist;
bool isMemFull = false;

for(int x = 0; x < NUMBER_PAGES; x++)
{
	if(head->status == 1){
		pagesFound++;
	}
	head = head->next;
}
if(pagesFound >= NUMBER_PAGES){
	isMemFull =true;
}
return isMemFull;
}


void print_pages(page* llist) {
	
	page* head = llist;
	for(int x = 0; x < NUMBER_PAGES; x++){
		if(head == NULL) break;

		printf("[(#: %d),", head->pageNumber);
		if (head->status == 1) {
			printf("(P: %c%c)] ", head->process_owner->name[0], head->process_owner->name[1]);
		} else {
			printf("(P:.)] ");
		}
		head = head->next;
	}
	printf("\n\n");
}


void printStats(int hitCount, int missCount) {
	printf("\n\n****************************\n");
	printf("         HIT: %d         \n", hitCount);
	printf("         MISS: %d        \n", missCount);
	printf("      HIT RATIO: %.2f     \n", (float) hitCount / missCount);
	printf("      MISS RATIO: %.2f     \n", (1 - (float) hitCount / missCount));
	printf("****************************\n\n");
	printf("All processes swapped in.\n\n");

}





