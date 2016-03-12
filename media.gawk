BEGIN {FS=",";}
NR {sum += $2 n++}
END {if(n>0) print $1","sum/n}
