set term pngcairo size 1280, 960	
set out 'Energy.png'
set key
set xlabel 'Tamaño de la red L' font "Arial, 16"
set ylabel 'Probabilidad P(p, L)' font "Arial, 16"
#set yrange [0:8e15]
#set key bottom left box #posiciona la tabla del título
set key width 1 #Deja un espacio para el título dentro de la caja
set key font "Arial, 16" #Cambia la fuente del título por Arial y el tamaño por 16
set border 3 #Elimina los bordes de arriba y a la derecha
set tics nomirror #Elimina los puntos de los ejes arriba y derecha
#unset xtics #elimina la escala en el eje x
set border lw 2 #Aumenta el grosor de los ejes
#set key at 3.0,6.2e15 #posiciona el título en la posición x=3 y=6.5e15