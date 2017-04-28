#include "clook.h"
#include "disk_sched.h"
#include <stdbool.h>

int clook(int startHeadPosition)
{
    int i = 0;
    int j = 0;

    int totalDistance = 0;
    int doneCount = 0;
    int currentPosition = startHeadPosition;
    int minimumDistance = CYLINDERS;
    int minimumIndex = 0;

    int directionMovement = -1;

    bool done[NUMREQUESTS];

    int min = CYLINDERS;
    int max = 0;

    for (i = 0; i < NUMREQUESTS; i++)
    {
        done[i] = false;
        if (requests[i] > max)
        {
            max = requests[i];
        }
        if (requests[i] < min)
        {
            min = requests[i];
        }
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
        if (currentPosition > max)
        {
            totalDistance += CYLINDERS - currentPosition;
            currentPosition = 0;
        }

    }

    return totalDistance;
}
