#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "trapezoidal.h"
#include "timer.h"

const int MAX_THREADS = 4;

/* Global variable:  accessible to all threads */
int thread_count;
double start, stop, elapsed;

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
  double tempos[thread_count];
  
  /* Get number of threads from command line */
  if (argc != 3) Usage(argv[0]);
  
  thread_count = strtol(argv[1], NULL, 10);
  
  if (thread_count <= 0 || thread_count > MAX_THREADS) Usage(argv[0]);
  
  thread_handles = malloc (thread_count*sizeof(pthread_t));
  
  for (thread = 0; thread < thread_count; thread++){
    GET_TIME(start);
    tempos[thread]=start;
    pthread_create(&thread_handles[thread], NULL,(void*) argv[2], (void*) thread);
    printf("Passei\n");
  }

  printf("Hello from the main thread\n");

  for (thread = 0; thread < thread_count; thread++){
    pthread_join(thread_handles[thread], NULL);
    GET_TIME(stop);
    elapsed = stop - tempos[thread];
    printf("%f\n",elapsed);
  }
  
  free(thread_handles);
  return 0;
}

