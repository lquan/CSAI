set term postscript enh
set output "ttsaNL8.eps"

set xlabel "time (s)"
set ylabel "cost"
set datafile commentschars "#%"
set nokey
set title "TTSA NL8"
set log x
plot "nl8.txt" w lp, "nl8_2.txt" w lp, "nl8_3.txt" w lp, 39721
