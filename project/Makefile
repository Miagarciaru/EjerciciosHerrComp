all: project.o main_project.o main_project.x

project.o: project.cpp
	g++ -c $^ -o $@

main_project.o: main_project.cpp
	g++ -c $^ -o $@

main_project.x: project.o main_project.o
	g++ -fsanitize=address -fsanitize=undefined $< -o $@

clean:
	-rm -f *~ *# *o *out *x
