/**
 * test.c
 *
 * Test the implementation of the PID manager.
 *	Template code by Dr. Karlsson.  Implemented by Benjamin Kaiser
 */

#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include "pid.h"

#define NUM_THREADS 100
#define ITERATIONS   10
#define SLEEP         5

int in_use[PID_MAX + 1]; //0 or 1 flag indicating usage although not 100% why needed

/**
 * mutex lock used when accessing data structure
 * to ensure there are no duplicate pid's in use.
 */
pthread_mutex_t test_mutex;

// the function that each thread should run upon creation
void *allocator(void *param)
{
	// creation of the loop variable as well as the process id for this thread.
	int i, pid;

	// each thread has a number of times that it requests a PID and then sleeps.
	for (i = 0; i < ITERATIONS; i++) {
      /* sleep for a random period of time */
		sleep((int)(random() % SLEEP));

		
      /* allocate a pid */
		pid = allocate_pid();
		// if allocate_pid returns -1 we have an error
		if (pid == -1)
		{
			printf("No pid available\n");
		}
		else
		{
   	    	 /* indicate in the in_use map the pid is in use */
			pthread_mutex_lock(&test_mutex);
			in_use[pid] = 1;
			pthread_mutex_unlock(&test_mutex);
			printf("allocated %d\n", pid);	
	
        	 /* sleep for a random period of time */
			sleep((int)(random() % SLEEP));
         
        	 /* release the pid */
			release_pid(pid);
		}
   }
}

// main function
int main(void)
{
   int i;
   pthread_t tids[NUM_THREADS];

	if (pthread_mutex_init(&test_mutex, NULL) != 0)
    {
        printf("\n mutex init failed\n");
        return -1;
    }

		//initialize these to put them to 0 to indicate not in use
   for (i = 0; i <= PID_MAX; i++) {
      in_use[i] = 0;
   }


   /* allocate the pid map */
   if (allocate_map() == -1)
	{
      return -1;
	}

   srandom((unsigned)time(NULL));

	// here begins the race condition posibilities
   /* create the threads */
	for (i = 0; i < NUM_THREADS; i++)
	{
		 pthread_create (&tids[i], NULL, &allocator, NULL);
	}
   /* join the threads */
	for (i = 0; i < NUM_THREADS; i++)
	{
	  pthread_join(tids[i], NULL);
	}
   /* test is finished */
    pthread_mutex_destroy(&test_mutex);
	cleanup();

   return 0;
}
