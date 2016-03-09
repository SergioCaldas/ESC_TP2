#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "trapezoidal.h"
#include "timer.h"

const int MAX_THREADS = 4;

/* Global variable:  accessible to all threads */
int thread_count;
double start, stop, elapsed;

void *trapezoidal_rule(void* rank) {
  long my_rank = (long) rank;  /* Use long in case of 64-bit system */

  printf("Thread: %ld Resultado = %f\n", my_rank, trapezoidal(1,10000000,10));

  return NULL;
}

/*-------------------------------------------------------------------*/
void Usage(char* prog_name) {
  fprintf(stderr, "usage: %s <number of threads>\n", prog_name);
  fprintf(stderr, "0 < number of threads <= %d\n", MAX_THREADS);
  exit(0);
}


/*--------------------------------------------------------------------*/
int main(int argc, char* argv[]) {
  long       thread;  /* Use long in case of a 64-bit system */
  pthread_t* thread_handles;

  /* Get number of threads from command line */
  if (argc != 2) Usage(argv[0]);
  thread_count = strtol(argv[1], NULL, 10);
  if (thread_count <= 0 || thread_count > MAX_THREADS) Usage(argv[0]);

  thread_handles = malloc (thread_count*sizeof(pthread_t));

  for (thread = 0; thread < thread_count; thread++){
    GET_TIME(start);
    pthread_create(&thread_handles[thread], NULL,trapezoidal_rule, (void*) thread);
    GET_TIME(stop);
    elapsed = stop - start;
    printf("%f\n",elapsed);
  }

  printf("Hello from the main thread\n");

  for (thread = 0; thread < thread_count; thread++){
    pthread_join(thread_handles[thread], NULL);
  }
  free(thread_handles);
  return 0;
}

