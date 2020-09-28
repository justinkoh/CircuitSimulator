#run directly
#gnuplot -p manualTwoPlot.gnuplot>temp.png
#set terminal png
set terminal pngcairo size 1000,600
set size 1,1

set datafile separator ','

#fname = 'blah.csv'
set key autotitle columnhead
#set format x '%e'

set ylabel 'Voltage/V'
set xlabel "Time/milliseconds"

set multiplot layout 2,1
plot for [col=2:4] 'x.csv' using 0:col with lines
set ylabel "Current/A"
plot for [col=5:8] 'x.csv' using 0:col with lines axis x1y2
