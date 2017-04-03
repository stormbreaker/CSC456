#include "customer.h"
#include <stdio.h>

/*
	Author: Benjamin Kaiser
	Description:  This function is the function that handles all of the printing
	of information.  It prints the headers and the column headers for the resources.
	It then goes through and prints the proper resource information for each resource.
*/
void print_state()
{
	int i = 0;
	int j = 0;
	int k = 0;
	// table headers
	printf("\tAllocated");
	for (j = 0; j < NUMBER_OF_RESOURCES - 2; j++)
	{
    	printf("\t");
	}
	printf("Need");
	for (j = 0; j < NUMBER_OF_RESOURCES - 2; j++)
	{
    	printf("\t");
	}	
	printf("Available\n");
    printf("\t");

	// column headers
    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < NUMBER_OF_RESOURCES; j++)
        {
            printf("%c ", 65 + j);
        }
		for (j = 0; j < NUMBER_OF_RESOURCES - 2; j++)
		{
        	printf("\t");
		}
    }

    printf("\n");

	// print resource information
    for (i = 0; i < NUMBER_OF_CUSTOMERS; i++)
    {
        printf("P%d\t", i);

        for (k = 0; k < 3; k++)
        {
            for (j = 0; j < NUMBER_OF_RESOURCES; j++)
            {
                if (k == 0)
                {
                    printf("%d ", allocation[i][j]);
                }
                else if (k == 1)
                {
                    printf("%d ", need[i][j]);
                }
                else if (i == 0 && k == 2)
                {
                    printf("%d ", available[j]);
                }
            }
			for (j = 0; j < NUMBER_OF_RESOURCES - 2; j++)
			{
		    	printf("\t");
			}
        }

        printf("\n");
    }
}

/*
	Author: Benjamin Kaiser
	Description:  This function is the main function that is run for the thread.  
	It takes a param which we pass in as the customer id for the thread.  It then
	loops and requests resources to run and then releases a random amount.  If
	it has reached a value of 0 in all of the positions of the number of resources,
	it terminates.  
*/
void* customer_function(void* param)
{
	char done = 0;
	int i = 0;
	int request_array[NUMBER_OF_RESOURCES];
	int release_array[NUMBER_OF_RESOURCES];
	int my_id = *((int*) param);

	int canRelease = 0;

	// while this process is still running.
	while (done == 0)
	{		
		// determine random amount of resources to ask for
		for (i = 0; i < NUMBER_OF_RESOURCES; i++)
		{
			if (need[my_id][i] > 0)
			{
				request_array[i] = rand() % need[my_id][i] + 1;
			}
		}
		
		// request the resources
		canRelease = request_resources(my_id, request_array);

		// ask for random amount of resources to release
		for (i = 0; i < NUMBER_OF_RESOURCES; i++)
		{
			if (allocation[my_id][i] > 0)
			{
				release_array[i] = rand() % allocation[my_id][i] + 1;
			}
		}

		// print state of system
		print_state();

		// assume we're done
		done = 1;

		// check if we're actually done
		for (i = 0; i < NUMBER_OF_RESOURCES; i++)
		{
			if (need[my_id][i] > 0)
			{
				done = 0;
			}
		}

		// if we're done, then we need to give up all the resources
		if (done == 1)
		{
			for (i = 0; i < NUMBER_OF_RESOURCES; i++)
			{
				release_array[i] = allocation[my_id][i];
			}
		}
		
		// we can only release if we actually got resources
		if (canRelease == 0)
		{
			release_resources(my_id, release_array);
		}
	}
}

/*
	Author: Benjamin Kaiser
	Description:  This function is the request function for the customer
	thread.  It takes a thread id and an array which contians values for how many of each resource to request.
	
*/
int request_resources(int customer_num, int request[])
{
    /* acquire the mutex lock and warn if unable */
    if (pthread_mutex_lock(&mutex) != 0)
    {
        printf("Unable to lock mutex\n");
        return -1;
    }	

	int i = 0;
	int safe = 0;
	//print what we're requesting.
	printf("Request P%d <", customer_num);
	for (i = 0; i < NUMBER_OF_RESOURCES - 1; i++)
	{
		printf("%d, ", request[i]);
	}
	printf("%d>\n", request[NUMBER_OF_RESOURCES - 1]);
	fflush(stdout);

	// check to see if we are asking for the proper amount.  
	for (i = 0; i < NUMBER_OF_RESOURCES; i++)
	{
		if (request[i] > available[i])
		{
			printf(" Request DENIED (asked for more than available)\n");
	
			/* acquire the mutex lock and warn if unable */
			if (pthread_mutex_unlock(&mutex) != 0)
			{
				printf("Unable to unlock mutex\n");
				return -1;
			}
			return - 1;
		}
	}

	// if asking for less than available, run banker's algorithm
	safe = safety_test();

	// if the state is good actually allocate the resources.
	if (safe == 0)
	{
		for (i = 0; i < NUMBER_OF_RESOURCES; i++)
		{
			allocation[customer_num][i] = allocation[customer_num][i] + request[i];
			available[i] = available[i] - request[i];
			need[customer_num][i] = need[customer_num][i] - request[i];	
			// since random could go over necessary needed, then clip our need...
			if (need[customer_num][i] < 0)
			{
				need[customer_num][i] = 0;
			}	
		}

		/* acquire the mutex lock and warn if unable */
		if (pthread_mutex_unlock(&mutex) != 0)
		{
		    printf("Unable to unlock mutex\n");
		    return -1;
		}
		return 0;
	}

	// if the state is unsafe exit and return bad state
	else
	{
		printf(" Request DENIED (unsafe state)\n");
		fflush(stdout);
		/* acquire the mutex lock and warn if unable */
		if (pthread_mutex_unlock(&mutex) != 0)
		{
		    printf("Unable to unlock mutex\n");
		    return -1;
		}
		return - 1;
	}
}

/*
	Author: Benjamin Kaiser
	Description:  This function is the function that a customer calls to release resources.
	It takes a thread id and an array containing the values of each resource to release.
	It then always releases these.  
*/
int release_resources(int customer_num, int release[])
{
    /* acquire the mutex lock and warn if unable */
    if (pthread_mutex_lock(&mutex) != 0)
    {
        printf("Unable to lock mutex\n");
        return -1;
    }


	int i = 0;
	//print what we're releasing
	printf("Release P%d <", customer_num);
	for (i = 0; i < NUMBER_OF_RESOURCES - 1; i++)
	{
		printf("%d, ", release[i]);
	}
	printf("%d>\n", release[NUMBER_OF_RESOURCES - 1]);
	fflush(stdout);

	// do the release
    for (i = 0; i < NUMBER_OF_RESOURCES; i++)
    {
        available[i] = available[i] + release[i];
        allocation[customer_num][i] = allocation[customer_num][i] - release[i];
    }

    /* acquire the mutex lock and warn if unable */
    if (pthread_mutex_unlock(&mutex) != 0)
    {
        printf("Unable to unlock mutex\n");
        return -1;
    }

	return 0;
}
