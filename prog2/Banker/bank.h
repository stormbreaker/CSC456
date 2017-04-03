#include <pthread.h>

/*
	Author: Benjamin Kaiser
	Description:  This file contains all of the global arrays necessary to implement the banker's algorithm
	It also has the function prototype of the function that actually is the banker's algorithm.  
*/

// values must be anything greater than 0
#define NUMBER_OF_CUSTOMERS 5
#define NUMBER_OF_RESOURCES 3

pthread_mutex_t mutex;

int customerids[NUMBER_OF_CUSTOMERS];

/* the available amount of each resource */
int available[NUMBER_OF_RESOURCES];

/* the maximum demand of each customer */
int maximum[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES];

/* the amount currently allocated to each customer */
int allocation[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES];

/* the remaining need of each customer */
int need[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES];

// function prototype
int safety_test();
