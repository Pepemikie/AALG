# ==============================================================================
# plot_results.gp - Gráficas comparativas con ajustes y referencias teóricas
# Uso: gnuplot plot_results.gp
# ==============================================================================

set terminal pngcairo size 1050,680 enhanced font "Arial,11"
set grid linestyle 0 linecolor rgb "#dcdcdc"
set key top left box opaque font "Arial,9" spacing 1.15
set xlabel "Tamaño del diccionario (n)"
set offsets 0, 0, graph 0.22, graph 0.03

# COL = 3 -> Tiempo medio (s) | COL = 4 -> Operaciones básicas medias (OB)
COL = 3
if (COL == 3) {
    set ylabel "Tiempo medio de búsqueda (s)"
    PREFIX = "time"
} else {
    set ylabel "Operaciones básicas medias (OB)"
    PREFIX = "ob"
}

set fit quiet
set fit logfile "/dev/null"

# Funciones de ajuste
f_lin(x)  = a_lin * x + b_lin
f_log(x)  = a_log * (log(x)/log(2)) + b_log
f_auto(x) = a_auto * x + b_auto
f_sqrt(x) = a_sqrt * sqrt(x) + b_sqrt

# Estilos de datos y ajustes
set style line 1 lc rgb "#1f77b4" pt 7 ps 1.2 lw 2.0   # Lineal
set style line 2 lc rgb "#2ca02c" pt 5 ps 1.2 lw 2.0   # Binaria
set style line 3 lc rgb "#d62728" pt 9 ps 1.2 lw 2.0   # Autoorganizada

# Estilos de referencia teórica de fondo (más visibles y con colores diferenciados)
set style line 11 lc rgb "#557799" lw 2.2 dt (10,6)    # Ref teórica O(n) -> azul apagado
set style line 12 lc rgb "#448855" lw 2.2 dt (6,4)     # Ref teórica O(log2 n) -> verde apagado
set style line 13 lc rgb "#aa5555" lw 2.2 dt (2,4)     # Ref teórica O(sqrt(n)) -> rojo apagado


# ==============================================================================
# 1. UNIFORME - ORDENADO (Lineal, Binaria, Autoorganizada)
# ==============================================================================
set output sprintf("grafica_1_uniforme_ordenado_%s.png", PREFIX)
set title "Diccionarios ordenados - Generador uniforme"

stats "results/uniform_sorted_linear.dat" using 1:COL nooutput
c_lin = STATS_max_y / STATS_max_x
stats "results/uniform_sorted_binary.dat" using 1:COL nooutput
c_log = STATS_max_y / (log(STATS_max_x)/log(2))

a_lin = 1e-8; b_lin = 1e-12
fit f_lin(x) "results/uniform_sorted_linear.dat" using 1:COL via a_lin, b_lin
a_log = 1e-8; b_log = 1e-12
fit f_log(x) "results/uniform_sorted_binary.dat" using 1:COL via a_log, b_log
a_auto = 1e-8; b_auto = 1e-12
fit f_auto(x) "results/uniform_sorted_auto.dat" using 1:COL via a_auto, b_auto

plot c_lin * x title "Ref. teórica: O(n)" with lines ls 11, \
     c_log * (log(x)/log(2)) title "Ref. teórica: O(log₂ n)" with lines ls 12, \
     "results/uniform_sorted_linear.dat" using 1:COL title "Lineal (datos)" with points ls 1, \
     f_lin(x) title sprintf("Lineal ajuste: %.2e·n %+.2e", a_lin, b_lin) with lines ls 1 dt 2, \
     "results/uniform_sorted_binary.dat" using 1:COL title "Binaria (datos)" with points ls 2, \
     f_log(x) title sprintf("Binaria ajuste: %.2e·log₂(n) %+.2e", a_log, b_log) with lines ls 2 dt 2, \
     "results/uniform_sorted_auto.dat" using 1:COL title "Autoorganizada (datos)" with points ls 3, \
     f_auto(x) title sprintf("Auto ajuste: %.2e·n %+.2e", a_auto, b_auto) with lines ls 3 dt 2

# ==============================================================================
# 2. UNIFORME - NO ORDENADO (Lineal, Autoorganizada)
# ==============================================================================
set output sprintf("grafica_2_uniforme_desordenado_%s.png", PREFIX)
set title "Diccionarios no ordenados - Generador uniforme"

