#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "shared.h"
#include "page_operations.h"
#include "process_operations.h"


//We only use algorithm when memory is full.
//Increment the frequency for that page that comes into memory.
//Lowest frequency page is kicked out of memory.
//If there are 2 or more pages with the same lowest frequency, then kick out the oldest page.
//When page is kicked out, reset that pages frequency to 0.
