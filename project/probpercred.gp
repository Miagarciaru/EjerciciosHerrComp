set term pngcairo size 1280, 960	
set out 'ProbabilidadP(p,L)r.png'
set title "Probabilidad de Percolación en función de la probabilidad de llenado p para L=32, 64, 128, 256, 512" font "Arial, 20"
set key box
set xlabel 'Probabilidad de llenado p' font "Arial, 16"
set ylabel 'Probabilidad P(p, L)' font "Arial, 16"
set xrange [0.45:0.7]
set yrange [0:1.2]
set key bottom left box #posiciona la tabla del título
set key width 1 #Deja un espacio para el título dentro de la caja
set key font "Arial, 16" #Cambia la fuente del título por Arial y el tamaño por 16
set grid
set border 3 #Elimina los bordes de arriba y a la derecha
set tics nomirror #Elimina los puntos de los ejes arriba y derecha
set border lw 2 #Aumenta el grosor de los ejes
plot  "<(sed -n '2, 30p' stats_full.txt)" u 2:5:6 title "P(p,32)" lt 7 lc 0 with errorbars, "<(sed -n '2, 30p' stats_full.txt)" u 2:5 title "Modelo P(p, 32)" lt 7 lc 0 w l, "<(sed -n '31, 59p' stats_full.txt)" u 2:5:6 title "P(p,64)" lt 7 lc 1 with errorbars, "<(sed -n '31, 56p' stats_full.txt)" u 2:5 title "Modelo P(p, 64)" lt 7 lc 1 w l, "<(sed -n '60, 88p' stats_full.txt)" u 2:5:6 title "P(p,128)" lt 7 lc 2 with errorbars, "<(sed -n '60, 88p' stats_full.txt)" u 2:5 title "Modelo P(p, 128)" lt 7 lc 2 w l, "<(sed -n '89, 117p' stats_full.txt)" u 2:5:6 title "P(p,256)" lt 7 lc 3 with errorbars, "<(sed -n '89, 117p' stats_full.txt)" u 2:5 title "Modelo P(p, 256)" lt 7 lc 3 w l, "<(sed -n '118, 146p' stats_full.txt)" u 2:5:6 title "P(p,512)" lt 7 lc 4 with errorbars, "<(sed -n '118, 146p' stats_full.txt)" u 2:5 title "Modelo P(p, 512)" lt 7 lc 4 w l  