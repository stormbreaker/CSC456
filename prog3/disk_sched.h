#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

int requests[1000];
const int CYLINDERS = 5000;

int fcfcs();
int sstf();
int scan();
int cscan();
int look();
int clook();
void generateRequests(); 
