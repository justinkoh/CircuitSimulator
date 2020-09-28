#set terminal png
set terminal pngcairo size 1200,600
set size 1,1
set output ofilename

f = system("read filename; echo $filename")
fname = f

set datafile separator ','
stats f skip 1
max_col = STATS_columns
print max_col
set key autotitle columnhead
#set format x '%e'
#set ylabel "Numerical Value(Volts)"
set ylabel 'Voltage/V, Current/A'
set xlabel "Time(0.) Seconds"
plot for [col=2:max_col] fname using 0:col with lines


#set multiplot layout 2,1
#plot for [col=2:6] fname using 0:col with lines
#set ylabel "Current/A"
#plot for [col=7:12] fname using 0:col with lines axis x1y2
