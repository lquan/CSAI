set term postscript enh
set output "ttsaNL12.eps"

set xlabel "time (s)"
set ylabel "cost"
set datafile commentschars "#%"
set nokey
set title "TTSA NL12"
set yrange [100000:165000]
set log x
plot "nl12.txt" w lp, "nl12_2.txt" w lp, "nl12_3.txt" w lp, \
"nl12_4.txt" w lp, "nl12_5.txt" w lp, "nl12_6.txt" w lp, \
"nl12_10.txt" w lp, "nl12_12.txt" w lp, "nl12_13.txt" w lp, \
"experimentsA.txt" w lp, "experimentsB.txt" w lp, "experimentsC.txt" w lp, \
"experimentsD.txt" w lp, "experimentsE.txt" w lp, "experimentsF.txt" w lp, \
"experimentsG.txt" w lp, "experimentsH.txt" w lp, "experimentsJ.txt" w lp, \
"experimentsK.txt" w lp, 110729
