BEGIN {FS=",";}
NR {print $1","$2}
END {}
