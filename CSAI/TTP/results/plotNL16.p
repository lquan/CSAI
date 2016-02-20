set title "TTSA NL16"
set term postscript enh
set output "ttsaNL16.eps"
set yrange [250000:450000]
set xlabel "time (s)"
set ylabel "cost"
set datafile commentschars "#%"
set nokey
set log x
plot "nl16_1.txt" w lp, "nl16_2.txt" w lp, "nl16_3.txt" w lp, 261687
