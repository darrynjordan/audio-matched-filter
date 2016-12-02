set terminal png enhanced font 'Script,12' linewidth 0.3 
set title 'word-time-domain'
set output 'word-time-domain.png' 
set xlabel 'No Label'
set ylabel 'No Label'
plot 'word-time-domain.dat' using 1:2 lt rgb 'blue' with lines notitle
