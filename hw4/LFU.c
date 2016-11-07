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
void startLFU(process** processbyarrivial, page** pagelist)
{
	int currentQuanta = 0;
	int isDone = 0;
	int hitCount = 0;
	int missCount = 0;
	process* process_head = *processbyarrivial;
	page* page_head = *pagelist;

	while(currentQuanta < 600){
		for(int i =0; i < NUMBER_PROCESS; i++){
			if( process_head->completion_time > 0 && process_head->arrival_time <= currentQuanta){
				printf("\nQUANTA: %d\n", currentQuanta);
				printf("\n\n COMPLETION TIME: %d \n", process_head->completion_time);

				if(process_head->pagesowned[0].status != NULL){
					process_head->last_reference = getPageReference(process_head->page_size, process_head->last_reference);
				}
				if(!isPageAlreadyInMemory(process_head, process_head->last_reference)){ //if page not in memory
					//Page is not yet in memory. 
					if(!isMemoryFull(*pagelist)){//if memory is not full and page not in memory
						addPageToMemory(pagelist, process_head, currentQuanta, process_head->last_reference);//Add page to memory which should also add 1 to frequency for page	
						page_head = page_head->next;
						print_pages(*pagelist);
					}
					else{//else memory is full and page is not in memory DO SWAP IN THIS ELSE
							
						swapWithLowFreqAndHighTimePage();
						print_pages(*pagelist);
							} 
					
					} missCount++;
				else{ //this else means, pages is in memory and its a hit

					page_head->frequency = page_head->frequency + 1;
					hitCount++;

				}
				process_head->completion_time -= 1;
				
			}
			process_head = process_head->next;
			if(process_head == NULL) process_head = *processbyarrivial;
		}
		currentQuanta += 1;
	}
}

page* getLowFreqAndHighTimePage(page* pagelist) //this function returns the page that needs to be taken out of memory.
{
	page* head = pageList;

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

void swapWithLowFreqAndHighTimePage(page** pagelist, process* p1, int inMemoryTime, int pageNumber, int frequency)
{
page* head = *pagelist;
page* lowestFreqAndHighestTimePage = getLowFreqAndHighTimePage(*pagelist);
page insert;
insert.status = 1;
insert.inMemoryTime = inMemoryTime;
insert.process_owner = p1;
insert.pageNumber = pageNumber;
insert.frequency = frequency;

for(int i = 0; i < NUMBER_PAGES; i++){
if(head->process_owner->name[0] == lowestFreqAndHighestTimePage->process_owner->name[0] && head->inMemoryTime == lowestFreqAndHighestTimePage->inMemoryTime)
{
	removePageFromProcessArray()
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





