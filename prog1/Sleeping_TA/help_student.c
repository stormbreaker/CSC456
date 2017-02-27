/**
 * Simulate helping a student
 */

#include <stdio.h>
#include "ta.h"

void help_student(int sleep_time)
{
   printf("Helping a student for %d seconds waiting students = %d\n", sleep_time , students_waiting);
   sleep(sleep_time);
	//kick the student out
    sem_post(&freetogo);
}
