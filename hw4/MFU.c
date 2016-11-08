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
void startMFU(process** prolist, page** pagelist) {

	int currentQuanta = 0;
	int freqArray[32]; //keep track of frequency. page = index + 1; values inside are frequency of each page.
	int indexForArray = 0;
	int hitCount = 0;
	int missCount = 0;
	int numOfProcessesDone = 0;
	process* process_head = *prolist;
	page* page_head = *pagelist;

	for(int i = 0; i < 32; i++)
	{
		freqArray[i] = 0;
	}


	while (currentQuanta < 600) { // 600 quanta = 1 minute (max)

		for (int i = 0; i < NUMBER_PROCESS; i++) {


			if (process_head->completion_time > 0 && process_head->arrival_time <= currentQuanta) { // Only run that process if its completition if > 0

				printf("\nQUANTA: %d\n", currentQuanta);
				//printf("COMPLETION TIME: %d \n", process_head->completion_time);

				if (process_head->pagesowned[0].process_owner != NULL) { // Not first referencing made
					process_head->last_reference = getPageReference(process_head->page_size, process_head->last_reference); // The next page to reference
				}

				if (!isPageAlreadyInMemoryLFU(process_head, process_head->last_reference)) {

					// Page in not yet in memory. Add to free list
					printf("\nPAGE REFERENCED # %d\n", process_head->last_reference);
					printf("\n----ENTER - PAGE# %d OF PROCESS %c%c----\n", process_head->last_reference, process_head->name[0], process_head->name[1]);

						if (!isMemoryFullMFU(*pagelist)) {
							freqArray[process_head->last_reference] = freqArray[process_head->last_reference] + 1;

							addPageToMemory(pagelist, process_head, currentQuanta, process_head->last_reference);
							if (page_head != NULL) page_head = page_head->next;

							print_pagesMFU(*pagelist);
						} else {	
							// Memory is full. Do swap with oldest page.
							swapWithLowFreqAndHighTimePage(pagelist, process_head, currentQuanta, process_head->last_reference, freqArray);
							print_pagesLFU(*pagelist);
						}
						missCount++;
		
				} else {
					// Page is already in memory. a hit
					hitCount++;
					// Increase frequency +1 in frequency counter array
					freqArray[process_head->last_reference] = freqArray[process_head->last_reference] + 1;
				}

				process_head->completion_time -= 1;

				if (process_head->completion_time <= 0) {
					//printf("\nCOMPLETION TIME %d\n", process_head->completion_time);
					printf("\nPROCESS %c%c DONE. REMOVING PAGES\n", process_head->name[0], process_head->name[1]);
					// Process if finished, removing its free list from free memory
					removePageFromFreeListLFU(pagelist, process_head->name[0], process_head->name[1], freqArray);
					numOfProcessesDone++;
				}
			}
			process_head = process_head->next;
			if (process_head == NULL) process_head = *prolist; // wrap around to head process again..
		}
		currentQuanta += 1; // Increment 1 quanta, which is
	}

	printStatsMFU(hitCount, missCount, numOfProcessesDone);
}


page* getHighFreqAndHighTimePage(page* pagelist, int* freqArray) //this function returns the page that needs to be taken out of memory.
{
	page* head = pagelist;
	page* highFreq = malloc(sizeof(page));
	highFreq = head; 
	//page* lowFreqAndHighTime = malloc(sizeof(page));
	//lowFreqAndHighTime->frequency = head->frequency;
	int highestFoundFrequency = freqArray[0]; //frequency value
	
	//first find lowest frequency in frequency array
	for(int i = 0; i < 32; i++)
	{
		printf("\nVALUE %d \n", freqArray[i]);
		if(freqArray[i] != 0 && freqArray[i] > highestFoundFrequency){
			highestFoundFrequency = freqArray[i];
		}
	}

	//printf("\nLOWEST FOUND %d\n", lowestFoundFrequency);

	//then match the frequency to a page 
	for(int i = 0; i < NUMBER_PAGES; i++)
	{	// Find matching low freq in linked list
		if(head->pageNumber == highestFoundFrequency) {
			// Find lowest entry time (been there the longest)
			if (head->inMemoryTime < highFreq->inMemoryTime) {
				highFreq = head; //lowfreq is a node with lowest frequency
			}
		}
		head = head->next;
	}
	return highFreq;
}

