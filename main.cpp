#include "mazeCreator.hpp"

int main()
{
	DepthFirstMaze maze;
	maze.resize(29, 29);
	maze.create();
	maze.dumpFile();
	return 0;
}
