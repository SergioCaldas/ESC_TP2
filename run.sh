#!bin/bash

a=0
b=1024


cd src

mkdir -p CSV

echo "Executing Ex1..."
echo "Nº Threads,Average Time (MiliSecounds),Time (MiliSecounds)" >> CSV/pth_hello.csv

for ((i=0;i<5;i++))
do
  ./pth_hello 1 >> CSV/pth_hello.csv
done

for n_threads in 2 4 8 16 32 64
do
  for ((i=0;i<5;i++))
  do
    ./pth_hello $n_threads >> CSV/pth_hello.csv
  done
done

echo "Executing EX2..."

echo "Prog_name,Nº Threads,a,b,n,Time (MiliSecounds),Result" >> CSV/trap_busy.csv
echo "Prog_name,Nº Threads,a,b,n,Time (MiliSecounds),Result" >> CSV/trap_mutex.csv
echo "Prog_name,Nº Threads,a,b,n,Time (MiliSecounds),Result" >> CSV/trap_sem.csv

for ((i=0;i<5;i++))
do
  ./trap_busy 1 $a $b 1 >> CSV/trap_busy.csv
  ./trap_mutex 1 $a $b 1 >> CSV/trap_mutex.csv
  ./trap_sem 1 $a $b 1 >> CSV/trap_sem.csv
done

for n_threads in 2 4 8 16 32 64
do
  for ((i=0;i<5;i++))
  do
    ./trap_busy $n_threads $a $b $n_threads >> CSV/trap_busy.csv
    ./trap_mutex $n_threads $a $b $n_threads >> CSV/trap_mutex.csv
    ./trap_sem $n_threads $a $b $n_threads >> CSV/trap_sem.csv
  done
done

echo "Done! All CSV's Generated"
