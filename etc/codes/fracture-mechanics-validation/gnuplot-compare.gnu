set tics font "times,15"
set key font "times,15" bottom
set title  'Validation PSD Fracture'
set xlabel 'Time t' font "times,15"
set ylabel 'Force Fy(x,1) [kN]' font "Helvetica,15"

plot 'force-stress.data'  u 1:3  w lp pointinterval 25 pt 8 ps 2 lw 2 t 'PSD-stress-based', 'force-varf.data'  u 1:3  w lp pointinterval 25 pt 6 ps 2 lw 2 t 'PSD-varf-based', './ref/ref.data' u 1:2 w p pt 7 ps 1 t 'Ref-Ambhati(2014)'

set term postscript
set output "Force-vs-time.eps"
replot
