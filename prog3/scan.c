/*
	Author: Benjamin Kaiser
	Description:  This file contains the actual definition of
	the scan algorithm.
*/
#include "scan.h"
#include "disk_sched.h"
#include <stdbool.h>

/*
	Author: Benjamin Kaiser
	Description:  
*/
int scan(int startHeadPosition)
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

    for (i = 0; i < NUMREQUESTS; i++)
    {
        done[i] = false;
    }

    while (doneCount < NUMREQUESTS)
    {
        if (currentPosition == 0)
        {
            directionMovement = 1;
        }
        else if (currentPosition == CYLINDERS - 1)
        {
            directionMovement = -1;
        }

        for (i = 0; i < NUMREQUESTS; i++)
        {
            if (requests[i] == currentPosition && done[i] == false)
            {
                done[i] = true;
                doneCount++;
            }
        }
        currentPosition += directionMovement;
        totalDistance += 1;
    }
    return totalDistance;
}
