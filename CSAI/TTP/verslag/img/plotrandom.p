set title "recursive backtrack random schedule"
set term postscript enh
set output "random.eps"
set xlabel "experiment"
set ylabel "time (s)"
set datafile commentschars "#%"
#set nokey
set log y
plot "randomschedules.txt" index 0 w lp title "NL4", \
"randomschedules.txt" index 1 w lp title "NL6", \
"randomschedules.txt" index 2 w lp title "NL8", \
"randomschedules.txt" index 3 w lp title "NL10", \
"randomschedules.txt" index 4 w lp title "NL12", \
"randomschedules.txt" index 5 w lp title "NL14", \
"randomschedules.txt" index 6 w lp title "NL16"
