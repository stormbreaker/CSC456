 /**
 * A solution to the pid manager problem. 
 *	Template code by Dr. Karlsson.  Modified by Benjamin Kaiser
 */

#include "pid.h"
#include <pthread.h>
#include <stdio.h>



// Allocates the pid map.
int allocate_map(void) 
{
	// initialize the primary mutex
	if (pthread_mutex_init(&mutex, NULL) != 0)
    {
        printf("\nmutex init failed\n");
        return -1;
    }

	//loop variable
	int i;
	// set all PIDs to unused to begin	
	for (i = 0; i <= PID_MAX; i++)
	{
		pid_map[i] = 0;
	}

   return 0; // succesfully allocated
}

// Allocates a pid
int allocate_pid(void)
{
   /* local variables */
	int allocatedPID = 0; // the pid that I'm allocating
	int i; //loop variable

   /* acquire the mutex lock and warn if unable */
	if (pthread_mutex_lock(&mutex) != 0)
	{
		printf("unable to accuire lock\n");
	}
   /* find the next available pid */
	i = PID_MIN; // start at the bottom and then work your way up searching through the PID list every single time.
	do
	{
		i++;
	} while ((pid_map[i] == 1) && i < PID_MAX + 1);
	
	//set the allocated pid to in use
	pid_map[i] = 1;
	// set the id to the value which we return from this function
	allocatedPID = i;

   /* release and warn if the mutex was not released */
	if (pthread_mutex_unlock(&mutex) != 0)
	{
		printf("unable to release lock\n");
	}
	//whoops we over stepped the array which means there were no available PIDs so return a failure
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
	//a check in case the user of our function is an idiot and doesn't ensure that we pass in a PID that
	// was actually allocated
	if (pid_map[pid] == 0)
	{
		printf("PID was not already in use\n");
	}
	// set the PID to out of use.  We can do this no matter what.
	pid_map[pid] = 0;

   /* release and warn if the mutex was not released  */
	if (pthread_mutex_unlock(&mutex) != 0)
	{
		printf("failed to release mutex\n");
		return;
	}

	printf("released %d\n", pid);

}

//this function destroys the main mutex.  I didn't do a check on it because honestly the program will
// end right after this function is called.  
void cleanup()
{
    pthread_mutex_destroy(&mutex);
}


