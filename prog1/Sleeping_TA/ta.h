/**
 * Header file for sleeping TA
 */

#include <pthread.h>
#include <semaphore.h>

/* the maximum time (in seconds) to sleep */
#define MAX_SLEEP_TIME         5

/* number of maximum waiting students */
#define MAX_WAITING_STUDENTS   3

/* number of potential students */
#define NUM_OF_STUDENTS        5

/* number of available seats */
#define NUM_OF_SEATS           3

/* semaphores and mutex lock */
pthread_mutex_t mutex_lock;

/* semaphore declarations */
sem_t sleeping;
sem_t officechair;
sem_t freetogo;

/* the number of waiting students */
int students_waiting;

/* student being served */
int serving_student;

/* the numeric id of each student */
int student_id[NUM_OF_STUDENTS];

/* student function prototype */
void *student_loop(void *param);

/* ta function prototype */
void *ta_loop(void *param);

