#ifndef FIFO
#define FIFO

// Generate page reference based on locality of reference
int getOldestPageFIFO();
void runFIFO(process** prolist, page** pagelist);

#endif