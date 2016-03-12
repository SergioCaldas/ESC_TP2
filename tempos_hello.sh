#!bin/bash

cd src

gcc-5 -Wall -o hello hello.c -lpthread

for nt in 1 2 4
do
  ./hello $nt >> "hello_"$nt.csv
done

mv *csv ../
cd ..

for file in *csv
do
  gawk -f media.gawk $file >> "medias_"$file
done

for file in medias_*.csv
do
  gawk -f limpar.gawk $file >> "medias".csv
done

rm hello_*
rm medias_*

