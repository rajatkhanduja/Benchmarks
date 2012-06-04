/* Program to compare the performance difference between an array and a 
 * vector. To make the competition fair, the vector is initialized as the 
 * same size as the array and the size is never changed. Also, the comparison
 * is made between an array initialized at runtime, dynamically.
 *
 * The idea is to compare access times for array and vectors, using both 
 * indices and iterators for vectors.
 * 
 * Arrays and vectors of only 'int' is created and tested. It is assumed that
 * it shouldn't make much difference in judging the performance in general.
 * Also, both vector and array are compared for sequential access and not
 * random access.
 *
 * OBSERVATIONS :-
 *  - Using indices, writing to vectors is faster than to arrays.
 *  - It is faster to read from arrays than from vectors.
 *  - Reading/writing using iterators in vectors is far slower than using indices.
 *
 * Times taken for ARR_SIZE = 1m (1000000) on Linux i386 (32bit Machine) 3GB RAM:-
 *
 *  Time taken to write to array. : 33.273 ms
 *  Time taken to read from array. : 3.855 ms
 *  Time taken to write to vector using indices. : 26.007 ms
 *  Time taken to read from vector using indices. : 5.633 ms
 *  Time taken to write to vector using iterators. : 43.448 ms
 *  Time taken to read from vector using iterators. : 21.938 ms
 *
 * Times taken for ARR_SIZE = 1m (1000000) on Linux i686 (64bit Machine) 7.7GB RAM:-
 *
 *  Time taken to write to array. : 21.1658 ms
 *  Time taken to read from array. : 2.84009 ms
 *  Time taken to write to dynamic array. : 14.967 ms
 *  Time taken to read from dynamic array. : 3.09204 ms
 *  Time taken to write to vector using indices. : 13.8569 ms
 *  Time taken to read from vector using indices. : 4.94507 ms
 *  Time taken to write to vector using iterators. : 32.8459 ms
 *  Time taken to read from vector using iterators. : 20.8821 ms
 */
 
#include <vector>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <sys/time.h>
#include <cassert>

#define ARR_SIZE 1000000

using std::string;

void printtime (struct timeval& start, struct timeval& end, string str)
{
  double start_time, end_time, diff;
  
  start_time = ((start.tv_sec) * 1000 + start.tv_usec/1000.0);
  end_time   = ((end.tv_sec) * 1000 + end.tv_usec/1000.0);
  diff = end_time - start_time;

  std::cout << str << " : " << diff << " ms" << std::endl;
}


int main (void)
{
  int arr[ARR_SIZE];
  int tmp;
  struct timeval start, stop;
 
  srand (time (NULL));

  /* Writing data to array */
  gettimeofday (&start, NULL);
  for (int i = 0; i < ARR_SIZE; i++)
  {
    arr[i] = rand();
  }
  gettimeofday (&stop, NULL);
  printtime (start, stop, string ("Time taken to write to array."));

  /* Reading data from array */
  gettimeofday (&start, NULL);
  for (int i = 0; i < ARR_SIZE; i++)
  {
    tmp = arr[i];
  }
  gettimeofday (&stop, NULL);
  printtime (start, stop, string ("Time taken to read from array."));

  int *darr = (int *) calloc (sizeof (int), ARR_SIZE);  

  /* Writing data to array */
  gettimeofday (&start, NULL);
  for (int i = 0; i < ARR_SIZE; i++)
  {
    darr[i] = rand();
  }
  gettimeofday (&stop, NULL);
  printtime (start, stop, string ("Time taken to write to dynamic array."));

  /* Reading data from array */
  gettimeofday (&start, NULL);
  for (int i = 0; i < ARR_SIZE; i++)
  {
    tmp = darr[i];
  }
  gettimeofday (&stop, NULL);
  printtime (start, stop, string ("Time taken to read from dynamic array."));


  std::vector<int> v(ARR_SIZE);
  
  /* Writing to vector using indices*/
  gettimeofday (&start, NULL);
  for (int i = 0; i < ARR_SIZE; i++)
  {
    v[i] = rand();
  }
  gettimeofday (&stop, NULL);
  printtime (start, stop, string ("Time taken to write to vector using indices."));
  assert (v.capacity() == ARR_SIZE);

  /* Reading from vector using indices*/
  gettimeofday (&start, NULL);
  for (int i = 0; i < ARR_SIZE; i++)
  {
    tmp = v[i];
  }
  gettimeofday (&stop, NULL);
  printtime (start, stop, string ("Time taken to read from vector using indices."));

  std::vector<int> v2(ARR_SIZE);
  
  /* Writing to vector using iterators*/
  gettimeofday (&start, NULL);
  std::vector<int>::iterator itr, itr_end;
  for (itr = v2.begin(), itr_end = v2.end(); itr != itr_end; itr++)
  {
    *itr = rand();
  }
  gettimeofday (&stop, NULL);
  printtime (start, stop, string ("Time taken to write to vector using iterators."));


  /* Reading from vector using iterators*/
  gettimeofday (&start, NULL);
  for (itr = v2.begin(), itr_end = v2.end(); itr != itr_end; itr++)
  {
    tmp = *itr;
  }
  gettimeofday (&stop, NULL);
  printtime (start, stop, string ("Time taken to read from vector using iterators."));

  return 0;
}
