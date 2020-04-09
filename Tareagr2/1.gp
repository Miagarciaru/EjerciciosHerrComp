set term pdf
set out '1.pdf'
set xlabel 'Número de precisión n bit'
set ylabel 'Error relativo de función arctan'
set log y
plot 'datos.txt' w lp lw 2 pt 5 ps 3