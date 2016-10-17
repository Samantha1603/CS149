#ifndef SHARED
#define SHARED
#include "pthread.h"
#include <stdbool.h>

///Total Number of seats that can be sold
#define TOTAL_SEATS 100	
// Total minutes to sell
#define MAX_MINUTES 60 

/// Restricts access to seats
pthread_mutex_t seat_access; 

pthread_cond_t cond;

time_t startTime;

///Counts how many seats are filled - semaphore
int filled_seats; 

///Actual map of location of seats - inc 0, 3, 6, 9 due to 3 chars being stored per seat
char* seat_map; 

///When to start selling
bool start; 

#endif