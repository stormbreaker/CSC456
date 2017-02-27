 /**
 * A solution to the pid manager problem. 
 *
 */

#include "pid.h"
#include <pthread.h>
#include <stdio.h>



// Allocates the pid map.
int allocate_map(void) 
{
	if (pthread_mutex_init(&mutex, NULL) != 0)
    {
        printf("\nmutex init failed\n");
        return -1;
    }
	int i;
	for (i = 0; i <= PID_MAX; i++)
	{
		pid_map[i] = 0;
	}

   return 0; //return last;
}

// Allocates a pid
int allocate_pid(void)
{
   /* local variables */
	int allocatedPID = 0;\
	int i;

   /* acquire the mutex lock and warn if unable */
	if (pthread_mutex_lock(&mutex) != 0)
	{
		printf("unable to accuire lock\n");
	}
   /* find the next available pid */
	i = PID_MIN;
	do
	{
		//printf("%d\n", i);
		i++;
	} while ((pid_map[i] == 1) && i < PID_MAX + 1);
	

	pid_map[i] = 1;
	allocatedPID = i;

   /* release and warn if the mutex was not released */
	if (pthread_mutex_unlock(&mutex) != 0)
	{
		printf("unable to release lock\n");
	}
	if (i == PID_MAX + 1)
	{
		return -1;
	}

   return allocatedPID; // return last;
}

// Releases a pid
void release_pid(int pid)
{
   /* acquire the mutex lock and warn if unable */
	if (pthread_mutex_lock(&mutex) != 0)
	{
		printf("unable to accquire lock\n");
		return;
	}

	if (pid_map[pid] == 0)
	{
		printf("PID was not already in use\n");
	}
	pid_map[pid] = 0;

   /* release and warn if the mutex was not released  */
	if (pthread_mutex_unlock(&mutex) != 0)
	{
		printf("failed to release mutex\n");
		return;
	}


	printf("released %d\n", pid);

}
void cleanup()
{
    pthread_mutex_destroy(&mutex);
}


