#include "mazeCreator.hpp"

int main()
{
	DepthFirstMaze maze;
	maze.create();
	maze.dumpMazeFile();
	return 0;
}
