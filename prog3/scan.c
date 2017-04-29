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
    Description:  This function implements the scan
    scheduling algorithm.  It takes a head starting position for an
    input.  After that it moves one position to the left and scans down to the
    start of the disk.  When it hits this, it scans back up.
*/
int scan(int startHeadPosition)
{
    int i = 0;

    int totalDistance = 0;
    int doneCount = 0;
    int currentPosition = startHeadPosition;

    int directionMovement = -1;

    bool done[NUMREQUESTS];

    // initialize done
    for (i = 0; i < NUMREQUESTS; i++)
    {
        done[i] = false;
    }

    // process requests
    while (doneCount < NUMREQUESTS)
    {
        // hit the start of disk
        if (currentPosition == 0)
        {
            directionMovement = 1;
        }
        //hit end of disk
        else if (currentPosition == CYLINDERS - 1)
        {
            directionMovement = -1;
        }

        // see if is request at this location
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
