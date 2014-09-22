

#ifndef _MAZE_CREATOR_
#define _MAZE_CREATOR_

#include <stdlib.h>
#include <time.h>

#include <iostream>
#include <fstream>
#include <vector>

#define MX 21
#define MY 29

#define MWALL	"[]"
#define MWAY	"  "
#define MSTART	"SS"
#define MEND	"EE"

#define maze(p) m_maze[p.x][p.y]

struct Pointer;

enum Direction {
	D_LEFT,
	D_RIGHT,
	D_UP,
	D_DOWN,
	LAST_D
};

struct Pointer
{
	int x;
	int y;
public:
	bool operator==(const Pointer& right);
	bool operator!=(const Pointer& right);
	bool isCorrect();
	Pointer getNextInDirection(Direction d);
};

class BaseMaze
{
protected:
	Pointer m_start;
	Pointer m_end;
	bool m_maze[MX][MY];
	std::ofstream outFile;
	char* outFileName;
public:
	BaseMaze();
	void reset();
	Pointer getStart();
	Pointer getEnd();
	bool dumpMazeFile();
	bool dumpMazeFile(char* fileName);
	virtual void create();
protected:
	virtual void setStartPointer();
	virtual void make() = 0;
};

class DepthFirstMaze
	: public BaseMaze
{
	Pointer m_current;
	std::vector<Pointer> m_path;
private:
	bool getStatForPropagation(Direction d);
	Direction randomDirection();
	void make();
};

#endif
