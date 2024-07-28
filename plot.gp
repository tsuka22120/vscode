reset
set xrange [0:100000]
set grid
set xlabel "N"
set ylabel "m"
set term pdfcairo enhanced
set output "quickgraph.pdf"
plot "quick.txt" us 1:2 t "quick sort" w d
exit