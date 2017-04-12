#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include "disk_sched.h"
#include "fcfs.h"

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
    int distance;
    int startHead;

    if (argc < 2)
    {
        printf("Usage: disk_sched <head starting position>\n");
        return -1;
    }

    startHead = atoi(argv[1]);

    generateRequests();

    distance = fcfs(startHead);

    return 0;
}
