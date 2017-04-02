#include "customer.h"
#include <stdio.h>

void print_state()
{
	int i = 0;
	int j = 0;
	int k = 0;
	printf("\tAllocated\tNeed\tAvailable\n");
    printf("\t");

    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < NUMBER_OF_RESOURCES; j++)
        {
            printf("%c ", 'A' + j);
        }

        printf("\t\t");
    }

    printf("\n");

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

            printf("\t\t");
        }

        printf("\n");
    }
}


void* customer_function(void* param)
{
	char done = 0;
	int i = 0;
	int request_array[NUMBER_OF_RESOURCES];
	int release_array[NUMBER_OF_RESOURCES];
	int my_id = *((int*) param);

	int canRelease = 0;

	while (done == 0)
	{		

		for (i = 0; i < NUMBER_OF_RESOURCES; i++)
		{
			if (need[my_id][i] > 0)
			{
				request_array[i] = rand() % need[my_id][i] + 1;
			}
		}
		
		canRelease = request_resources(my_id, request_array);

		for (i = 0; i < NUMBER_OF_RESOURCES; i++)
		{
			if (allocation[my_id][i] > 0)
			{
				release_array[i] = rand() % allocation[my_id][i] + 1;
			}
		}

		print_state();

		done = 1;

		for (i = 0; i < NUMBER_OF_RESOURCES; i++)
		{
			if (need[my_id][i] > 0)
			{
				done = 0;
			}
		}

		if (done == 1)
		{
			for (i = 0; i < NUMBER_OF_RESOURCES; i++)
			{
				release_array[i] = allocation[my_id][i];
			}
		}
		if (canRelease == 0)
		{
			release_resources(my_id, release_array);
		}
	}
}

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
	printf("Request P%d <", customer_num);
	for (i = 0; i < NUMBER_OF_RESOURCES - 1; i++)
	{
		printf("%d, ", request[i]);
	}
	printf("%d>\n", request[NUMBER_OF_RESOURCES - 1]);
	fflush(stdout);

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

	safe = safety_test();

	if (safe == 0)
	{
		for (i = 0; i < NUMBER_OF_RESOURCES; i++)
		{
			allocation[customer_num][i] = allocation[customer_num][i] + request[i];
			available[i] = available[i] - request[i];
			need[customer_num][i] = need[customer_num][i] - request[i];	
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

int release_resources(int customer_num, int release[])
{
    /* acquire the mutex lock and warn if unable */
    if (pthread_mutex_lock(&mutex) != 0)
    {
        printf("Unable to lock mutex\n");
        return -1;
    }


	int i = 0;
	printf("Release P%d <", customer_num);
	for (i = 0; i < NUMBER_OF_RESOURCES - 1; i++)
	{
		printf("%d, ", release[i]);
	}
	printf("%d>\n", release[NUMBER_OF_RESOURCES - 1]);
	fflush(stdout);

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
