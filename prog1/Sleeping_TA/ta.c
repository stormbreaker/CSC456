/**
 * General structure of the teaching assistant.
 *
 */

#include <pthread.h>
#include <stdio.h>
#include <time.h>
#include <errno.h>
#include <string.h>
#include "ta.h"

void *ta_loop(void *param)
{

   /* seed random generator */
   srandom((unsigned)time(NULL));

   while (1) {

      /* wait for a student to show up */
      if ( )
         printf("%s\n",strerror(errno));

      /* acquire the mutex lock */
      if ( )
          printf("%s\n",strerror(errno));

      /* indicate the TA is ready to help a student */
      if ( )
          printf("%s\n",strerror(errno));

      /* release mutex lock */
      if ( )
          printf("%s\n",strerror(errno));

      /* helping students random time */

   }
}

