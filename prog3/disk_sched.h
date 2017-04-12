#ifndef BTK_DISK_SCHED
#define BTK_DISK_SCHED

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#define NUMREQUESTS 1000

int requests[NUMREQUESTS];
int CYLINDERS;

int scan();
int cscan();
int look();
int clook();
void generateRequests(); 

#endif
