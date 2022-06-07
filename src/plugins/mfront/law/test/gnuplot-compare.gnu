set multiplot

set tics font "times,15"
set key font "times,15" bottom left
set xlabel 'time steps' font "times,15"
set ylabel 'Stress_{xy}' font "Helvetica,15"


 plot 'fileSigOut.data' u 1 w lp lw 1 ps 1 pt 4 t 'MFront-PSD', './../../../soil-laws/hujeux-law-lib/fileSigOutRef.data' u 1 w lp lw 1 ps 1 pt 10 t 'C++'



set tics font "times,10"
set key font "times,8" bottom
set xlabel '' font "times,10"
set ylabel 'Error %' font "Helvetica,8"
set xtic 50
set ytic 10
set size 0.5, 0.35
set origin 0.45, 0.5

plot '< paste fileSigOut.data ./../../../soil-laws/hujeux-law-lib/fileSigOutRef.data' u (abs($1-$3)*100/$3) w l lw 3 t ''

unset multiplot

