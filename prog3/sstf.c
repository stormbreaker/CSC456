/*
	Author: Benjamin Kaiser
	Description:  This file contains the actual definition of
	the shortest seek time first algorithm.
*/
#include "sstf.h"
#include "disk_sched.h"
#include <stdbool.h>

/*
	Author: Benjamin Kaiser
	Description:  This function is the implementation of
	the shortest seek time first algorithm.  It takes
	a starting head position in the disk.  It then 
	initializes the array used to check and see if a
	request has already been processed.  After that
	It goes through and begins processing requests.
	It takes the current disk head postion
	and adds the minimum distance to it and then moves
	the disk head to the proper position.  
*/
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

	// initialize the done check array
    for (i = 0; i < NUMREQUESTS; i++)
    {
        done[i] = false;
    }

	// process all requests
    while (doneCount < NUMREQUESTS)
    {
		// find our minimum distance
        for (i = 0; i < NUMREQUESTS; i++)
        {
			// set new minimum distance and index
            if (abs(currentPosition - requests[i]) < minimumDistance && !done[i])
            {
                minimumDistance = abs(currentPosition - requests[i]);
                minimumIndex = i;
            }
        }
		// set to processed
        done[minimumIndex] = true;
        totalDistance += minimumDistance;
		// move disk head
        currentPosition = requests[minimumIndex];
		// reset minimum distance
        minimumDistance = CYLINDERS;
        doneCount++;
    }

    return totalDistance;
}
