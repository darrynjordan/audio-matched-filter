set terminal png enhanced font 'Script,12' linewidth 0.3 
set title 'word-freq-domain'
set output 'word-freq-domain.png' 
set xlabel 'No Label'
set ylabel 'No Label'
plot 'word-freq-domain.dat' using 1:2 lt rgb 'blue' with lines notitle
