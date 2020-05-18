set term pngcairo size 1280, 960	
set out 'Optimizaciontiempo.png'
set title "Optimización del programa para dos niveles" font "Arial, 20"
set key box
set ylabel 'Optimización en tiempo (adimensional)' font "Arial, 16"
set xlabel 'Tamaño de la matriz L' font "Arial, 16"
set yrange [0:1.2]
#set key bottom left box #posiciona la tabla del título
set key width 1 #Deja un espacio para el título dentro de la caja
set key font "Arial, 16" #Cambia la fuente del título por Arial y el tamaño por 16
set grid
set border 3 #Elimina los bordes de arriba y a la derecha
set tics nomirror #Elimina los puntos de los ejes arriba y derecha
set border lw 2 #Aumenta el grosor de los ejes
plot  "<(sed -n '2, 6p' timerresult.txt)" u 1:2 title "Nivel 1 Optimización" lt 7 lc 0 w l, "<(sed -n '2, 6p' timerresult.txt)" u 1:3 title "Nivel 3 Optimización" lt 7 lc 1 w l