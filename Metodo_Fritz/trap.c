#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "timer.h"

#ifdef D_SEMAPHORE
#include <semaphore.h>
#endif

const int MAX_THREADS = 48;

#ifdef D_MUTEX
pthread_mutex_t mutex;
#endif

#ifdef D_SEMAPHORE
sem_t sem;
#endif

#ifdef D_BUSYWAITING
long flag = 0;
#endif

/* Global variable:  accessible to all threads */
int thread_count;
double start, stop, elapsed;
double total;
int n;
double a, b, h;
double all_approx;
int n_thread;

/*--Global Functions*/
void Usage (char* prog_name);
void *job_thread(void* rank);                 /* Thread function */
double trapezoidal_rule(double a_thread, double b_thread, int n_thread, double h);  /* Calculate integral for thread */
double f(double x); 

/*-------------------------------------------------------------------*/
void Usage(char* prog_name) {

  fprintf(stderr, "usage: %s <number of threads>\n", prog_name);
  fprintf(stderr, "0 < number of threads <= %d\n", MAX_THREADS);
  exit(0);

}

/*-------------- f(x) --------------*/
double f(double x) {
  double return_val;

  return_val = x*x;
  return return_val;
}

double trapezoidal_rule (double a_thread, double b_thread, int n_thread, double h) {

  double approx;
  double x;
  int i;
  approx = (f(a_thread) + f(b_thread))/2.0;
  x = a_thread;
  for (i = 1; i <= n_thread-1; i++) {
    x = a_thread + i*h;
    approx += f(x);
  }
  approx = approx*h;
  return approx;
} /*  Trap  */

void* job_thread(void *rank){
  long my_rank = (long) rank;
  double a_thread;
  double b_thread;
  double my_integral;

  a_thread = a + my_rank*n_thread*h;
  b_thread = a_thread + n_thread*h;

  my_integral = trapezoidal_rule(a_thread, b_thread, n_thread, h);

#ifdef D_SEMAPHORE
  sem_wait(&sem);
  all_approx+=my_integral;
  sem_post(&sem);
#endif

#ifdef D_MUTEX
  pthread_mutex_lock(&mutex);
  all_approx += my_integral;
  pthread_mutex_unlock(&mutex);
#endif

#ifdef D_BUSYWAITING
  while(flag != my_rank){
    all_approx += my_integral;
    flag = (flag+1) % thread_count;
  }
#endif

  return NULL;
}

/*--------------------------------------------------------------------*/
int main(int argc, char* argv[]) {

  long thread;  /* Use long in case of a 64-bit system */
  pthread_t* thread_handles;
  all_approx=0.0;
  char* prog_name = argv[0];

  if (argc < 5 ) Usage(prog_name);
  thread_count = strtol(argv[1], NULL, 10);
  if (thread_count <= 0 || thread_count > MAX_THREADS) Usage(prog_name);



  a = strtol(argv[2], NULL, 10);
  b = strtol(argv[3], NULL, 10);
  n = strtol(argv[4], NULL, 10);

  h=(b-a)/n;

  n_thread = n/thread_count;

  thread_handles = malloc (thread_count*sizeof(pthread_t));

#ifdef D_MUTEX
  pthread_mutex_init(&mutex, NULL);
#endif


#ifdef D_SEMAPHORE
  sem_init(&sem, 0, 1); /** 0 - semaphore shared by all threads, 1 - Semaphore initialized as unlocked **/
#endif

  GET_TIME(start);
  for (thread = 0; thread < thread_count; thread++){
    pthread_create(&thread_handles[thread], NULL, job_thread , (void*) thread);
  }

  for (thread = 0; thread < thread_count; thread++){
    pthread_join(thread_handles[thread], NULL);
  }
  GET_TIME(stop);

  elapsed = stop - start;
  printf("%s,%d,%.2f,%.2f,%d,%.2f,%.2f\n",prog_name,thread_count,a,b,n,elapsed,all_approx);

#ifdef D_SEMAPHORE
  sem_destroy(&sem);
#endif


#ifdef D_MUTEX  
  pthread_mutex_destroy(&mutex);
#endif

  free(thread_handles);
  return 0;
}

