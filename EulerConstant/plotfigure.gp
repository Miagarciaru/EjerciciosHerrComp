set term pdf
set output 'EulerConstant.pdf'
set xlabel 'Número de pasos n'
set ylabel 'Valor de la constante de Euler'
set title 'Calculo de la constante de Euler por iteración'
unset key
plot 'Eulercons.txt' u 1:2 lc 9 w l
