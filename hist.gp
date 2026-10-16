# Parametros del experimento (deben coincidir con los de exercise1)
inf = 1
sup = 10
muestras = 100000
esperada = muestras / (sup - inf + 1.0)

set terminal pngcairo size 800,500
set output 'histograma.png'

set title sprintf("Histograma de random\\_num en [%d, %d] (%d muestras)", inf, sup, muestras)
set xlabel "Valor generado"
set ylabel "Frecuencia (numero de apariciones)"

set style fill solid 0.7
set boxwidth 0.8
set xtics 1
set xrange [inf-0.6:sup+0.6]
set yrange [0:*]          # el eje Y empieza en 0 para no exagerar diferencias
set key outside bottom center horizontal

plot 'hist.dat' using 1:2 with boxes title "Frecuencia observada", \
     esperada with lines lw 2 lc rgb "red" title sprintf("Frecuencia esperada (%.0f)", esperada)