#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "shared.h"

void generate_pageList(page** list)
{
	page* b_list;
	page* head;
	b_list = malloc(sizeof(page));
	b_list->next = malloc(sizeof(page));
	b_list->status = 0;
	head = b_list->next;

	for(int x = 1; x < NUMBER_PAGES; x++){ //create/initialize page list with 100 avaliable pages.
		
		head->next = malloc(sizeof(page));
		head = head->next;
	}
	head->next = NULL;
	//free(head); needed?
	*list = b_list;
	return;
}

bool find_4FreePages(page* llist)
{
	/*
	int pagesFound = 0;
	while(pagesFound < 4) {
	for(int x = 1; x < NUMBER_PAGES; x++) { //iterate through linked list of pages to find 4 available pages.
		if(head->status = 0) {
			pagesFound++;
          	head->status = 1;
        }
        head = head->next;
	}
	}
	
	if(pagesFound == 4) {
		return true;
	}	else{
		return false;
	}*/
	return false;
}

// Remove the page at a given position
void removeAPage(page** list, int nodeIndex) 
{

	page* previous;
	page* temp;

	if (list == NULL || *list == NULL || nodeIndex < 0) return;

	if (nodeIndex == 0) {
		temp = (*list)->next;
		free(*list);
		*list = temp;
	} else {
		previous = *list;
		temp = (*list)->next;

		for (int x = 1; x < nodeIndex; x++) {
			previous = temp;
			temp = temp->next;
			if (temp == NULL) return;
		}

		previous->next= temp->next; // Connection previous to the node after deleted node
		free(temp);
	}
}


void addPageToMemory() 
{

}

// Created based on suggested procedure for locality of reference
int getPageReference() 
{
	int random = rand() % 11; // 0 -> 10
	int refNum = 0;

	if(random < 7) {
		refNum = (rand() % 3) - 1; // -1 -> 1
	} else if(random >= 7) {
		refNum = (rand() % 8) + 2; // 2 -> 9
	}
	return refNum;
}

void print_pagesLL(page* llist) {

	page* head = llist;
	for(int x = 0; x < NUMBER_PAGES; x++){
		if(head == NULL) break;
		printf("Status: %d \t\n", head->status);
		head = head->next;
	}
}



