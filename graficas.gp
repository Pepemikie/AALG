# Formato de los .dat (6 columnas): 1=N 2=n_elems 3=time(s) 4=average_ob 5=min_ob 6=max_ob
set terminal pngcairo size 900,650 font "Arial,10"
set grid

# ============ 2. Tiempos medios de CPU (columna 3) ============
set output "comparativa_tiempos_real.png"
set title "Tiempo medio de CPU por permutación (Insert, Bubble y MergeSort)"
set xlabel "Tamaño de la permutación N (elementos)"
set ylabel "Tiempo medio de CPU (s)"
plot "insert_resultados.dat" using 1:3 with linespoints lw 2 title "InsertSort", \
     "bubble_resultados.dat" using 1:3 with linespoints lw 2 title "BubbleSort", \
     "merge_resultados.dat"  using 1:3 with linespoints lw 2 title "MergeSort"

# Misma gráfica con eje Y logarítmico (para ver MergeSort junto a los O(n^2))
set output "comparativa_tiempos_log.png"
set title "Tiempo medio de CPU (escala logarítmica en Y)"
set logscale y
plot "insert_resultados.dat" using 1:3 with linespoints lw 2 title "InsertSort", \
     "bubble_resultados.dat" using 1:3 with linespoints lw 2 title "BubbleSort", \
     "merge_resultados.dat"  using 1:3 with linespoints lw 2 title "MergeSort"
unset logscale y

# ============ 3. OB media (columna 4) ============
set output "comparativa_operaciones_medias.png"
set title "Número medio de ejecuciones de la OB"
set xlabel "Tamaño de la permutación N (elementos)"
set ylabel "Ejecuciones medias de la OB (comparaciones)"
plot "insert_resultados.dat" using 1:4 with linespoints lw 2 title "InsertSort", \
     "bubble_resultados.dat" using 1:4 with linespoints lw 2 title "BubbleSort", \
     "merge_resultados.dat"  using 1:4 with linespoints lw 2 title "MergeSort"

set output "comparativa_operaciones_log.png"
set title "Número medio de ejecuciones de la OB (escala logarítmica en Y)"
set logscale y
plot "insert_resultados.dat" using 1:4 with linespoints lw 2 title "InsertSort", \
     "bubble_resultados.dat" using 1:4 with linespoints lw 2 title "BubbleSort", \
     "merge_resultados.dat"  using 1:4 with linespoints lw 2 title "MergeSort"
unset logscale y

# ============ 4 y 5. Media, mínimo y máximo: MISMA ESCALA Y en Insert y Bubble ============
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

# MergeSort: escala propia (n log n es mucho menor que n^2)
set autoscale y

set output "ops_merge.png"
set title "MergeSort: ejecuciones de la OB (media, mínimo y máximo)"
plot "merge_resultados.dat" using 1:4 with lines lw 2 lt rgb "blue" title "Media", \
     "merge_resultados.dat" using 1:5 with lines lt rgb "green" title "Mínimo", \
     "merge_resultados.dat" using 1:6 with lines lt rgb "red" title "Máximo"

# ============ AJUSTES DE CURVAS: MergeSort ============
# Modelo teorico: comparaciones ~ a * n * ln(n); tiempo de CPU ~ b * n * ln(n)
# (columna 4 = OB media, columna 3 = tiempo de CPU medido con clock(), NO tiempo de pared)
# Intervalo de ajuste: ajustad LO y HI a vuestro num_min y num_max
LO = 100
HI = 2000

set fit logfile "fit_merge.log"

f_ob(x)   = a * x * log(x)
f_time(x) = b * x * log(x)
a = 1
b = 1e-7

fit [LO:HI] f_ob(x)   "merge_resultados.dat" using 1:4 via a
fit [LO:HI] f_time(x) "merge_resultados.dat" using 1:3 via b

set autoscale y
set xlabel "Tamaño de la permutación N (elementos)"

set output "fit_merge_ob.png"
set title sprintf("MergeSort: ajuste de la OB media  (a = %.4f, ajuste en [%d,%d])", a, LO, HI)
set ylabel "Ejecuciones medias de la OB (comparaciones)"
plot "merge_resultados.dat" using 1:4 with points pt 7 title "Datos medidos", \
     f_ob(x) with lines lw 2 lt rgb "red" title "a*n*ln(n)"

set output "fit_merge_time.png"
set title sprintf("MergeSort: ajuste del tiempo medio de CPU  (b = %.3e, ajuste en [%d,%d])", b, LO, HI)
set ylabel "Tiempo medio de CPU (s)"
plot "merge_resultados.dat" using 1:3 with points pt 7 title "Datos medidos", \
     f_time(x) with lines lw 2 lt rgb "red" title "b*n*ln(n)"
