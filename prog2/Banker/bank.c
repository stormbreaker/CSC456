#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include "bank.h"
#include "customer.h"
/*
	Author: Benjamin Kaiser
	Description:  This file contains some of the functions required to run this program.  
	It contains an initialization of the arrays along with the safety_test function and
	the main function.  
*/

/*
	Author: Benjamin Kaiser
	Description:  This function is simply an initialization function.  It bases all of
	the initial values from the originally available resources which were passed in on
	the command line.  
*/
void init_arrays()
{
	int i = 0;
	int j = 0;
	
	// for each customer initialize all the arrays of all the resources
	for (j = 0; j < NUMBER_OF_CUSTOMERS; j++)
	{
		for (i = 0; i < NUMBER_OF_RESOURCES; i++)
		{
			allocation[j][i] = 0;
			maximum[j][i] = available[i]/(NUMBER_OF_CUSTOMERS/2);
			need[j][i] = maximum[j][i] - allocation[j][i];
		}
	}
}

/*
	Author: Benjamin Kaiser
	Description:  This function is the main function for the program.  It creates an array of threads
	that will be "each" customer.  It also converts the command line arguments that were passed in
	into the numbers.  The arrays are then initialized for the banker's data structures.  
*/
int main(int argc, char* argv[])
{

 	pthread_t threads[NUMBER_OF_CUSTOMERS];
	int i = 0;

	// verify command line arguments
	if (argc != NUMBER_OF_RESOURCES + 1)
	{
        printf( "usage: %s <resource counts>\n", argv[0] );
		return 1;
	}
	
	// convert command line arguments
	for (i = 1; i < argc; i++)
	{
		available[i-1] = atoi(argv[i]);
	}

	// initialize arrays
	init_arrays();
   
	// create the threads
	for (i = 0; i < NUMBER_OF_CUSTOMERS; i++)
	{
		customerids[i] = i;
    	pthread_create (&threads[i], NULL, &customer_function, &customerids[i]);
	}

	// join all the threads together
	for (i = 0; i < NUMBER_OF_CUSTOMERS; i++) {
	   pthread_join(threads[i],NULL);
	}

	return 0;
}
/*
	Author: Benjamin Kaiser
	Description:  This function is the actual function which implements the banker's algorithm.

	It essentially loops through the set of processes and makes the assumptions required of the
	bankers algorithm.  These are that each process will request all of it's needs all at once
	and so it needs to know if these resources are available.  It then resets if it finds one
	where this is true after grabbing all of the resources back.

	I based the code of this function off the pseudo-code found here:
	http://cs.uns.edu.ar/~jechaiz/sosd/clases/extras/Banker_s_algorithm_-_Wikipedia__the_free_encyclopedia.pdf
*/
int safety_test()
{
	int i = 0;
	int j = 0;
    int isSafe = 0;
	int allResourcesLess = 1;
    int test_available[NUMBER_OF_RESOURCES];
    int isAbleToFinish[NUMBER_OF_CUSTOMERS];

	// copy actual available resources to a temp array to play with
    for (i = 0; i < NUMBER_OF_RESOURCES; i++)
    {
        test_available[i] = available[i];
    }

	for (i = 0; i < NUMBER_OF_CUSTOMERS; i++)
	{
		// assume all resources needed are less than available
		allResourcesLess = 1;
		// assume isn't safe state
		isSafe = -1;
		// check if process is still in the set
		if (isAbleToFinish[i] == 0)
		{
			// make sure all resource needs are less than available
			for (j = 0; j < NUMBER_OF_RESOURCES; j++)
			{
				if (need[i][j] > test_available[j])
				{
					// this process can't finish on this iteration
					allResourcesLess = 0;
				}
			}

			// reset since this process could finish this round
			if (allResourcesLess == 1)
			{
				for (j = 0; j < NUMBER_OF_RESOURCES; j++)
				{
					test_available[j] += allocation[i][j];
				}
				isAbleToFinish[i] = 1;
				isSafe = 0;
				i = 0;
			}
		}
	}

	// decide which to return.  Originally assume safe.
	isSafe = 0;
	//look for an unsafe state
	for (i = 0; i < NUMBER_OF_CUSTOMERS; i++)
	{
		// oh hey we found an unsafe state
		if (isAbleToFinish[i] == 0)
		{
			isSafe = -1;
		}
	}

    return isSafe;
}
