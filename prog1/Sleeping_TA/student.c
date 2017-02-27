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

		//unlock

        if (sem_post(&sleeping) != 0){ //wake TA (post)
             printf("StudentC %s\n",strerror(errno));
		}

	     pthread_mutex_unlock(&mutex_lock);

         if (sem_wait(&officechair) != 0) {
             printf("StudentB %s\n",strerror(errno));
		}

         printf("Student %d receiving help\n", param);

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

