/*
	Author: Benjamin Kaiser
	Description:  This file contains the actual definition of
	the circular scan algorithm.
*/
#include "cscan.h"
#include "disk_sched.h"
#include <stdbool.h>

/*
    Author: Benjamin Kaiser
    Description:  This function implements the circular scan
    scheduling algorithm.  It takes a head starting position for an
    input.  After that it moves one position to the right and scans up to the
    end of the disk.  When it hits this it goes over the end of the disk
    and continues until all requests have been processed.
*/
int cscan(int startHeadPosition)
{
    int i = 0;

    int totalDistance = 0;
    int doneCount = 0;
    int currentPosition = startHeadPosition;

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
