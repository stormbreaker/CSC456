/**
 * Simulate a student hanging out
 */

#include <stdio.h>
// sets up the student as hanging out
void hang_out(int lnumber, int sleep_time) 
{
   printf("\tStudent %d hanging out for %d seconds\n", lnumber, sleep_time);
   sleep(sleep_time);
}
