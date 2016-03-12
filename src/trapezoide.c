#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

extern double a, h;
extern int local_n;
double  total;
pthread_mutex_t   mutex;
long flag = 0;
sem_t sem;
extern int thread_count;

double f(double x) {

  double return_val;
  return_val = x*x;

  return return_val;

}

double trap(double  local_a, double  local_b, double h, int local_n) {

  double integral;
  double x;
  int i;
  integral = (f(local_a) + f(local_b))/2.0;
  x = local_a;
  for (i = 1; i <= local_n-1; i++) {
    x = local_a + i*h;
    integral += f(x);
  }
  integral = integral*h;
  return integral;
} /*  Trap  */

void *trap_mutex(void* rank) {
  double      local_a;
  double      local_b;
  double      my_int;
  long        my_rank = (long) rank;
  
  local_a = a + my_rank*local_n*h;
  local_b = local_a + local_n*h;

  my_int = trap(local_a, local_b, local_n, h);
  pthread_mutex_init(&mutex, NULL);
  pthread_mutex_lock(&mutex);
  total += my_int;
  pthread_mutex_unlock(&mutex);
  return NULL;
}

void *trap_busy(void* rank) {
  double      local_a;
  double      local_b;
  double      my_int;
  long        my_rank = (long) rank;

  local_a = a + my_rank*local_n*h;
  local_b = local_a + local_n*h;

  my_int = trap(local_a, local_b, local_n, h);
  
  while(flag != my_rank);
  total += my_int;
  flag=(flag+1)%thread_count;
  return NULL;
}

void *trap_sem(void* rank) {
  double      local_a;
  double      local_b;
  double      my_int;
  long        my_rank = (long) rank;

  local_a = a + my_rank*local_n*h;
  local_b = local_a + local_n*h;

  my_int = trap(local_a, local_b, local_n, h);
  sem_init(&sem, 0, 1);
  sem_wait(&sem);
  total += my_int;
  sem_post(&sem);
  sem_destroy(&sem);
  return NULL;
}
