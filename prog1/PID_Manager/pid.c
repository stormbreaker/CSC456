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
        printf("\n mutex init failed\n");
        return 1;
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
	} while (pid_map[i] == 1);
	pid_map[i] = 1;
	allocatedPID = i;

   /* release and warn if the mutex was not released */
	if (pthread_mutex_unlock(&mutex) != 0)
	{
		printf("unable to release lock\n");
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


   /* release and warn if the mutex was not released  */
	if (pthread_mutex_unlock(&mutex) != 0)
	{
		printf("failed to release mutex\n");
		return;
	}

	pid_map[pid]  = 0;
	printf("released %d\n", pid);

}
void cleanup()
{
    pthread_mutex_destroy(&mutex);
}


