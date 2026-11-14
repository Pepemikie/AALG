# Formato de los .dat (6 columnas): 1=N 2=n_elems 3=time(s) 4=average_ob 5=min_ob 6=max_ob
set terminal pngcairo size 900,650 font "Arial,10"
set termoption noenhanced
set grid

# ---------- Configuración ----------
BASE   = "resultados.dat"          # el mismo valor que pasas a -outputFile
names  = "merge quick_min quick_mean quick_median"
labels = "MergeSort QuickSort_min QuickSort_mean QuickSort_median"
NALG   = 4
file(i)  = word(names, i)."_".BASE
label(i) = word(labels, i)
name(i)  = word(names, i)

# Intervalo de ajuste: ajustad LO y HI a vuestro num_min y num_max
LO = 100
HI = 2000

# ============ Tiempos medios de CPU (columna 3) ============
set xlabel "Tamaño de la permutación N (elementos)"
set ylabel "Tiempo medio de CPU (s)"

set output "comparativa_tiempos_real.png"
set title "Tiempo medio de CPU por permutación"
plot for [i=1:NALG] file(i) using 1:3 with linespoints lw 2 title label(i)

set output "comparativa_tiempos_log.png"
set title "Tiempo medio de CPU (escala logarítmica en Y)"
set logscale y
plot for [i=1:NALG] file(i) using 1:3 with linespoints lw 2 title label(i)
unset logscale y

# ============ OB media (columna 4) ============
set ylabel "Ejecuciones medias de la OB (comparaciones)"

set output "comparativa_operaciones_medias.png"
set title "Número medio de ejecuciones de la OB"
plot for [i=1:NALG] file(i) using 1:4 with linespoints lw 2 title label(i)

set output "comparativa_operaciones_log.png"
set title "Número medio de ejecuciones de la OB (escala logarítmica en Y)"
set logscale y
plot for [i=1:NALG] file(i) using 1:4 with linespoints lw 2 title label(i)
unset logscale y

# ============ Media, mínimo y máximo de la OB (uno por algoritmo) ============
set autoscale y
set ylabel "Ejecuciones de la OB (comparaciones)"

do for [i=1:NALG] {
  set output "ops_".name(i).".png"
  set title label(i).": ejecuciones de la OB (media, mínimo y máximo)"
  plot file(i) using 1:4 with lines lw 2 lt rgb "blue"  title "Media", \
       file(i) using 1:5 with lines lt rgb "green" title "Mínimo", \
       file(i) using 1:6 with lines lt rgb "red"   title "Máximo"
}

# ============ AJUSTES DE CURVAS ============
# Modelo teórico: comparaciones ~ a * n * ln(n); tiempo de CPU ~ b * n * ln(n)
# (columna 4 = OB media, columna 3 = tiempo de CPU medido con clock(), NO tiempo de pared)
f_ob(x)   = a * x * log(x)
f_time(x) = b * x * log(x)

do for [i=1:NALG] {
  set fit logfile "fit_".name(i).".log"

  # reiniciar valores iniciales para que un ajuste no contamine al siguiente
  a = 1
  b = 1e-8
  fit [LO:HI] f_ob(x)   file(i) using 1:4 via a
  fit [LO:HI] f_time(x) file(i) using 1:3 via b

  set autoscale y
  set xlabel "Tamaño de la permutación N (elementos)"

  set output "fit_".name(i)."_ob.png"
  set title sprintf("%s: ajuste de la OB media  (a = %.4f, ajuste en [%d,%d])", label(i), a, LO, HI)
  set ylabel "Ejecuciones medias de la OB (comparaciones)"
  plot file(i) using 1:4 with points pt 7 title "Datos medidos", \
       f_ob(x) with lines lw 2 lt rgb "red" title "a*n*ln(n)"

  set output "fit_".name(i)."_time.png"
  set title sprintf("%s: ajuste del tiempo medio de CPU  (b = %.3e, ajuste en [%d,%d])", label(i), b, LO, HI)
  set ylabel "Tiempo medio de CPU (s)"
  plot file(i) using 1:3 with points pt 7 title "Datos medidos", \
       f_time(x) with lines lw 2 lt rgb "red" title "b*n*ln(n)"
}