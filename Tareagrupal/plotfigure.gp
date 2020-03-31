set term pdf
set output 'grafica.pdf'
set xlabel 'X dado'
set ylabel 'X reducido al intervalo requerido'
set title 'Reducción del dominio de x'
unset key
plot 'datos.txt' u 1:2 lc 9 w l