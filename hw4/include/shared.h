#ifndef SHARED
#define SHARED

/// Total number of processes to create
#define NUMBER_PROCESS 11

#define TOTAL_TIME 100;

struct process{
	char name[2];// 1 Char per MB? only 1 Char per name?
	int page_size; // Can be 5, 11, 17, and 31
	int arrival_time; // 
	int completion_time; // Can be 1, 2, 3, 4, or 5
	struct process* next; // makes possible to create linked list
};

typedef struct process process;


#endif