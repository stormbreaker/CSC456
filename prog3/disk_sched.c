#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include "disk_sched.h"

void generateRequests()
{
    int i = 0;

    srand(time(NULL));

    for (i = 0; i < NUMREQUESTS; i++)
    {
        requests[i] = rand() % CYLINDERS;
    }
}

int main(int argc, char** argv)
{

}
