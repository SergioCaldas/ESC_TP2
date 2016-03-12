#include <stdio.h>
#include <stdlib.h>
#include <pthread.h> 
#include "timer.h"
#include <math.h>

const int MAX_THREADS = 4;

/* Global variable:  accessible to all threads */
int thread_count;  
double start, stop, elapsed;
void Usage(char* prog_name);
void *Hello(void* rank);/* Thread function */

/*-------------------------------------------------------------------*/
void *Hello(void* rank) {
  return NULL;
}  /* Hello */

/*-------------------------------------------------------------------*/
void Usage(char* prog_name) {
  fprintf(stderr, "usage: %s <number of threads>\n", prog_name);
  fprintf(stderr, "0 < number of threads <= %d\n", MAX_THREADS);
  exit(0);
}  /* Usage */

/*--------------------------------------------------------------------*/
int main(int argc, char* argv[]) {
  long       thread;  /* Use long in case of a 64-bit system */
  pthread_t* thread_handles; 
  
  /* Get number of threads from command line */
  if (argc != 2) Usage(argv[0]);
  thread_count = strtol(argv[1], NULL, 10);  
  if (thread_count <= 0 || thread_count > MAX_THREADS) Usage(argv[0]);

  thread_handles = malloc (thread_count*sizeof(pthread_t)); 

  GET_TIME(start);
  for (thread = 0; thread < thread_count; thread++)
    pthread_create(&thread_handles[thread], NULL,Hello, (void*) thread);  

  for (thread = 0; thread < thread_count; thread++)
    pthread_join(thread_handles[thread], NULL);
  
  GET_TIME(stop);
  elapsed = stop-start;
  printf("%d,%f,%f\n",thread_count,(float)((elapsed/thread_count)*pow(10,3)),elapsed*pow(10,3));
  
  free(thread_handles);
  return 0;
}  /* main */

