#!bin/bash

cd src

make

for nt in 1 2 4
do
  for file in trap_busy trap_mutex trap_sem
  do
    for ((i=0;i<10;i++))
    do
      ./$file $nt >> $file"_"$nt.csv
    done
  done
done

mv *.csv ../
cd ..

for nt in 1 2 4
do
  for file in trap_busy_$nt.csv
  do
    gawk -f media.gawk $file >> "media_"$nt"_trap_busy".csv
  done
done

for nt in 1 2 4
do
  for file in trap_mutex_$nt.csv
  do
    gawk -f media.gawk $file >> "media_"$nt"_trap_mutex".csv
  done
done

for nt in 1 2 4
do
  for file in trap_sem_$nt.csv
  do
    gawk -f media.gawk $file >> "media_"$nt"_trap_sem".csv
  done
done

for nt in 1 2 4
do
  for file in media_$nt*_busy.csv
  do
    gawk -f limpar.gawk $file >> "medias_trap_busy".csv
  done
done

for nt in 1 2 4
do
  for file in media_$nt*_mutex.csv
  do
    gawk -f limpar.gawk $file >> "medias_trap_mutex".csv
  done
done

for nt in 1 2 4
do
  for file in media_$nt*_sem.csv
  do
    gawk -f limpar.gawk $file >> "medias_trap_sem".csv
  done
done

rm media_*
rm trap_*

mkdir Medias_Trap
mv medias_* Medias_Trap

cd Medias_Trap

gnuplot <<- EOF
  set datafile separator ","
  set autoscale fix
  set style func linespoints
  set title "Relação do tempo com o número de threads para"
  set key above
  set xlabel "Nº Threads"
  set ylabel "Tempo (segundos)"
  set term png
  set output "grafico.png"
  plot "medias_trap_busy.csv" with lines title "Busy and Wait", "medias_trap_mutex.csv" with lines title "Mutex", "medias_trap_sem.csv" with lines title "Semáforos"
EOF
