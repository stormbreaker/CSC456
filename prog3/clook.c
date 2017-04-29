/*
	Author: Benjamin Kaiser
	Description:  This file contains the actual definition of
	the circular look algorithm.
*/
#include "clook.h"
#include "disk_sched.h"
#include <stdbool.h>
/*
	Author: Benjamin Kaiser
	Description:  
*/
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
        if (currentPosition > max || currentPosition > CYLINDERS)
        {
            totalDistance += CYLINDERS - currentPosition;
            currentPosition = min;
        }

    }

    return totalDistance;
}
