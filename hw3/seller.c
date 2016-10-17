#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
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

	// Wait for seat access then unlock 
	while(!start) pthread_cond_wait(&cond, &seat_access);
	pthread_mutex_unlock(&seat_access);
	seller* seat_seller_s = (seller*) seat_seller;


   	for (int i = 0; i < NUM_OF_CUSTOMERS; i++)  {

		time_t after;
    	time(&after);
    	int currentTime = (int) difftime(after, startTime);

   		printf("\n....Timer- %1d:%02d\n\n", currentTime / 60, currentTime % 60);
   		sleep(seat_seller_s->start_queue[i].arrival_time); // Sleep so the process will only run on its arrival time..not working.		

   		/*
		printf("\n CUSTOMER ID %c is being served \n\n", ((seller *) seat_seller_s)->start_queue[i].customer_id);*/
		char currentCustomer[2];
		currentCustomer[1] = seat_seller_s->start_queue[i].customer_id[1]; 
		currentCustomer[0] = seat_seller_s->start_queue[i].customer_id[0];
		printf("\nCUSTOMER ID %c%c SELLER %c%c NOW AT %d \n\n", seat_seller_s->start_queue[i].customer_id[0], seat_seller_s->start_queue[i].customer_id[1], 
				seat_seller_s->name[0],
				seat_seller_s->name[1],
				seat_seller_s->start_queue[i].arrival_time);

	// Continue as long as seats are not filled and minute hasn't hit 60
	//while((filled_seats < TOTAL_SEATS) || (currentTime % 60 != 60)){
	// add check for customer arrival before trying lock
	
		pthread_mutex_lock(&seat_access);

		if (seat_seller_s->sales_price == 1) {
			// L seller

			printf("\nCustomer %c%c being served\n", currentCustomer[0], currentCustomer[1]);
			sleep((rand() % 4) + 4); // Sell for 4,5,6 or 7 minutes

			// Sell seat starting with row 10 and work towards the front
			for(int x = 396; x > 0; x -= 4){
				if(*(seat_map + x) == (char) 45){ // (char) 45 = '-'
					//printf("Customer L%d%02d is now being served", min / 60, min % 60, id % 10, count + 1);

					time_t after;
                    time(&after);
                    int aftertime = (int) difftime(after, startTime);
					
					*(seat_map + x) = (*seat_seller_s).name[0];
					*(seat_map + x + 1) = (*seat_seller_s).name[1];
					//TODO: ADD SLOT FOR CUSTOMER
					*(seat_map + x + 2) = currentCustomer[0];
					*(seat_map + x + 3) = currentCustomer[1];
					l_t_sold++;
					print_seat();

					printf("\nCustomer %c%c of seller %c%c - Timer- %1d:%02d purchased a ticket", currentCustomer[0], currentCustomer[1],
						(*seat_seller_s).name[0], (*seat_seller_s).name[1], aftertime / 60, aftertime % 60);

					break;
				}
			}

		} else if (seat_seller_s->sales_price == 2) {
			// M seller

			printf("\nCustomer %c%c being served\n", currentCustomer[0], currentCustomer[1]);
			sleep((rand() % 3) + 2); // Sell for 2,3 or 4 minutes

			// Sell seat starting with row 5 then 6 then 4 then 7
			int startingIndex = 160;
			int seatNotSold = 1;

			do {
				if (*(seat_map + startingIndex) == (char) 45) {

					time_t after;
                    time(&after);
                    int aftertime = (int) difftime(after, startTime);
					
					*(seat_map + startingIndex) = (*seat_seller_s).name[0];
					*(seat_map + startingIndex + 1) = (*seat_seller_s).name[1];
					*(seat_map + startingIndex + 2) = currentCustomer[0];
					*(seat_map + startingIndex + 3) = currentCustomer[1];
					seatNotSold = 0; // Seat now sold
					m_t_sold++;
					print_seat();

					printf("\nCustomer %c%c of seller %c%c - Timer- %1d:%02d purchased a ticket", currentCustomer[0], currentCustomer[1],
						(*seat_seller_s).name[0], (*seat_seller_s).name[1], aftertime / 60, aftertime % 60);
				}
				startingIndex += 4; // Increment by 3 in index

				// Switching for 5->6->4->7 only
				if (startingIndex == 220) { // Hit 7 after end of 6, go back to row 4
					startingIndex = 130; // Index of row 4
				} else if (startingIndex == 160) { // Hit row 5 after end of 4, go to row 7
					startingIndex = 220;
				}

			} while (seatNotSold);
		
		} else if (seat_seller_s->sales_price == 3) {
			// H Seller sales_price = 3

			printf("\nCustomer %c%c being served\n", currentCustomer[0], currentCustomer[1]);
			sleep((rand() % 1) + 1); // Sell for 1 or 2 minutes
			// Sell seat starting with row 1 then worl towards the front
			for(int x = 0; x < (TOTAL_SEATS * 4); x += 4){
				if(*(seat_map + x) == (char) 45){
					time_t after;
                    time(&after);
                    int aftertime = (int) difftime(after, startTime);

            		*(seat_map + x) = (*seat_seller_s).name[0];
					*(seat_map + x + 1) = (*seat_seller_s).name[1];
					*(seat_map + x + 2) = currentCustomer[0];
					*(seat_map + x + 3) = currentCustomer[1];
					h_t_sold++;
					print_seat();

					printf("\nCustomer %c%c of seller %c%c - Timer- %1d:%02d purchased a ticket", currentCustomer[0], currentCustomer[1],
						(*seat_seller_s).name[0], (*seat_seller_s).name[1], aftertime / 60, aftertime % 60);
					break;
				}
			}
		}

		filled_seats++;
		pthread_mutex_unlock(&seat_access);
	}
	//}

	pthread_exit(NULL);
}

void print_seat(){
	printf("\n\n");
	for(int x = 0; x < (TOTAL_SEATS * 4); x += 4){
		printf("|%c%c%c%c| ", seat_map[x], seat_map[x + 1], seat_map[x + 2], seat_map[x + 3]);
		if (x == 36 || x == 76 || x == 116 || x == 156 || x == 196 || x == 236 ||
			x == 276 || x == 316 || x == 356) {
			printf("\n");
		}
	}
	printf("\n\n");
}
