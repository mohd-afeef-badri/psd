set tics font "times,15"
set key font "times,15" bottom
set title  'Varf based force calculation model'
set xlabel ' ' font "times,15"
set ylabel 'Error in %' font "Helvetica,15"

set boxwidth 0.5
set style fill solid

plot 'psd-varf-based-err.data' u 1:3:xtic(2) with boxes t ''

set term postscript
set output "varf-based.eps"
replot
