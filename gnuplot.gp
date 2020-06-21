set pm3d
set contour
set term pdfcairo size 1280, 960
set output 'Laplace-boundary-circle.png'
splot 'datos.txt' w pm3d