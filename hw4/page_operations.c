#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "shared.h"
#include "page_operations.h"

#define TRUE 1
#define FALSE 0

void generate_pageList(page** list){
	page* b_list;
	page* head;
	b_list = malloc(sizeof(page));
	b_list->next = malloc(sizeof(page));
	b_list->status = 0;
	b_list->pageNumber = 0;

	head = b_list->next;

	for(int x = 1; x < NUMBER_PAGES; x++){ //create/initialize page list with 100 avaliable pages.
		head->process_owner = NULL;
		head->next = malloc(sizeof(page));
		head->status = 0;
		head->pageNumber = 0;
		head->process_owner = NULL;
		head = head->next;
	}
	head->next = NULL;
	//free(head); needed?
	*list = b_list;

	return;
}

bool find_4FreePages(page* llist){
	int pagesFound = 0;
	page* head = llist;

	while(pagesFound < 4)
	{
		for(int x = 1; x < NUMBER_PAGES; x++) //iterate through linked list of pages to find 4 available pages.
		{
	        if(head->status == 0)
	        {
	          pagesFound++;
	          head->status = 1;
	        }
	        head = head->next;
		}
	}

	if(pagesFound == 4){
		return true;
	}	
	else{
 	return false;
	}
}

// Remove the page at a given position
void removeAPage(page** list, int nodeIndex) 
{
	page* prev;
	page* temp;

	if (list == NULL || *list == NULL || nodeIndex < 0) return;

	if (nodeIndex == 0) { // Remove head
		temp = (*list)->next;
		free(*list);// COULD CAUSE PROBLEMS. 9/10 WILL CAUSE PROBLEMS
		*list = temp;

	} else {
		prev = *list;
		temp = (*list)->next;

		// Go to the node position 
		for (int x = 1; x < nodeIndex; x++) {
			prev = temp;
			temp = temp->next;
			if (temp == NULL) return;
		}
		prev->next= temp->next; // Skip over the node to be removed
		free(temp); // Remove the node waiting for removal
	}
}

// Add page to first available position, starting from head node
void addPageToMemory(page** list, page* pageToInsert, process* p1, int inMemoryTime, int pageNumber) 
{
	page* current;
	page* temp;
	current = *list;

	if (current->status == 0) { //Insert at head
		temp = current;
		*list = pageToInsert; // Change head to new page
		pageToInsert->next = temp->next;
	} else {
		// Loop as long as current node is occupied 
		while (current->next->status != 0) {
			current = current->next;
		}

		temp = current->next->next;
		current->next = pageToInsert;
		pageToInsert->next = temp; 
	}
	pageToInsert->status = 1; // change status to true when occupied
	pageToInsert->inMemoryTime = inMemoryTime; // time page added to memory
	pageToInsert->process_owner = p1;
	pageToInsert->pageNumber = pageNumber;
	p1->num_page_in_freelist++;
	for(int x = 0; x < p1->page_size; x++){
		if(p1->pagesowned[x].isInMemory == false) p1->pagesowned[x] = *pageToInsert;
		break;
	}
	return;
}

// Created based on suggested procedure for locality of reference
int getPageReference(int pageSize, int lastReference) 
{
	int random = rand() % 11; // 0 -> 10
	int refNum = 0;

	if(random < 7) {
		refNum = lastReference + (rand() % 3) - 1; // -1 -> 1
		if (refNum < 0) refNum = 0; // wrap around

	} else if(random >= 7) {
		refNum = lastReference + (rand() % 8) + 2; // 2 -> 9
		if (refNum > pageSize) refNum = 0; // wrap around 
	}
	return refNum;
}

/**
 * Prints a linked list of pages. Prints the page number and their status e.g. in use or not
 * @param llist linked list of pages
 */
void print_pagesLL(page* llist) {

	page* head = llist;
	for(int x = 0; x < NUMBER_PAGES; x++){
		if(head == NULL) break;
		printf("Status: %d \t Page Number: %d", head->status, head->pageNumber);
		if(head->status == true) printf(" Page Owner: %c\n", head->process_owner->name[0]);
		else printf(" Page Owner: Free\n");
		head = head->next;
	}
}