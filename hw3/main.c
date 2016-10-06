#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "seller.h"
#include "customer.h"
#include "shared.h"
#include "algorithms.h"

#define NUM_OF_H_SELLERS 1
#define NUM_OF_M_SELLERS 3
#define NUM_OF_L_SELLERS 6

void wake_up(){
	pthread_mutex_lock(&seat_access);
	start = true;
	pthread_cond_broadcast(&cond);
	pthread_mutex_unlock(&seat_access);
}

void print_seats();

int main(){

	//Initilization of variables
	int seed = 0;
	srand(seed);
	start = false;
	seat_map = malloc(TOTAL_SEATS * (sizeof(char) * 3)); //100 seats can store 3 each seat
	memset(seat_map, 45, TOTAL_SEATS * (sizeof(char) * 3));
	seller* h_sellers = malloc(sizeof(seller) * NUM_OF_H_SELLERS);//create h_sellers
	seller* m_sellers = malloc(sizeof(seller) * NUM_OF_M_SELLERS);//create m_sellers
	seller* l_sellers = malloc(sizeof(seller) * NUM_OF_L_SELLERS);//create l_sellers
	filled_seats = 0;

	//Setting logs and threads
	seat_access = PTHREAD_MUTEX_INITIALIZER;
	cond = PTHREAD_COND_INITIALIZER;
	pthread_t h_seller_thread;
	pthread_t m_sellers_thread[10];
	pthread_t l_sellers_thread[10];

	//For the future broadcast call to restart threads

	for(int x = 0; x < NUM_OF_H_SELLERS; x++){
		if(x < 10){
			h_sellers[x].name[0] = 'H'; 
			h_sellers[x].name[1] = (char) 48;
			h_sellers[x].name[2] = (char) (x + 48);
		}
		else{
			h_sellers[x].name[0] = 'H';
			h_sellers[x].name[1] = '1';
			h_sellers[x].name[2] = '2';
		}
		make_customers(&(h_sellers[x].start_queue), NUM_OF_CUSTOMERS);
		h_sellers[x].sales_price = 3;
	}

	//Populate all medium sellers
	for(int x = 0; x < NUM_OF_M_SELLERS; x++){
		if(x < 10){
			m_sellers[x].name[0] = 'M'; 
			m_sellers[x].name[1] = (char) 48;
			m_sellers[x].name[2] = (char) (x + 48);
		}
		else{
			m_sellers[x].name[0] = 'M';
			m_sellers[x].name[1] = '1';
			m_sellers[x].name[2] = '2';
		}
		make_customers(&(m_sellers[x].start_queue), NUM_OF_CUSTOMERS);
		m_sellers[x].sales_price = 2;
	}

	for(int x = 0; x < NUM_OF_L_SELLERS; x++){
		if(x < 10){
			l_sellers[x].name[0] = 'L'; 
			l_sellers[x].name[1] = (char) 48;
			l_sellers[x].name[2] = (char) (x + 48);
		}
		else{
			l_sellers[x].name[0] = 'L';
			l_sellers[x].name[1] = '1';
			l_sellers[x].name[2] = '2';
		}
		make_customers(&(l_sellers[x].start_queue), NUM_OF_CUSTOMERS);
		l_sellers[x].sales_price = 1;
	}


	print_customers(h_sellers[0].start_queue, NUM_OF_CUSTOMERS);
	sort(h_sellers[0].start_queue, &h_sellers[0].start_queue[0].arrival_time, sizeof(customer), NUM_OF_CUSTOMERS);
	
	printf("\n-----------------------------after sort------------------\n");

	print_customers(h_sellers[0].start_queue, NUM_OF_CUSTOMERS);


	for(int x = 0; x < NUM_OF_M_SELLERS; x++){
	pthread_create(&(m_sellers_thread[x]), NULL, sell_seats, (void*) &m_sellers[x]);
	}
	for(int x = 0; x < NUM_OF_L_SELLERS; x++){
		pthread_create(&(l_sellers_thread[x]), NULL, sell_seats, (void*) &l_sellers[x]);
	}
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

	print_seats();

	return 0;
}

void print_seats(){
	for(int x = 0; x < (TOTAL_SEATS * 3); x += 3){
		printf("|%c%c%c| ", seat_map[x], seat_map[x + 1], seat_map[x + 2]);
		if(x % 30 == 0 && x > 0) printf("\n");
	}
}