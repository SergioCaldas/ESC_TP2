/* 
 * APina - 2016
 * */
/*
 * compilar com:  g++-mp-5  --std=c++11 -Wall -O2 -fopenmp -o ex2_v2 ex2_v2.cxx
 * usar  modos de escalonamento : export OMP_SCHEDULE="guided", OMP_SCHEDULE="dynamic", OMP_SCHEDULE="static" 
 * */
/*
 * ExecuÃ§Ã£o:
 *  ./ex2_v2 <n.threads> <opcional- intervalo>
 *  */
#include <cstdlib>
#include <iostream>
#include <random>
using namespace std;
#include <omp.h>

#define S 1024*1024
define S 100

int main(int argc, char *argv[]){
  int i, r, a[S], np, nr;
  double T1,T2;

  np = atoi(argv[1]);
  if (argc == 2)  nr= 99; else nr= atoi(argv[2]);

  std::random_device d;
  std::default_random_engine e1(d());
  // a distribution that takes randomness and produces values in specified range
  std::uniform_int_distribution<> dist(1,nr);

  omp_set_num_threads(np);
  T1 = omp_get_wtime();
#pragma omp parallel for private (r) schedule (runtime) 
  for (i=0 ; i < S ; i++) {
    a[i] = 0.;
    for (r = dist(e1) ; r > 0 ; r -= 20) {
      T2 = omp_get_wtime();
      cout << "fiosExecucao =" << np << " Intervalo=" << nr <<  ": tempo -> "<< (T2-T1)*1e6 << " usecs\n";
    }
  }
}
