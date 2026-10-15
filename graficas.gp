# Configuración de salida
set terminal pngcairo size 900,650 font "Arial,10"
set grid

# =====================================================================
# GRÁFICA 1: COMPARATIVA DE TIEMPOS REALES DE CPU (Columna 2)
# =====================================================================
set output "comparativa_tiempos_real.png"
set title "Comparativa de Tiempos Medios de CPU (InsertSort vs BubbleSort)"
set xlabel "Tamaño de la permutación (N)"
set ylabel "Tiempo medio de CPU (Segundos)"
plot "insert_resultados.dat" using 1:2 with linespoints lw 2 title "InsertSort", \
     "bubble_resultados.dat" using 1:2 with linespoints lw 2 title "BubbleSort"

# =====================================================================
# GRÁFICA 2: ENVOLVENTE INSERTION (Media, Mín, Máx)
# =====================================================================
set output "ops_insert.png"
set title "Métricas de Operaciones Básicas en InsertSort"
set xlabel "Tamaño de la permutación (N)"
set ylabel "Número de Operaciones Básicas"
plot "insert_resultados.dat" using 1:3 with lines lw 2 lt rgb "blue" title "Media OB", \
     "insert_resultados.dat" using 1:4 with lines lt rgb "green" title "Mínimo OB", \
     "insert_resultados.dat" using 1:5 with lines lt rgb "red" title "Máximo OB"

# =====================================================================
# GRÁFICA 3: ENVOLVENTE BUBBLESORT (Media, Mín, Máx)
# =====================================================================
set output "ops_bubble.png"
set title "Métricas de Operaciones Básicas en BubbleSort"
set xlabel "Tamaño de la permutación (N)"
set ylabel "Número de Operaciones Básicas"
plot "bubble_resultados.dat" using 1:3 with lines lw 2 lt rgb "blue" title "Media OB", \
     "bubble_resultados.dat" using 1:4 with lines lt rgb "green" title "Mínimo OB", \
     "bubble_resultados.dat" using 1:5 with lines lt rgb "red" title "Máximo OB"
