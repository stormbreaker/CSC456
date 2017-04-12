#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

const int NUMREQUESTS = 1000;

int requests[NUMREQUESTS];
const int CYLINDERS = 5000;

int fcfcs();
int sstf();
int scan();
int cscan();
int look();
int clook();
void generateRequests(); 
