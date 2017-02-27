/**
 * General structure of the teaching assistant.
 *
 */

#include <pthread.h>
#include <stdio.h>
#include <time.h>
#include <errno.h>
#include <string.h>
#include "ta.h"

void *ta_loop(void *param)
{

   /* seed random generator */
   srandom((unsigned)time(NULL));

	int sleep_time = 0;

   while (1) {

	sleep_time = (int)((random() % MAX_SLEEP_TIME)+1);

      /* wait for a student to show up */
      if (sem_wait(&sleeping) == -1) {
         printf("%s\n",strerror(errno));
	}
	//printf("hi\n");

      /* acquire the mutex lock */
      if (pthread_mutex_lock(&mutex_lock) != 0) {
          printf("%s\n",strerror(errno));
		}
		
		students_waiting--;

      /* indicate the TA is ready to help a student */
      if (sem_post(&officechair) != 0) {
          printf("%s\n",strerror(errno));
	}

      /* release mutex lock */
      if (pthread_mutex_unlock(&mutex_lock) != 0) {
          printf("%s\n",strerror(errno)); 
	}

      /* helping students random time */

		help_student(sleep_time);

   }
}

