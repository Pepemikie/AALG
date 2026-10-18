# Configuración de salida
set terminal pngcairo size 900,650 font "Arial,10"
set grid

# =====================================================================
# GRÁFICA 1: HISTOGRAMA DE random_num (Apartado 1)
# =====================================================================
set output "histograma_random_num.png"
set title "Histograma de random_num en [1, 10] (100000 muestras)"
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
set key default

# =====================================================================
# GRÁFICA 2: COMPARATIVA DE TIEMPOS REALES DE CPU (Columna 2)
# =====================================================================
set output "comparativa_tiempos_real.png"
set title "Comparativa de Tiempos Medios de CPU (InsertSort vs BubbleSort)"
set xlabel "Tamaño de la permutación (N)"
set ylabel "Tiempo medio de CPU (Segundos)"
plot "insert_resultados.dat" using 1:2 with linespoints lw 2 title "InsertSort", \
     "bubble_resultados.dat" using 1:2 with linespoints lw 2 title "BubbleSort"

# =====================================================================
# GRÁFICA 3: COMPARATIVA DE OPERACIONES BÁSICAS MEDIAS (Columna 3)
# =====================================================================
set output "comparativa_operaciones_medias.png"
set title "Comparativa del Número Medio de Operaciones Básicas"
set xlabel "Tamaño de la permutación (N)"
set ylabel "Número medio de ejecuciones de la OB"
plot "insert_resultados.dat" using 1:3 with linespoints lw 2 title "InsertSort", \
     "bubble_resultados.dat" using 1:3 with linespoints lw 2 title "BubbleSort"

# =====================================================================
# GRÁFICA 4: ENVOLVENTE INSERTION (Media, Mín, Máx)
# =====================================================================
set output "ops_insert.png"
set title "Métricas de Operaciones Básicas en InsertSort"
set xlabel "Tamaño de la permutación (N)"
set ylabel "Número de Operaciones Básicas"
plot "insert_resultados.dat" using 1:3 with lines lw 2 lt rgb "blue" title "Media OB", \
     "insert_resultados.dat" using 1:4 with lines lt rgb "green" title "Mínimo OB", \
     "insert_resultados.dat" using 1:5 with lines lt rgb "red" title "Máximo OB"

# =====================================================================
# GRÁFICA 5: ENVOLVENTE BUBBLESORT (Media, Mín, Máx)
# =====================================================================
set output "ops_bubble.png"
set title "Métricas de Operaciones Básicas en BubbleSort"
set xlabel "Tamaño de la permutación (N)"
set ylabel "Número de Operaciones Básicas"
plot "bubble_resultados.dat" using 1:3 with lines lw 2 lt rgb "blue" title "Media OB", \
     "bubble_resultados.dat" using 1:4 with lines lt rgb "green" title "Mínimo OB", \
     "bubble_resultados.dat" using 1:5 with lines lt rgb "red" title "Máximo OB"