//function to take lowestFrequencyAndHighestTime Page from function above and swap it with a new page in memory.
void swapWithHighFreqAndHighTimePage(page** pagelist, process* p1, int inMemoryTime, int pageNumber, int* freqArray)
{
	page* head = *pagelist;
	page* highestFreqAndHighestTimePage = getHighFreqAndHighTimePage(*pagelist, freqArray);
	// Swapped out this page so -1 frequency from the page in frequency counter array
	freqArray[highestFreqAndHighestTimePage->pageNumber] = freqArray[highestFreqAndHighestTimePage->pageNumber] - 1;

	// New page to be added. +1 frequency in the frequency counter array
	freqArray[pageNumber] = freqArray[pageNumber] + 1;
	//page* lowestFreqAndHighestTimePage = getLowFreqAndHighTimePage(*pagelist);
	page insert;
	insert.status = 1;
	insert.inMemoryTime = inMemoryTime;
	insert.process_owner = p1;
	insert.pageNumber = pageNumber;

	for(int i = 0; i < NUMBER_PAGES; i++){

		if(head->process_owner->name[0] == highestFreqAndHighestTimePage->process_owner->name[0] && 
			head->process_owner->name[1] == highestFreqAndHighestTimePage->process_owner->name[1] &&
			head->inMemoryTime == highestFreqAndHighestTimePage->inMemoryTime) {

			removePageFromAProcessArrayMFU(head->process_owner, highestFreqAndHighestTimePage);
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
		if(p1->pagesowned[x].status != 1) {
			p1->pagesowned[x] = insert;
			p1->num_page_in_freelist++;
			break;
		}
	}
}

void removePageFromAProcessArrayMFU(process* p1, page* highestfreqPage) {

	for(int x = 0; x < p1->page_size; x++) {
		if(highestfreqPage->pageNumber == p1->pagesowned[x].pageNumber) {

			printf("\n****EVICTING - PAGE# %d OF PROCESS %c****\n\n", p1->pagesowned[x].pageNumber, p1->name[0]);
			p1->pagesowned[x].status = 0; // Set the process's free page list of that page to free
			p1->pagesowned[x].pageNumber = -1; // Set back to free default value
			p1->num_page_in_freelist--;
			break;
		}
	} 
}


void removePageFromFreeListMFU(page** pagelist, char pageToRemove1, char pageToRemove2, int* freqArray) {

	page* head = *pagelist;
	bool isRemovalExists = false;

	for (int x = 0; x < NUMBER_PAGES; x++) {
		if (head->process_owner == NULL) break;
		// Setting the page to be available for other pages to take its spot
		if (head->process_owner->name[0] == pageToRemove1 && head->process_owner->name[1] == pageToRemove2) {

			// Removed this page so -1 frequency from the page in frequency counter array
			freqArray[head->pageNumber] = freqArray[head->pageNumber] - 1;

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
	print_pagesMFU(*pagelist);
}



//check if page is currently in memory
bool isPageAlreadyInMemoryMFU(process* p1, int pageNumber)
{
	bool isInMemory = false;
	for(int x =0; x < p1->num_page_in_freelist; x++)
	{
		if(p1->pagesowned[x].pageNumber == pageNumber) isInMemory = true;
	}
	return isInMemory;
}

//check if memory is full
bool isMemoryFullMFU(page* llist)
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


void print_pagesMFU(page* llist) {
	
	page* head = llist;
	for(int x = 0; x < NUMBER_PAGES; x++){
		if(head == NULL) break;

		if (head->process_owner->name == NULL || head->process_owner->name[0] == '.') {
			printf("[(#: .),"); // hole
		} else {						
			printf("[(#: %d),", head->pageNumber);
		}
		if (head->status == 1) {
			printf("(P: %c%c)] ", head->process_owner->name[0], head->process_owner->name[1]);
		} else {
			printf("(P:.)] "); // hole
		}
		head = head->next;
	}
	printf("\n\n");
}


void printStatsMFU(int hitCount, int missCount, int numOfProcessesDone) {
	printf("\n\n****************************\n");
	printf("         HIT: %d         \n", hitCount);
	printf("         MISS: %d        \n", missCount);
	printf("      HIT RATIO: %.2f     \n", (float) hitCount / (hitCount + missCount));
	printf("      MISS RATIO: %.2f     \n", ((float) missCount / (hitCount + missCount)));
	printf("****************************\n\n");
	printf("NUMBER OF PROCESSES SUCCESSFULLY SWAPPED: %d\n\n", numOfProcessesDone);

}