all:
	g++ -c main.cpp utils.cpp h-cg.cpp h-agm.cpp bl.cpp bl-tabu.cpp
	g++ -o main main.o utils.o h-cg.o h-agm.o bl.o bl-tabu.o -O2 -std=c++14