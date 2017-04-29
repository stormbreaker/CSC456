/*
	Author: Benjamin Kaiser
	Class:  CSC 456 - Operating Systems
	Professor: Dr. Christer Karlsson

	Description:  This file contains all of the implementation for
	the main part of the disk scheduling program.  This includes
	the function which generates the requests to access the disk head
	and the main function.  
*/

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include "disk_sched.h"
#include "fcfs.h"
#include "sstf.h"
#include "scan.h"
#include "cscan.h"
#include "look.h"
#include "clook.h"

// initialize the constant number of cylinders
int CYLINDERS = 5000;

/*
	Author: Benjamin Kaiser
	Description:  This function just generates the list of requests
	for access on the disk.  It does this by looping through as many
	times as assigned to the NUMREQUESTS macro and each time generates a number
	between 0 and the number of CYLINDERS there are (base program has 5000 cylinders)
	This random value is then assigned to the requests array.  
*/
void generateRequests()
{
    int i = 0;

    srand(time(NULL));

    for (i = 0; i < NUMREQUESTS; i++)
    {
        requests[i] = rand() % CYLINDERS;
    }
}

/*
	Author: Benjamin Kaiser
	Description:  This is the main function for the program.
	It takes a count of how many command line arguments
	were passed and an array of what those arguments were.
	There are a few error checks.  If the number
	of arguments is not exactly 2 (executable and it's input)
	then a usage statement is printed and the program exits.
	If the input is invalid, then an error is printed and
	the program returns.  After this, if everything is
	OK, then each algorithm is called that has been 
	implemented in it's own function.  The value from these
	functions are set to the distance variable and this is then
	printed out along with the algorithm that created that number.
*/
int main(int argc, char** argv)
{
    int distance;
    int startHead;

	// error check proper usage
    if (argc < 2)
    {
        printf("Usage: disk_sched <head starting position>\n");
        return -1;
    }

    startHead = atoi(argv[1]);

	// error check proper input
    if (startHead < 0 || startHead > CYLINDERS)
    {
        printf("Invalid Starting Head please enter a value between %d and %d\n", 0, CYLINDERS);
        return -1;
    }

    generateRequests();

	// call algorithms and print results
    distance = fcfs(startHead);

    printf("FCFS: %d\n", distance);

    distance = sstf(startHead);

    printf("SSTF: %d\n", distance);

    distance = scan(startHead);

    printf("SCAN: %d\n", distance);

    distance = cscan(startHead);

    printf("CSCAN: %d\n", distance);

    distance = look(startHead);

    printf("LOOK: %d\n", distance);

    distance = clook(startHead);

    printf("CLOOK: %d\n", distance);

    return 0;
}
