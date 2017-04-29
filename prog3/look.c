/*
	Author: Benjamin Kaiser
	Description:  This file contains the actual definition of
	the look algorithm.
*/
#include "look.h"
#include "disk_sched.h"
#include <stdbool.h>

/*
	Author: Benjamin Kaiser
	Description:  This function implements the
	look disk scheduling algorithm.  It takes
	a starting disk head position as input and
	proceeds from there.  It initializes
	the array which indicates if something is
	done or not.  At the same time, it finds the min
	and max of the requests and sets those.  
	After that it processes the requests as it moves
	up and down and looks to see if there are any requests
	at the current position.  
*/
int look(int startHeadPosition)
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

	// initialize the done array and the min and maxes
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
		// set direction of movement
        if (currentPosition < min)
        {
            directionMovement = 1;
        }
        else if (currentPosition > max)
        {
            directionMovement = -1;
        }

		// look to see if there are any requests for our current position
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
