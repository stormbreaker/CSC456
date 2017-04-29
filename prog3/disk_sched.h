/*
	Author:  Benjamin Kaiser
	Description:  This file contains all of the interface
	information for the main portion of the program
	The NUMREQUESTS macro is defined here as well
	as the proper globals declared and the generateRequests()
	function prototype is declared here.
*/
#ifndef BTK_DISK_SCHED
#define BTK_DISK_SCHED

#include <stdlib.h>
#include <stdio.h>

#define NUMREQUESTS 1000

// requests list
int requests[NUMREQUESTS];
int CYLINDERS;

void generateRequests();

#endif
