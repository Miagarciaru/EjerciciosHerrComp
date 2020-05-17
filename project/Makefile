all: project.o main_project.o main_project.x

project.o: project.cpp
	g++ -c $^ -o $@

main_project.o: main_project.cpp
	g++ -c $^ -o $@

main_project.x: project.o main_project.o
	g++ -std=c++11 -Wall -fsanitize=address -fsanitize=undefined $^ -o $@ -lgsl -lgslcblas

clean:
	-rm -f *~ *# *o *out *x *txt
