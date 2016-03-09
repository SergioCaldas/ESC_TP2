#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

double approx;

double f(double x) {
  
  double return_val;
  return_val = x*x;
  
  return return_val;

}

void *trap_busy(void* rank) {
  
  long my_rank = (long) rank;  /* Use long in case of 64-bit system */
  int a = 1;
  int b = 10000000;
  int n = 4;
  int i;
  long flag = 0;
  double x_i,h;
  
  h = (b-a)/n;
  
  approx = (f(a) + f(b))/2.0;
  
  printf("Estou a porta\n");
  for(i=1;i<=n-1;i++) {
      printf("Na fila\n");
      while(flag != my_rank);
      printf("Entrei\n");
      x_i = a + i*h;
      approx += f(x_i);
      flag++;
      printf("Entrei\n");
  }

  approx = h*approx;
  
  printf("Thread: %ld Resultado = %f\n", my_rank,approx);

  return NULL;
}

void *trap_mutex(void* rank) {
  
  long my_rank = (long) rank;  /* Use long in case of 64-bit system */
  int a = 1;
  int b = 10000000;
  int n = 4;
  int i;
  double x_i,h;
  
  h = (b-a)/n;
  
  approx = (f(a) + f(b))/2.0;
  
  for(i=1;i<=n-1;i++) {
    x_i = a + i*h;
    approx += f(x_i);
  }
  
  approx = h*approx;
  
  printf("Thread: %ld Resultado = %f\n", my_rank,approx);

  return NULL;
}

void *trap_sem(void* rank) {
  
  long my_rank = (long) rank;  /* Use long in case of 64-bit system */
  int a = 1;
  int b = 10000000;
  int n = 4;
  int i;
  double x_i,h;
  
  h = (b-a)/n;
  
  approx = (f(a) + f(b))/2.0;
  
  for(i=1;i<=n-1;i++) {
    x_i = a + i*h;
    approx += f(x_i);
  }
  
  approx = h*approx;
  
  printf("Thread: %ld Resultado = %f\n", my_rank,approx);

  return NULL;
}

