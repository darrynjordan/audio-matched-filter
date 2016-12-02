set terminal png enhanced font 'Script,12' linewidth 0.3 
set title 'time-domain'
set output 'time-domain.png' 
set xlabel 'No Label'
set ylabel 'No Label'
plot 'time-domain.dat' using 1:2 lt rgb 'blue' with lines notitle
