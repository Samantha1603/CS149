#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "shared.h"
#include "page_operations.h"
#include "process_operations.h"

//while(memory is full) do this algorithm
//We only use algorithm when memory is full.
//Increment the frequency for that page that comes into memory.
//Lowest frequency page is kicked out of memory.
//If there are 2 or more pages with the same lowest frequency, then kick out the oldest page.
//When page is kicked out, reset that pages frequency to 0.

//this is the function call to start the algorithm. This function uses all functions underneath it
void startLFU(process** processbyarrivial, page** pagellist)
{
	int currentQuanta = 0;
	int isDone = 0;
	process* process_head = *processbyarrivial;
	page* page_head = *pagellist;

	while(currentQuanta < 600)
}




//Swapping pages algorithm, processes are sorted by arrival time
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




