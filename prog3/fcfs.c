/*
	Author: Benjamin Kaiser
	Description:  This file contains the actual definition of
	the first come first serve algorithm.
*/
#include "fcfs.h"
#include "disk_sched.h"

/*
	Author: Benjamin Kaiser
	Description:  This function implements the first come first serve
	scheduling algorithm.  It takes a head starting position for an
	input.  It then takes the distance from the starting position and
	the first request.  After that, it loops through all the requests
	and sums the distance between two adjacent requests.  
	The total distance is returned.  
*/
int fcfs(int headStartPosition)
{
    int totalDistance = 0;

    int i = 0;

    totalDistance = abs(requests[0] - headStartPosition);

    for (i = 1; i < NUMREQUESTS; i++)
    {
        totalDistance += abs(requests[i-1] - requests[i]);
    }

    return totalDistance;
}
