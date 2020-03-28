all: Eulercons.x Eulercons.txt graficaEulerCons.pdf

Eulercons.x: Eulerconstant.cpp
	g++ Eulerconstant.cpp -o Eulercons.x

Eulercons.txt: Eulercons.x
	./Eulercons.x > Eulercons.txt

graficaEulerCons.pdf: Eulercons.txt plotfigure.gp
	gnuplot plotfigure.gp

clean:
	rm -f Eulercons.txt Eulercons.x
