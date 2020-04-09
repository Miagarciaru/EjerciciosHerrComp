all: 1.x datos.txt 1.pdf

1.x: 1.cpp
	g++ -fsanitize=undefined -fsanitize=address 1.cpp -o 1.x

datos.txt: 1.x
	./1.x > datos.txt

1.pdf: datos.txt 1.gp
	gnuplot 1.gp

clean:
	datos.txt 1.x 1.pdf
