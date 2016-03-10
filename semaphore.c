#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "trapezoide.h"
#include "timer.h"
#include <semaphore.h>

const int MAX_THREADS = 4;

/* Global variable:  accessible to all threads */
int thread_count;
double start, stop, elapsed;
double total;
int n, local_n;
double a, b, h;

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
  double tempos[thread_count];

  thread_count = strtol(argv[1], NULL, 10);
  a = 1;
  b = 100;
  n = 40;
  h = (b-a)/n;
  local_n = n/thread_count;

  if (thread_count <= 0 || thread_count > MAX_THREADS) Usage(argv[0]);
  
  thread_handles = malloc (thread_count*sizeof(pthread_t));

  GET_TIME(start);
  for (thread = 0; thread < thread_count; thread++){
    tempos[thread]=start;
    pthread_create(&thread_handles[thread], NULL, trap_sem , (void*) thread);
  }

  for (thread = 0; thread < thread_count; thread++){
    pthread_join(thread_handles[thread], NULL);
  }
  GET_TIME(stop);
  elapsed = stop - tempos[thread];
  printf("%f,%.2f\n",elapsed,total);
  
  free(thread_handles);
  return 0;
}

