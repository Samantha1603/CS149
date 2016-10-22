#include <stdio.h>
#include <stdlib.h>
#include "shared.h"

void print_process(process p){
	printf("\n Completion Time: %d Arrival Time: %d Process Name: %c%c\n", p.completion_time, p.arrival_time, p.name[0], p.name[1]);
}

int main(){
	return 0;
}