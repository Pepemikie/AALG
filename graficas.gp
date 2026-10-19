# Formato de los .dat (6 columnas): 1=N 2=n_elems 3=time(s) 4=average_ob 5=min_ob 6=max_ob
set terminal pngcairo size 900,650 font "Arial,10"
set grid

# ============ 1. Histograma de random_num (random_num.dat: valor frecuencia) ============
set output "histograma_random_num.png"
set title "Histograma de random num en [1, 10] (100000 muestras)"
set xlabel "Valor generado"
set ylabel "Frecuencia (número de apariciones)"
set style fill solid 0.7
set boxwidth 0.8
set xrange [0:11]
set xtics 1
set yrange [0:*]
plot "random_num.dat" using 1:2 with boxes title "Frecuencia observada", \
     10000 with lines lw 2 lt rgb "red" title "Frecuencia esperada (10000)"

unset xrange
unset yrange
unset boxwidth
set xtics autofreq
set key left top

# ============ 2. Tiempos medios de CPU (columna 3) ============
set output "comparativa_tiempos_real.png"
set title "Tiempo medio de CPU por permutación (InsertSort vs BubbleSort)"
set xlabel "Tamaño de la permutación N (elementos)"
set ylabel "Tiempo medio de CPU (s)"
plot "insert_resultados.dat" using 1:3 with linespoints lw 2 title "InsertSort", \
     "bubble_resultados.dat" using 1:3 with linespoints lw 2 title "BubbleSort"

# ============ 3. OB media de ambos (columna 4) ============
set output "comparativa_operaciones_medias.png"
set title "Número medio de ejecuciones de la OB"
set xlabel "Tamaño de la permutación N (elementos)"
set ylabel "Ejecuciones medias de la OB (comparaciones)"
plot "insert_resultados.dat" using 1:4 with linespoints lw 2 title "InsertSort", \
     "bubble_resultados.dat" using 1:4 with linespoints lw 2 title "BubbleSort"

# ============ 4 y 5. Media, mínimo y máximo: MISMA ESCALA Y en ambas ============
# YMAX ~ num_max*(num_max-1)/2 ; para num_max = 2000 -> 2000000
YMAX = 2000000
set yrange [0:YMAX]
set ylabel "Ejecuciones de la OB (comparaciones)"

set output "ops_insert.png"
set title "InsertSort: ejecuciones de la OB (media, mínimo y máximo)"
plot "insert_resultados.dat" using 1:4 with lines lw 2 lt rgb "blue" title "Media", \
     "insert_resultados.dat" using 1:5 with lines lt rgb "green" title "Mínimo", \
     "insert_resultados.dat" using 1:6 with lines lt rgb "red" title "Máximo"

set output "ops_bubble.png"
set title "BubbleSort: ejecuciones de la OB (media, mínimo y máximo)"
plot "bubble_resultados.dat" using 1:4 with lines lw 2 lt rgb "blue" title "Media", \
     "bubble_resultados.dat" using 1:5 with lines lt rgb "green" title "Mínimo", \
     "bubble_resultados.dat" using 1:6 with lines lt rgb "red" title "Máximo"
