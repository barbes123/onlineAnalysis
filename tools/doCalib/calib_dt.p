# Energy values are taken from http://www.nucleide.org/DDEP_WG/DDEPdata.htm  
set key box
set xtics offset 0, +0.6
set title "domain ".PA
set key left top
set yrange [0:12000]
plot 'ecalmapId'.PA.'.dat' using 1:2 with lines notitle    
set ylabel "keV" font "Times-Roman,12" offset 0, +1.5
set xlabel "Channels" font "Times-Roman,12" offset 0.2, +1.5
f(x)= a0 +a1*x
g(x)= b0 +b1*x+ b2*x*x
fit f(x) 'ecalmapId'.PA.'.dat' via a0,a1
fit g(x) 'ecalmapId'.PA.'.dat' via b0,b1,b2
plot 'ecalmapId'.PA.'.dat', f(x), 'ecalmapId'.PA.'.dat', g(x)
set terminal postscript color portrait dashed enhanced 'Times-Roman'
set output 'ecalmapId'.PA.'.eps'
set size 1,0.5
replot
pause 2
