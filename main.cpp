#include "mazeCreator.hpp"

#include <string>
#include <iostream>

int main(int argc, char** argv)
{
	DFSMaze maze;

    switch (argc) {
        case 1:
	        maze.resize(29, 29);
            break;
        case 3:
            try {
                int w = std::stoi(argv[1]);
                int h = std::stoi(argv[2]);
                maze.resize(w / 2 * 2 + 1, h / 2 * 2 + 1);
            } catch(std::exception) {
                std::cout << "Arguments should be integers" << std::endl;
                return 1;
            }
            break;
        default:
            std::cout << "Wrong number of args" << std::endl;
            std::cout << argv[0] << "[width height]" << std::endl;

            return 1;
    }

	maze.create();
	maze.dumpFile();

    std::cout << "Done" << std::endl;

	return 0;
}
