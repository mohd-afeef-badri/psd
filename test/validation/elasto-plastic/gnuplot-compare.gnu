set multiplot

set tics font "times,15"
set key font "times,15" bottom
set xlabel 'Displacement of inner border' font "times,15"
set ylabel 'q/q_{lim}' font "Helvetica,15"


plot 'result.data' w  lp pt 8  ps 2  t 'PSD', './ref/ref.data' u 1:2  w lp pt 7 ps 1 t 'Ref'



set tics font "times,10"
set key font "times,10" bottom
set xlabel '' font "times,10"
set ylabel 'Error %' font "Helvetica,10"
set ytic 0.0001 
set size 0.65, 0.4
set origin 0.3, 0.3

plot '< paste result.data ./ref/ref.data' u 1:(abs($2-$4)*100/$4) w l lw 3 t ''

unset multiplot

set term postscript
set output "comp.eps"
load "gnuplot.input"
