set tics font "times,15"
set key font "times,15" bottom
set title  'Plain Stress model'
set xlabel 'x position' font "times,15"
set ylabel 'Displacement Uy(x,0.5)' font "Helvetica,15"

plot './ref/ref-plain-stress.data'  u 1:2 w lp pointinterval 20 pt 7 ps 1  lw 5 t 'Ref', 'psd-plain-stress.data' u 1:2  w lp pointinterval 20 pt 8 ps 2 lw 2 t 'PSD'

set term postscript
set output "plain-stress.eps"
replot
