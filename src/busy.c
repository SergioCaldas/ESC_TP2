#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "trapezoide.h"
#include "timer.h"
#include <semaphore.h>
#include <math.h>

const int MAX_THREADS = 64;

/* Global variable:  accessible to all threads */
int thread_count;
double start, stop, elapsed;
double total;
int n, local_n;
double a, b, h;

void* trap_busy(void* rank);

/*-------------------------------------------------------------------*/
void Usage(char* prog_name) {

  fprintf(stderr, "usage: %s <number of threads>\n", prog_name);
  fprintf(stderr, "0 < number of threads <= %d\n", MAX_THREADS);
  exit(0);

}


/*--------------------------------------------------------------------*/
int main(int argc, char* argv[]) {
  
  long thread;  /* Use long in case of a 64-bit system */
  pthread_t* thread_handles;
  char* prog_name = argv[0];
  total = 0.0;

  if (argc < 5) Usage(prog_name);
  thread_count = strtol(argv[1], NULL, 10);
  if (thread_count <= 0 || thread_count > MAX_THREADS) Usage(prog_name);
  
  a = strtol(argv[2], NULL, 10);
  b = strtol(argv[3], NULL, 10);
  n = strtol(argv[4], NULL, 10);
  h = (b-a)/n;
  local_n = n/thread_count;
  
  thread_handles = malloc (thread_count*sizeof(pthread_t));

  GET_TIME(start);
  for (thread = 0; thread < thread_count; thread++){
    pthread_create(&thread_handles[thread], NULL, trap_busy , (void*) thread);
  }

  for (thread = 0; thread < thread_count; thread++){
    pthread_join(thread_handles[thread], NULL);
  }
  GET_TIME(stop);
  elapsed = stop - start;
  printf("%s,%ld,%.2f,%.2f,%d,%.2f,%.2f\n",prog_name,thread,a,b,n,elapsed,total);
  
  free(thread_handles);
  return 0;
}

