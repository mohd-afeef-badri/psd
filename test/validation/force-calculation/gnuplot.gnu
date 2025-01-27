set tics font "times,15"
set key font "times,15" bottom
set xlabel ' ' font "times,15"
set ylabel 'Error in %' font "Helvetica,15"

if (!exists("MP_LEFT"))   MP_LEFT = .2
if (!exists("MP_RIGHT"))  MP_RIGHT = .95
if (!exists("MP_BOTTOM")) MP_BOTTOM = .14
if (!exists("MP_TOP"))    MP_TOP = .9
if (!exists("MP_xGAP"))   MP_xGAP = 0.15
if (!exists("MP_yGAP"))   MP_yGAP = 0.1


set multiplot layout 1,2 columnsfirst title "{/:Bold=15 Force Calculation error}" \
              margins screen MP_LEFT, MP_RIGHT, MP_BOTTOM, MP_TOP spacing screen MP_xGAP, MP_yGAP
 
 
unset ylabel 
unset xlabel
#set format y "%.1f"

set ytic 3
#set key box opaque
set ylabel '% Error'
#set xrange [-2*pi:2*pi]

set boxwidth 0.5
set style fill solid

set xlabel 'Stress-based'

plot 'psd-stress-based-err.data' u 1:3:xtic(2) with boxes t '', '' u 1:3:3 with labels offset char 0,0.5 t ''

unset ylabel



set ytic .01
set xlabel 'Variational-based'

plot 'psd-varf-based-err.data' u 1:3:xtic(2) with boxes t '', '' u 1:3:3 with labels offset char 0,0.5 t ''


unset ylabel
unset ytics
unset xlabel



set xlabel 'Variational-based'

unset multiplot
set term postscript
set output "comp.eps"
load "gnuplot.input"
