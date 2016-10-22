#ifndef SHARED
#define SHARED

/// Total number of processes to create
#define NUMBER_PROCESS 150

struct process{
	char name[2];
	int page_size;
	int arrival_time;
	int completion_time;
};

typedef struct process process;


#endif