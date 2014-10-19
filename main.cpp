#include "mazeCreator.hpp"

int main()
{
	DFSMaze maze;
	maze.resize(29, 29);
	maze.create();
	maze.dumpFile();
	return 0;
}
