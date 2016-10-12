#ifndef CUSTOMER
#define CUSTOMER

///number of customers for each queue
#define NUM_OF_CUSTOMERS 10

struct customer{
	///// Time of arrival to seller
	int arrival_time; 
};

typedef struct customer customer;

/**
 * make_customers creates an array of customers
 * @param queue  pointer to where customers should be stored
 * @param length length of queue to create
 */
void make_customers(customer** queue, int length);

/**
 * print_customers prints a list of customers
 * @param list   list of customers to print
 * @param length length of list
 */
void print_customers(customer* list, int length);

#endif