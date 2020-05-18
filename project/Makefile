all: project.o main1.o main1.x plot1.png plot2.png

project.o: project.cpp
	g++ -c $^ -o $@

main1.o: main1.cpp
	g++ -c $^ -o $@

main1.x: project.o main1.o
	g++ -std=c++11 -Wall -fsanitize=address -fsanitize=undefined $^ -o $@ -lgsl -lgslcblas

project_test: project_test.cpp
	g++ -c $^ -o $@ 

plot1.png: plot1.gp
	gnuplot plot1.gp

plot2.png: plotfigure.gp
	gnuplot plotfigure.gp

test: main_project.o project_test.o
	g++ -std=c++11 -Wall -fsanitize=address -fsanitize=undefined $^ -o project_test.o -lgsl -lgslcblas

valgrind: main1.x
	valgrind --tool=memcheck --leak-check=yes ./main_project.x

clean:
	-rm -f *~ *# *o *out *x *txt