stats "results/uniform_unsorted_linear.dat" using 1:COL nooutput
c_lin = STATS_max_y / STATS_max_x

a_lin = 1e-8; b_lin = 1e-12
fit f_lin(x) "results/uniform_unsorted_linear.dat" using 1:COL via a_lin, b_lin
a_auto = 1e-8; b_auto = 1e-12
fit f_auto(x) "results/uniform_unsorted_auto.dat" using 1:COL via a_auto, b_auto

plot c_lin * x title "Ref. teórica: O(n)" with lines ls 11, \
     "results/uniform_unsorted_linear.dat" using 1:COL title "Lineal (datos)" with points ls 1, \
     f_lin(x) title sprintf("Lineal ajuste: %.2e·n %+.2e", a_lin, b_lin) with lines ls 1 dt 2, \
     "results/uniform_unsorted_auto.dat" using 1:COL title "Autoorganizada (datos)" with points ls 3, \
     f_auto(x) title sprintf("Auto ajuste: %.2e·n %+.2e", a_auto, b_auto) with lines ls 3 dt 2

# ==============================================================================
# 3. POTENCIAL - ORDENADO (Lineal, Binaria, Autoorganizada)
# ==============================================================================
set output sprintf("grafica_3_potencial_ordenado_%s.png", PREFIX)
set title "Diccionarios ordenados - Generador potencial"

stats "results/potential_sorted_linear.dat" using 1:COL nooutput
c_lin = STATS_max_y / STATS_max_x
stats "results/potential_sorted_binary.dat" using 1:COL nooutput
c_log = STATS_max_y / (log(STATS_max_x)/log(2))
stats "results/potential_sorted_auto.dat" using 1:COL nooutput
c_sqrt = STATS_max_y / sqrt(STATS_max_x)

a_lin = 1e-8; b_lin = 1e-12
fit f_lin(x) "results/potential_sorted_linear.dat" using 1:COL via a_lin, b_lin
a_log = 1e-8; b_log = 1e-12
fit f_log(x) "results/potential_sorted_binary.dat" using 1:COL via a_log, b_log
a_sqrt = 1e-7; b_sqrt = 1e-12
fit f_sqrt(x) "results/potential_sorted_auto.dat" using 1:COL via a_sqrt, b_sqrt

plot c_lin * x title "Ref. teórica: O(n)" with lines ls 11, \
     c_log * (log(x)/log(2)) title "Ref. teórica: O(log₂ n)" with lines ls 12, \
     c_sqrt * sqrt(x) title "Ref. teórica: O(√n)" with lines ls 13, \
     "results/potential_sorted_linear.dat" using 1:COL title "Lineal (datos)" with points ls 1, \
     f_lin(x) title sprintf("Lineal ajuste: %.2e·n %+.2e", a_lin, b_lin) with lines ls 1 dt 2, \
     "results/potential_sorted_binary.dat" using 1:COL title "Binaria (datos)" with points ls 2, \
     f_log(x) title sprintf("Binaria ajuste: %.2e·log₂(n) %+.2e", a_log, b_log) with lines ls 2 dt 2, \
     "results/potential_sorted_auto.dat" using 1:COL title "Autoorganizada (datos)" with points ls 3, \
     f_sqrt(x) title sprintf("Auto ajuste: %.2e·√n %+.2e", a_sqrt, b_sqrt) with lines ls 3 dt 2

# ==============================================================================
# 4. POTENCIAL - NO ORDENADO (Lineal, Autoorganizada)
# ==============================================================================
set output sprintf("grafica_4_potencial_desordenado_%s.png", PREFIX)
set title "Diccionarios no ordenados - Generador potencial"

stats "results/potential_unsorted_linear.dat" using 1:COL nooutput
c_lin = STATS_max_y / STATS_max_x
stats "results/potential_unsorted_auto.dat" using 1:COL nooutput
c_sqrt = STATS_max_y / sqrt(STATS_max_x)

a_lin = 1e-8; b_lin = 1e-12
fit f_lin(x) "results/potential_unsorted_linear.dat" using 1:COL via a_lin, b_lin
a_sqrt = 1e-7; b_sqrt = 1e-12
fit f_sqrt(x) "results/potential_unsorted_auto.dat" using 1:COL via a_sqrt, b_sqrt

