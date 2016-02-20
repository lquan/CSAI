set term postscript enh
set output "ttsaNL14.eps"

set xlabel "time (s)"
set ylabel "cost"
set datafile commentschars "#%"
set nokey
set title "TTSA NL14"
set log x
plot "experiments14.txt" w lp, "experiments14A.txt" w lp, "experiments14B.txt" w lp, 189766
