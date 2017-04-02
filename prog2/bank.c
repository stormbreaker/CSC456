#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include "bank.h"
#include "customer.h"

void init_arrays()
{
	int i = 0;
	int j = 0;
	for (j = 0; j < NUMBER_OF_CUSTOMERS; j++)
	{
		for (i = 0; i < NUMBER_OF_RESOURCES; i++)
		{
			allocation[j][i] = 0;
			maximum[j][i] = available[i]/(NUMBER_OF_CUSTOMERS/2);
			//printf("%d\n", available[i]);
			need[j][i] = maximum[j][i] - allocation[j][i];
		}
	}
}

int main(int argc, char* argv[])
{

 	pthread_t threads[NUMBER_OF_CUSTOMERS];
	int i = 0;

	if (argc != NUMBER_OF_RESOURCES + 1)
	{
		/* We print argv[0] assuming it is the program name */
        printf( "usage: %s <resource counts>\n", argv[0] );
		return 1;
	}

	for (i = 1; i < argc; i++)
	{
		available[i-1] = atoi(argv[i]);
	}

	init_arrays();
   
	for (i = 0; i < NUMBER_OF_CUSTOMERS; i++)
	{
		customerids[i] = i;
    	pthread_create (&threads[i], NULL, &customer_function, &customerids[i]);
	}

   for (i = 0; i < NUMBER_OF_CUSTOMERS; i++) {
	   pthread_join(threads[i],NULL);
	}

	return 0;
}

int safety_test()
{
	int i, j, k = 0;
    int isSafe = 0;
    int test_available[NUMBER_OF_RESOURCES];
    int finish[NUMBER_OF_CUSTOMERS];

    for (i = 0; i < NUMBER_OF_RESOURCES; i++)
    {
        test_available[i] = available[i];
    }

    for (i = 0; i < NUMBER_OF_CUSTOMERS; i++)
    {
        isSafe = 0;

        for (j = 0; j < NUMBER_OF_RESOURCES; j++)
        {
            if (need[i][j] > test_available[j])
            {
                isSafe = -1;
            }
        }

        if (finish[i] == 0 && isSafe == 0)
        {
            for (k = 0; k < NUMBER_OF_RESOURCES; k++)
            {
                test_available[k] += allocation[i][k];
            }

            finish[i] = 1;
            i = 0;
        }
    }

    for (i = 0; i < NUMBER_OF_CUSTOMERS; i++)
    {
        if (finish[i] == 0)
        {
            isSafe = -1;
            break;
        }
    }
    return isSafe;
}
