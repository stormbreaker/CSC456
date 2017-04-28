#include "cscan.h"
#include "disk_sched.h"
#include <stdbool.h>

int cscan(int startHeadPosition)
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
            if (requests[i] == currentPosition && done[i] == false)
            {
                done[i] = true;
                doneCount++;
            }
        }
        currentPosition += 1;
        totalDistance += 1;
        if (currentPosition > CYLINDERS)
        {
            //assuming we just go from 5000 to 0 since they're technically right
            // next to each other in a circle
            //totalDistance += CYLINDERS;
            currentPosition = 0;
        }
    }

    return totalDistance;
}
