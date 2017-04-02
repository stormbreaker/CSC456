#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include "bank.h"
#include "customer.h"

int main(int argc, char* argv[])
{

	if (argc != 3)
	{
		/* We print argv[0] assuming it is the program name */
        printf( "usage: %s <resource counts>\n", argv[0] );
		return 1;
	}

    pthread_t thread[NUMBER_OF_CUSTOMERS];
	int i = 0;
	for (i = 0; i < NUMBER_OF_CUSTOMERS; i++)
	{
    	pthread_create (&thread, NULL, &thread_function, NULL);
	}	

	return 0;

}
