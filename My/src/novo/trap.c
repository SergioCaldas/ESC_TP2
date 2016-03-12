#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "timer.h"
#ifdef D_SEMAPHORE
#include <semaphore.h>
#endif
#include <math.h>

const int MAX_THREADS = 48;

/* Global variable:  accessible to all threads */
int thread_count;
double start, stop, elapsed;
double total;
int n, local_n;
double a, b, h;
double total;

#ifdef D_SEMAPHORE
sem_t sem;
#endif

#ifdef D_MUTEX
pthread_mutex_t mutex;
#endif

#ifdef D_BUSYWAITING
long flag = 0;
#endif


void Usage (char* prog_name);
void* trap_thread (void *rank);
double trap(double local_a,double local_b,double h, int local_c);
double function(double x);

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

  #ifdef D_MUTEX
  pthread_mutex_init(&mutex, NULL);
  #endif

  #ifdef D_SEMAPHORE
  sem_init(&sem, 0, 1);
  #endif

  GET_TIME(start);
  printf("Cheguei\n");
  for (thread = 0; thread < thread_count; thread++){
    printf("Entrei Thread[%ld]\n",thread);
    pthread_create(&thread_handles[thread], NULL, trap_thread , (void*) thread);
    printf("Criei Thread[%ld]\n",thread);
  }

  for (thread = 0; thread < thread_count; thread++){
    printf("Estou preparado para sair Thread[%ld]\n",thread);
    pthread_join(thread_handles[thread], NULL);
    printf("Sai Thread[%ld]\n",thread);
  }
  #ifdef D_SEMAPHORE
  sem_destroy(&sem);
  #endif

  #ifdef D_MUTEX
  pthread_mutex_destroy(&mutex);
  #endif

  GET_TIME(stop);
  elapsed = stop - start;
  printf("%s,%ld,%.2f,%.2f,%d,%.2f,%.2f\n",prog_name,thread,a,b,n,elapsed*pow(10,3),total);
  
  free(thread_handles);
  return 0;
}

void *trap_thread(void* rank) {
  double      local_a;
  double      local_b;
  double      my_integral;
  long        my_rank = (long) rank;
  
  local_a = a + my_rank*local_n*h;
  local_b = local_a + local_n*h;

  my_integral = trap(local_a, local_b, h, local_n);
  
  #ifdef D_BUSYWAITING
  while(flag != my_rank);
  total += my_integral;
  flag=(flag+1)%local_n;
  #endif

  #ifdef D_MUTEX
  pthread_mutex_lock(&mutex);
  total += my_integral;
  pthread_mutex_unlock(&mutex);
  #endif

  #ifdef D_SEMAPHORE
  sem_wait(&sem);
  total += my_integral;
  sem_post(&sem);
  #endif

  return NULL;
}


double trap(double  local_a, double  local_b, double h, int local_n) {

  double integral;
  double x;
  int i;
  integral = (function(local_a) + function(local_b))/2.0;
  for (i = 1; i <= local_n-1; i++) {
    x = local_a + i*h;
    integral += function(x);
  }
  integral = integral*h;
  return integral;
} /*  Trap  */

double function(double x) {

  double return_val;
  return_val = x*x;

  return return_val;

}

/*-------------------------------------------------------------------*/
void Usage(char* prog_name) {

  fprintf(stderr, "usage: %s <number of threads>\n", prog_name);
  fprintf(stderr, "0 < number of threads <= %d\n", MAX_THREADS);
  exit(0);

}
