

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
	bool isCorrect(int mx, int my);
	Pointer getNextInDirection(Direction d);
};

class BaseMaze
{
protected:
	int m_x;
	int m_y;
	Pointer m_start;
	Pointer m_end;
	bool** m_maze;
public:
	BaseMaze();
	~BaseMaze();
	bool** get();
	bool get(Pointer p);
	void reset();
	Pointer getStart();
	Pointer getEnd();
	void resize(int x, int y);
	bool dumpFile();
	bool dumpFile(char* fileName);
	virtual void create();
protected:
	virtual void setStartPointer();
	virtual void make() = 0;
	void initBoard();
	void deleteBoard();
};

class DFSMaze
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
