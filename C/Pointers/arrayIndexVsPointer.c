/* Program to test the time difference between the two variations of the same statement
 *    *(ptr + i) 
 *    ptr[i]
 *
 * The idea is to test by declaring pointers and arrays separately and testing the performance of 
 * the statements in each case.
 *
 * Tested on Input size : 2E6 = (2 * 10^6)
 *
 * Observations :-
 *    On an array *(arr + i) is faster than arr[i]
 *    This is true even for pointers (dynamic memory).
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <sys/time.h>

#define INPUT_SIZE 1000000 * 2

int main (void)
{
   struct timeval start[4], end[4];
   double start_time, end_time, diff;
   int arr[INPUT_SIZE], t;
   int *ptr = (int*) malloc ( sizeof (int) * INPUT_SIZE);

   assert (ptr);

   unsigned int i;

   srand(time(NULL));

   /* Using arr[index] method on a variable defined as array */
   gettimeofday (&start[0], NULL);   
   for ( i = 0; i < INPUT_SIZE; i++)
   {
      // Writing to memory
      arr[i] = rand();
   }

   for ( i = 0; i < INPUT_SIZE; i++)
   {
      // Reading from memory
      t = arr[i];
   }
   gettimeofday (&end[0], NULL);
   /* --- */

   /* Using *(arr + i) method on a variable defined as array */
   gettimeofday (&start[1], NULL);   
   for ( i = 0; i < INPUT_SIZE; i++)
   {
      // Writing to memory
      *(arr + i) = rand();
   }

   for ( i = 0; i < INPUT_SIZE; i++)
   {
      // Reading from memory
      t = *(arr + i);
   }

   gettimeofday (&end[1], NULL);   
   /* --- */

   /* Using ptr[index] method on a variable defined as pointer (dynamic memory) */
   gettimeofday (&start[2], NULL);   
   for ( i = 0; i < INPUT_SIZE; i++)
   {
      // Writing to memory
      ptr[i] = rand();
   }

   for ( i = 0; i < INPUT_SIZE; i++)
   {
      // Reading from memory
      t = ptr[i];
   }

   gettimeofday (&end[2], NULL);   
   /* --- */

   /* Using *(ptr + i) method on a variable defined as pointer (dynamic memory) */
   gettimeofday (&start[3], NULL);   
   for ( i = 0; i < INPUT_SIZE; i++)
   {
      // Writing to memory
      *(ptr + i) = rand();
   }

   for ( i = 0; i < INPUT_SIZE; i++)
   {
      // Reading from memory
      t = *(ptr + i);
   }

   gettimeofday (&end[3], NULL);   
   /* --- */

   /* Print the times taken */
   for (i = 0; i < 4; i++)
   {
      start_time = ((start[i].tv_sec) * 1000 + start[i].tv_usec/1000.0);
      end_time   = ((end[i].tv_sec) * 1000 + end[i].tv_usec/1000.0);
      diff = end_time - start_time;

      /* Print the total time taken for each operation (READ + WRITE) */
      printf ("%g\t", diff);
   }
   printf ("\n");

   return 0;
}
