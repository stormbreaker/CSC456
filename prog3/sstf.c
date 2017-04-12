#include "sstf.h"
#include "disk_sched.h"
#include <stdbool.h>

int sstf(int startHeadPosition)
{
    int i = 0;
    int j = 0;

    int totalDistance = 0;

    int minimumDistance = CYLINDERS;
    int minimumIndex = 0;

    bool done[NUMREQUESTS];

    for (i = 0; i < NUMREQUESTS; i++)
    {
        done[i] = false;
    }

    for (i = 0; i < NUMREQUESTS; i++)
    {
        if (abs(startHeadPosition - requests[i]) < minimumDistance)
        {
            minimumDistance = abs(startHeadPosition - requests[i]);
            minimumIndex = i;
        }
    }

    done[minimumIndex] = true;

    for (i = 0; i < NUMREQUESTS; i++)
    {
        for (j = 0; j < NUMREQUESTS; j++)
        {
             if (abs(requests[i] - requests[j]) && done[j] == false)
             {
                 minimumDistance = abs(
             }
        }
    }

    return totalDistance;
}
