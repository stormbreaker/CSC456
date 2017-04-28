#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include "disk_sched.h"
#include "fcfs.h"
#include "sstf.h"
#include "scan.h"
#include "cscan.h"
#include "look.h"
#include "clook.h"

int CYLINDERS = 5000;

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

    if (startHead < 0 || startHead > CYLINDERS)
    {
        printf("Invalid Starting Head please enter a value between %d and %d\n", 0, CYLINDERS);
        return -1;
    }

    generateRequests();

    distance = fcfs(startHead);

    printf("FCFS: %d\n", distance);

    distance = sstf(startHead);

    printf("SSTF: %d\n", distance);

    distance = scan(startHead);

    printf("SCAN: %d\n", distance);

    distance = cscan(startHead);

    printf("CSCAN: %d\n", distance);

    distance = look(startHead);

    printf("LOOK: %d\n", distance);

    distance = clook(startHead);

    printf("CLOOK: %d\n", distance);

    return 0;
}
