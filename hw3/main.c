#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#include "seller.h"
#include "customer.h"
#include "shared.h"
#include "algorithms.h"


#define NUM_OF_H_SELLERS 1
#define NUM_OF_M_SELLERS 3
#define NUM_OF_L_SELLERS 6
#define MINUTES 60 

struct itimerval sellerTimer;

void wake_up(){
	pthread_mutex_lock(&seat_access);
	start = true;
	pthread_cond_broadcast(&cond);
	pthread_mutex_unlock(&seat_access);
}

//void print_seats();

int main(){
	//Initilization of variables
	int seed = time(NULL);
	srand(seed);
	start = false;
	m_t_sold = 0;
	l_t_sold = 0;
	h_t_sold = 0;
	// Set timer
    sellerTimer.it_value.tv_sec = MAX_MINUTES;
    setitimer(ITIMER_REAL, &sellerTimer, NULL);
    time(&startTime);

	time_t currentTime; // type calender time
    time(&currentTime);
    int sec = (int) difftime(currentTime, startTime);
   
    printf("Timer- %1d:%02d\n", (int) (sec / 60), (int) sec % 60);


	seat_map = malloc(TOTAL_SEATS * (sizeof(char) * 4)); //100 seats can store 4 each seat
	memset(seat_map, 45, TOTAL_SEATS * (sizeof(char) * 4));
	seller* h_sellers = malloc(sizeof(seller) * NUM_OF_H_SELLERS);//create h_sellers
	seller* m_sellers = malloc(sizeof(seller) * NUM_OF_M_SELLERS);//create m_sellers
	seller* l_sellers = malloc(sizeof(seller) * NUM_OF_L_SELLERS);//create l_sellers
	filled_seats = 0;

	//Setting and threads
	seat_access = (pthread_mutex_t) PTHREAD_MUTEX_INITIALIZER;
	cond = (pthread_cond_t) PTHREAD_COND_INITIALIZER;
	pthread_t h_seller_thread;
	pthread_t m_sellers_thread[10]; 
	pthread_t l_sellers_thread[10]; 

	//For the future broadcast call to restart threads

	// Populate high seller
	for(int x = 0; x < NUM_OF_H_SELLERS; x++){

		if(x < 10){
			h_sellers[x].name[0] = 'H'; 
			h_sellers[x].name[1] = (char) (x + '0'); // seller id
			//h_sellers[x].name[1] = (char) 48;
			h_sellers[x].name[2] = (char) (x + 48);
		}
		else{
			h_sellers[x].name[0] = 'H';
			h_sellers[x].name[1] = (char) (x + '0');
			//h_sellers[x].name[1] = '1';
			h_sellers[x].name[2] = '2';
		}
		make_customers(&(h_sellers[x].start_queue), NUM_OF_CUSTOMERS);
		h_sellers[x].sales_price = 3;
	}

	//Populate all medium sellers
	for(int x = 0; x < NUM_OF_M_SELLERS; x++){

		if(x < 10){
			m_sellers[x].name[0] = 'M';
			m_sellers[x].name[1] = (char) (x + '0');
			//m_sellers[x].name[1] = (char) 48;
			m_sellers[x].name[2] = (char) (x + 48);
		}
		else{
			m_sellers[x].name[0] = 'M';
			m_sellers[x].name[1] = (char) (x + '0');
			//m_sellers[x].name[1] = '1';
			m_sellers[x].name[2] = '2';
		}
		make_customers(&(m_sellers[x].start_queue), NUM_OF_CUSTOMERS);
		m_sellers[x].sales_price = 2;
	}

	// Populate all low sellers
	for(int x = 0; x < NUM_OF_L_SELLERS; x++){

		if(x < 10){
			l_sellers[x].name[0] = 'L'; 
			l_sellers[x].name[1] = x + '0';
			//l_sellers[x].name[1] = (char) 48;
			l_sellers[x].name[2] = (char) (x + 48);
		}
		else{
			l_sellers[x].name[0] = 'L';
			l_sellers[x].name[1] = x + '0';
			//l_sellers[x].name[1] = '1';
			l_sellers[x].name[2] = '2';
		}
		make_customers(&(l_sellers[x].start_queue), NUM_OF_CUSTOMERS);
		l_sellers[x].sales_price = 1;
	}


	printf("\n----------------QUEUE H seller-------------------------------\n");
	//print_customers(h_sellers[0].start_queue, NUM_OF_CUSTOMERS);
	//sort(h_sellers[0].start_queue, &h_sellers[0].start_queue[0].arrival_time, sizeof(customer), NUM_OF_CUSTOMERS);
	//printf("\n-----------------------------after sort------------------\n");
	print_customers(h_sellers[0].start_queue, NUM_OF_CUSTOMERS);

	printf("\n----------------QUEUE FIRST M seller-------------------------------\n");
	//print_customers(m_sellers[0].start_queue, NUM_OF_CUSTOMERS);
	//sort(m_sellers[0].start_queue, &m_sellers[0].start_queue[0].arrival_time, sizeof(customer), NUM_OF_CUSTOMERS);
	//printf("\n-----------------------------after sort------------------\n");
	print_customers(m_sellers[0].start_queue, NUM_OF_CUSTOMERS);

	printf("\n----------------QUEUE SECOND M seller-------------------------------\n");
	//print_customers(m_sellers[1].start_queue, NUM_OF_CUSTOMERS);
	//sort(m_sellers[1].start_queue, &m_sellers[1].start_queue[0].arrival_time, sizeof(customer), NUM_OF_CUSTOMERS);
	//printf("\n-----------------------------after sort------------------\n");
	print_customers(m_sellers[1].start_queue, NUM_OF_CUSTOMERS);

	printf("\n----------------QUEUE THIRD M seller-------------------------------\n");
	//print_customers(m_sellers[2].start_queue, NUM_OF_CUSTOMERS);
	//sort(m_sellers[2].start_queue, &m_sellers[2].start_queue[0].arrival_time, sizeof(customer), NUM_OF_CUSTOMERS);
	//printf("\n-----------------------------after sort------------------\n");
	print_customers(m_sellers[2].start_queue, NUM_OF_CUSTOMERS);

	printf("\n----------------QUEUE FIRST L seller-------------------------------\n");
	//print_customers(l_sellers[0].start_queue, NUM_OF_CUSTOMERS);
	//sort(l_sellers[0].start_queue, &l_sellers[0].start_queue[0].arrival_time, sizeof(customer), NUM_OF_CUSTOMERS);
	//printf("\n-----------------------------after sort------------------\n");
	print_customers(l_sellers[0].start_queue, NUM_OF_CUSTOMERS);

	printf("\n----------------QUEUE SECOND L seller-------------------------------\n");
	//sort(l_sellers[1].start_queue, &l_sellers[1].start_queue[0].arrival_time, sizeof(customer), NUM_OF_CUSTOMERS);
	print_customers(l_sellers[1].start_queue, NUM_OF_CUSTOMERS);

	printf("\n----------------QUEUE THIRD L seller-------------------------------\n");
	//sort(l_sellers[2].start_queue, &l_sellers[2].start_queue[0].arrival_time, sizeof(customer), NUM_OF_CUSTOMERS);
	print_customers(l_sellers[2].start_queue, NUM_OF_CUSTOMERS);

	printf("\n----------------QUEUE FOURTH L seller-------------------------------\n");
	//sort(l_sellers[3].start_queue, &l_sellers[3].start_queue[0].arrival_time, sizeof(customer), NUM_OF_CUSTOMERS);
	print_customers(l_sellers[3].start_queue, NUM_OF_CUSTOMERS);

	printf("\n----------------QUEUE FIFTH L seller-------------------------------\n");
	//sort(l_sellers[4].start_queue, &l_sellers[4].start_queue[0].arrival_time, sizeof(customer), NUM_OF_CUSTOMERS);
	print_customers(l_sellers[4].start_queue, NUM_OF_CUSTOMERS);

	printf("\n----------------QUEUE SIXTH L seller-------------------------------\n");
	//sort(l_sellers[5].start_queue, &l_sellers[5].start_queue[0].arrival_time, sizeof(customer), NUM_OF_CUSTOMERS);
	print_customers(l_sellers[5].start_queue, NUM_OF_CUSTOMERS);

	// Create seller M threads
	for(int x = 0; x < NUM_OF_M_SELLERS; x++){ 
		// arguments(structure, NULL, function that runs in thread, argument to sell_seats function)
		pthread_create(&(m_sellers_thread[x]), NULL, sell_seats, (void*) &m_sellers[x]);
	}
	// Create seller L threads
	for(int x = 0; x < NUM_OF_L_SELLERS; x++){
		pthread_create(&(l_sellers_thread[x]), NULL, sell_seats, (void*) &l_sellers[x]);
	}
	// Create seller H thread
	pthread_create(&h_seller_thread, NULL, sell_seats, h_sellers);

	wake_up();

	//join all threads
	pthread_join(h_seller_thread, NULL);
	for(int x = 0; x < NUM_OF_L_SELLERS; x++){
		pthread_join(l_sellers_thread[x], NULL);
	}
	for(int x = 0; x < NUM_OF_M_SELLERS; x++){
		pthread_join(m_sellers_thread[x], NULL);
	}
	//print_seats();
	printf("\n----------------FINISHED------------------------\n");

	printf("\nTotal H tickets sold: %d Total M tickets sold: %d Total L tickets sold: %d\n", h_t_sold, m_t_sold, l_t_sold);

	return 0;
}
/* deprecated
void print_seats(){
	for(int x = 0; x < (TOTAL_SEATS * 4); x += 4){
		printf("|%c%c%c%c| ", seat_map[x], seat_map[x + 1], seat_map[x + 2], seat_map[x + 3]);
		if(x % 40 == 0 && x > 0) printf("\n");
	}
}
*/