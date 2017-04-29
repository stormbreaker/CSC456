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
    Description:  This function implements the circular look
    scheduling algorithm.  It takes a head starting position for an
    input.  After that it moves one position to the right and processes
    requests along the way.  If it hits the max request or the edge of the cylinder,
    it goes up (or down) to the minimum value and begins going up again
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

    // initialize done and find min and max
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

    // process requests
    while (doneCount < NUMREQUESTS)
    {
        // look for requests at this position
        for (i = 0; i < NUMREQUESTS; i++)
        {
            // found a request
            if (requests[i] == currentPosition && done[i] == false)
            {
                done[i] = true;
                doneCount++;
            }
        }
        currentPosition += 1;
        totalDistance += 1;
        // we hit the one end and need to go back
        // assume this is a reset and not actually part of the seek count
        if (currentPosition > max || currentPosition > CYLINDERS)
        {
            // uncomment this code to count the reset as part of seek time
            /*
            int tempDist = max - min;
            if (max - min > (CYLINDERS - currentPosition + min))
            {
                totalDistance += (CYLINDERS - currentPosition + min);
            }
            else
            {
                totalDistance += max - min;
            }
            */
            currentPosition = min;
        }

    }

    return totalDistance;
}
