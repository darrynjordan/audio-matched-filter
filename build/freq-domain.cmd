set terminal png enhanced font 'Script,12' linewidth 0.1 
set title 'freq-domain'
set output 'freq-domain.png' 
set xlabel 'No Label'
set ylabel 'No Label'
plot 'freq-domain.dat' using 1:2 lt rgb 'blue' with lines notitle
