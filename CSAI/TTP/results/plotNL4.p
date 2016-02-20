set term postscript enh
set output "ttsaNL4.eps"

set xlabel "time (s)"
set ylabel "cost"
set datafile commentschars "#%"
set title "TTSA NL4"

plot "nl4.txt" w lp, "nl4_2.txt" w lp, "nl4_3.txt" w lp, "nl4_4.txt" w lp, \
"nl4_5.txt" w lp, 8276
