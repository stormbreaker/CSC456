/**
 * General structure of a student.
 *
 */

#include <pthread.h>
#include <stdio.h>
#include <time.h>
#include <errno.h>
#include <string.h>
#include "ta.h"

void *student_loop(void *param)
{
   /* varaibles */
	int times_through_loop = 0;
	int sleep_time = 0;

   srandom((unsigned)time(NULL));

	// loop through many times the student tries to get help
   while (times_through_loop < 5) {

	sleep_time = (int)((random() % MAX_SLEEP_TIME)+1);
	
	hang_out(param, sleep_time);

      /* acquire the mutex lock */
      if (pthread_mutex_lock(&mutex_lock) != 0) {
         printf("StudentA %s\n",strerror(errno));
		}

      /* is there a seat available */
      if (students_waiting < NUM_OF_SEATS) {

		students_waiting++;
         printf("\t\tStudent %d takes a seat waiting = %d\n", param, students_waiting);

		//tells the TA to wake his butt up		
        if (sem_post(&sleeping) != 0){ 
             printf("StudentC %s\n",strerror(errno));
		}

	     pthread_mutex_unlock(&mutex_lock);
		// waits for the TA to get the room ready
         if (sem_wait(&officechair) != 0) {
             printf("StudentB %s\n",strerror(errno));
		}

         printf("Student %d receiving help\n", param);
		// waits until the TA tells the student he can leave.  
		if (sem_wait(&freetogo) !=0) {
			printf("something in freetogo broke");
		}
			
       } 
       else {
          printf("\t\t\tStudent %d will try later\n", param);
          pthread_mutex_unlock(&mutex_lock);
       }
		times_through_loop++;
   }
}

