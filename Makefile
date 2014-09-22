default:
	g++ -c mazeCreator.cpp
	g++ -c main.cpp
	g++ main.o mazeCreator.o -o mazeGenerator
