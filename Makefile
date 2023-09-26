main:
	clear
	g++-12 -o main.o main.cpp graph.cpp two_opt.cpp genetic_algorithm.cpp generate_tour.cpp

input: main
	./main.o < test/input.in

berlin52: main
	./main.o < test/input2.in

pr439: main
	./main.o < test/input3.in

remove_files:
	rm *.o

clear: remove_files
	clear