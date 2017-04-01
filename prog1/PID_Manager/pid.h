/*
* Template code by Dr. Karlsson.  Implemented by Benjamin Kaiser
*/
#include <pthread.h>

#define PID_MIN  	300
#define PID_MAX 	500

/* mutex lock for accessing pid_map */
pthread_mutex_t mutex;

// actual map of the process ids in and out of use
int pid_map[PID_MAX+1];

int last;	// last pid in use - NEVER UTILIZED
