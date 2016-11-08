
#include <stdio.h>
#include <stdlib.h>
#include "include/shared.h"
#include "include/page_operations.h"
#include "include/LRU.h"


int getLeastUsedPageLRU()
{
    return 0;
}
void runLRU(process **processList, page **pageList)
{
    memoryHelper* current_memory[4];
    for(int i = 0; i < 4; i++)
    {
        current_memory[i] = malloc(sizeof(memoryHelper));
        current_memory[i]->last_used = 0;
        current_memory[i]->pageInMemory = (*processList)->pagesowned[i];
    }
    
}
