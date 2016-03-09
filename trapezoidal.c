#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

double approx;

double f(double x) {
  double return_val;
  return_val = x*x;
  return return_val;
}

double trapezoidal (int a, int b, int n){
  int i;
  double x_i,h;
  h = (b-a)/n;
  approx = (f(a) + f(b))/2.0;
  for(i=1;i<=n-1;i++) {
    x_i = a + i*h;
    approx += f(x_i);
  }
  approx = h*approx;
  return approx;
}
