#!bin/bash

make

max=10

for file in trap_*
do
  for ((i=0;i<$max;i++))
  do
    ./$file 4 >> $file.csv
  done
done

