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


