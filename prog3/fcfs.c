#include "disk_sched.h"
#include "fcfs.h"


int fcfs(int headStartPosition)
{
    int totalDistance = 0;

    int i = 0;

    totalDistance = abs(requests[0] - headStartPosition);

    for (int i = 1; i < NUMREQUESTS; i++)
    {
        totalDistance += abs(requests[i-1] - requests[i]);
    }

    return totalDistance;
}