plot c_lin * x title "Ref. teórica: O(n)" with lines ls 11, \
     c_sqrt * sqrt(x) title "Ref. teórica: O(√n)" with lines ls 13, \
     "results/potential_unsorted_linear.dat" using 1:COL title "Lineal (datos)" with points ls 1, \
     f_lin(x) title sprintf("Lineal ajuste: %.2e·n %+.2e", a_lin, b_lin) with lines ls 1 dt 2, \
     "results/potential_unsorted_auto.dat" using 1:COL title "Autoorganizada (datos)" with points ls 3, \
     f_sqrt(x) title sprintf("Auto ajuste: %.2e·√n %+.2e", a_sqrt, b_sqrt) with lines ls 3 dt 2

# ==============================================================================
# 5. GAUSIANO - ORDENADO (Lineal, Binaria, Autoorganizada)
# ==============================================================================
set output sprintf("grafica_5_gausiano_ordenado_%s.png", PREFIX)
set title "Diccionarios ordenados - Generador gausiano"

stats "results/gaussian_sorted_linear.dat" using 1:COL nooutput
c_lin = STATS_max_y / STATS_max_x
stats "results/gaussian_sorted_binary.dat" using 1:COL nooutput
c_log = STATS_max_y / (log(STATS_max_x)/log(2))

a_lin = 1e-8; b_lin = 1e-12
fit f_lin(x) "results/gaussian_sorted_linear.dat" using 1:COL via a_lin, b_lin
a_log = 1e-8; b_log = 1e-12
fit f_log(x) "results/gaussian_sorted_binary.dat" using 1:COL via a_log, b_log
a_auto = 1e-8; b_auto = 1e-12
fit f_auto(x) "results/gaussian_sorted_auto.dat" using 1:COL via a_auto, b_auto

plot c_lin * x title "Ref. teórica: O(n)" with lines ls 11, \
     c_log * (log(x)/log(2)) title "Ref. teórica: O(log₂ n)" with lines ls 12, \
     "results/gaussian_sorted_linear.dat" using 1:COL title "Lineal (datos)" with points ls 1, \
     f_lin(x) title sprintf("Lineal ajuste: %.2e·n %+.2e", a_lin, b_lin) with lines ls 1 dt 2, \
     "results/gaussian_sorted_binary.dat" using 1:COL title "Binaria (datos)" with points ls 2, \
     f_log(x) title sprintf("Binaria ajuste: %.2e·log₂(n) %+.2e", a_log, b_log) with lines ls 2 dt 2, \
     "results/gaussian_sorted_auto.dat" using 1:COL title "Autoorganizada (datos)" with points ls 3, \
     f_auto(x) title sprintf("Auto ajuste: %.2e·n %+.2e", a_auto, b_auto) with lines ls 3 dt 2

# ==============================================================================
# 6. GAUSIANO - NO ORDENADO (Lineal, Autoorganizada)
# ==============================================================================
set output sprintf("grafica_6_gausiano_desordenado_%s.png", PREFIX)
set title "Diccionarios no ordenados - Generador gausiano"

stats "results/gaussian_unsorted_linear.dat" using 1:COL nooutput
c_lin = STATS_max_y / STATS_max_x

a_lin = 1e-8; b_lin = 1e-12
fit f_lin(x) "results/gaussian_unsorted_linear.dat" using 1:COL via a_lin, b_lin
a_auto = 1e-8; b_auto = 1e-12
fit f_auto(x) "results/gaussian_unsorted_auto.dat" using 1:COL via a_auto, b_auto

plot c_lin * x title "Ref. teórica: O(n)" with lines ls 11, \
     "results/gaussian_unsorted_linear.dat" using 1:COL title "Lineal (datos)" with points ls 1, \
     f_lin(x) title sprintf("Lineal ajuste: %.2e·n %+.2e", a_lin, b_lin) with lines ls 1 dt 2, \
     "results/gaussian_unsorted_auto.dat" using 1:COL title "Autoorganizada (datos)" with points ls 3, \
     f_auto(x) title sprintf("Auto ajuste: %.2e·n %+.2e", a_auto, b_auto) with lines ls 3 dt 2

unset output

