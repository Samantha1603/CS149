#ifndef PROCESS_OPERATIONS
#define PROCESS_OPERATIONS

/**
 * Prints a single process
 * @param p single process to print
 */
void print_process(process p);

/**
 * prints a linked list of processes
 * @param llist beginning of linked list to print
 */
void print_ll(process* llist);

/**
 * Generates a linked list of processes. Arrival time is according to shared.h variables
 * TODO: Add more characters to the alphabet to limit repitition
 * @param list pointer that will point to the beginning of the linkedl ist
 */
void generate_processes(process** list);

/**
 * Sorts a linked list of processes by arrival time
 * NOT FUNCTIONAL
 * @param list linked list to sort, starting at first process in the list
 */
void sort_pll(process** list);

void sort_pll_r(process** list, int lo, int hi);

#endif