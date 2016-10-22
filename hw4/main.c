#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "shared.h"
#include "process_operations.h"
/// Amount of memory in MB
#define MEMORY 100

///Page size in MB
#define PAGE_SIZE 1

int main(){
	srand(time(NULL));
	// Generate Processes
	process* llist;
	generate_processes(&llist);
	print_ll(llist);
	return 0;
}
