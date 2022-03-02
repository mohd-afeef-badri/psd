set tics font "times,15"
set key font "times,15" bottom
set xlabel 'Displacement of inner border' font "times,15"
set ylabel 'q/q_{lim}' font "Helvetica,15"
plot 'result.data' w  lp pt 8  ps 2  t 'PSD', 'ref.data' u 1:2  w lp pt 7 ps 1 t 'Ref'

