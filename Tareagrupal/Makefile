all: 1.x datos.txt grafica.pdf

1.x: 1.cpp
	g++ -fsanitize=undefined 1.cpp -o 1.x

datos.txt: 1.x
	./1.x > datos.txt

grafica.pdf: datos.txt plotfigure.gp
	gnuplot plotfigure.gp

clean:
	datos.txt 1.x grafica.pdf
