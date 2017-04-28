#include "sstf.h"
#include "disk_sched.h"
#include <stdbool.h>

int sstf(int startHeadPosition)
{
    int i = 0;
    int j = 0;

    int totalDistance = 0;
    int doneCount = 0;
    int currentPosition = startHeadPosition;
    int minimumDistance = CYLINDERS;
    int minimumIndex = 0;

    bool done[NUMREQUESTS];

    for (i = 0; i < NUMREQUESTS; i++)
    {
        done[i] = false;
    }

    while (doneCount < NUMREQUESTS)
    {
        for (i = 0; i < NUMREQUESTS; i++)
        {
            if (abs(currentPosition - requests[i]) < minimumDistance && !done[i])
            {
                minimumDistance = abs(currentPosition - requests[i]);
                minimumIndex = i;
            }
        }
        done[minimumIndex] = true;
        totalDistance += minimumDistance;
        currentPosition = requests[minimumIndex];
        minimumDistance = CYLINDERS;
        doneCount++;
    }

    return totalDistance;
}
