all: project.x timer figures

timer: pruebatimers.cpp
	g++ -fconcepts -Wall -fsanitize=undefined -fsanitize=address $^ -o timer.x -lgsl -lgslcblas

%.o: %.cpp
	g++ -c $< -o $@

project.x: project.o main_project.o
	g++ -fconcepts -std=c++11 -fsanitize=address -fsanitize=undefined $^ -o $@ -lgsl -lgslcblas -O3

figures: probperc.pg probpercred.gp cantclus.gp plottimers.gp plot2.128_0.570000_10.pg plot2.128_0.580000_10.pg plot2.128_0.590000_10.pg plot2.128_0.600000_10.pg plot2.512_0.550000_11.pg plot2.512_0.550000_9.pg 
	gnuplot $^

test: main_project.o project_test.o
	g++ -std=c++11 -Wall -fsanitize=address -fsanitize=undefined $^ -o project_test.o -lgsl -lgslcblas

valgrind: main_project.x
	valgrind --tool=memcheck --leak-check=yes ./main_project.x

clean:
	-rm -f *~ *# *o *out *x 
 s: 
