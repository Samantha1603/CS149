#include <stdio.h>
#include <stdlib.h>
#include "shared.h"
#include "seller.h"


void print_sellers(seller* list, int length){
	char* p; 
	char* i_p =(char*) &list[0].sales_price;
	for(int x = 0; x < length; x++){
		p = (char*) &list[x];
		printf("%c-%c%c Sales Price: %d\n", *p, *(p + 1), *(p + 2), *( (int*) i_p) );
		i_p += (sizeof(seller));
	}
	return;
}

void* sell_seats(void* seat_seller){
	int current_customer = 0;
	while(!start) pthread_cond_wait(&cond, &seat_access);
	pthread_mutex_unlock(&seat_access);
	seller* seat_seller_s = (seller*) seat_seller;
	while(filled_seats < TOTAL_SEATS){
		// add check for customer arrival before trying lock
		pthread_mutex_lock(&seat_access);
		for(int x = 0; x < (TOTAL_SEATS * 3); x += 3){
			//buy a seat
			if(*(seat_map + x) == (char) 45){
				*(seat_map + x) = (*seat_seller_s).name[0];
				*(seat_map + x + 1) = (*seat_seller_s).name[1];
				*(seat_map + x + 2) = (*seat_seller_s).name[2];
				current_customer++;
				break;
			}
		}
		filled_seats++;
		pthread_mutex_unlock(&seat_access);
	}
	pthread_exit(NULL);
}
