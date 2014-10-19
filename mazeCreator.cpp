#include "mazeCreator.hpp"


bool Pointer::operator==(const Pointer& right)
{
	return (x == right.x && y == right.y);
}

bool Pointer::operator!=(const Pointer& right)
{
	return (x != right.x || y != right.y);
}

Pointer Pointer::getNextInDirection(Direction d)
{
	Pointer p;
	p.x = x;
	p.y = y;
	switch (d) {
		case D_LEFT:
			p.x--;
		break;
		case D_RIGHT:
			p.x++;
		break;
		case D_UP:
			p.y++;
		break;
		case D_DOWN:
			p.y--;
		default:
		break;
	}
	return p;
}

bool Pointer::isCorrect(int mx, int my)
{
	return (x >= 0 && x < mx && y >= 0 && y < my);
}

//////////////////////////////////////////////////////////////////////////////////

BaseMaze::BaseMaze() :
	m_x(MX),
	m_y(MY)
{
	initBoard();
	srand(time(NULL));
}

BaseMaze::~BaseMaze()
{
	deleteBoard();
}

bool** BaseMaze::get()
{
	return m_maze;
}

bool BaseMaze::get(Pointer p)
{
	return maze(p);
}

void BaseMaze::reset()
{
	for (int x = 0; x < m_x; ++x){
		for (int y = 0; y < m_y; ++y){
			m_maze[x][y] = true;
		}
	}
}

void BaseMaze::initBoard()
{
	m_maze = new bool*[m_x];
	for (int i = 0; i < m_x; ++i) {
		m_maze[i] = new bool[m_y];
	}
	reset();
}

void BaseMaze::deleteBoard()
{
	for (int i = 0; i < m_x; ++i) {
		delete [] m_maze[i];
	}
	delete [] m_maze;
}

Pointer BaseMaze::getStart()
{
	return m_start;
}

Pointer BaseMaze::getEnd()
{
	return m_end;
}

void BaseMaze::resize(int x, int y){
	deleteBoard();
	m_x = x;
	m_y = y;
	initBoard();
}

bool BaseMaze::dumpFile(char* fileName)
{
	std::ofstream outFile;
	outFile.open(fileName);
	if (outFile.is_open()) {
		Pointer p;
		for (int i = 0; i < m_x + 2; ++i) {
			outFile << MWALL;
		}
		outFile << "\n" << MWALL;
		for (p.y = m_y - 1; p.y >= 0; --p.y) {
			for (p.x = 0; p.x < m_x; ++p.x) {
				if (maze(p) && p.isCorrect(m_x, m_y)) {
					outFile << MWALL;
				} else if (p == m_start) {
					outFile << MSTART;
				} else if (p == m_end) {
					outFile << MEND;
				} else {
					outFile << MWAY;
				}
			}
			outFile << MWALL << "\n" << MWALL;
		}
		for (int i = 0; i < m_x + 1; ++i) {
			outFile << MWALL;
		}
		outFile.close();
		return true;
	} else {
		return false;
	}
}

bool BaseMaze::dumpFile(){
	return dumpFile((char*)"maze.txt");
}

void BaseMaze::create()
{
	reset();
	make();
}

void BaseMaze::setStartPointer()
{
	int dir = rand() % 4;
	switch (dir){
		case 0:
			m_start.x = 0;
			m_start.y = double(rand() % m_y/2)*2;
		break;
		case 1:
			m_start.x = double(rand() % m_x/2)*2;
			m_start.y = 0;
		break;
		case 2:
			m_start.x = m_x - 1;
			m_start.y = double(rand() % m_y/2)*2;
		break;
		case 3:
			m_start.x = double(rand() % m_x/2)*2;
			m_start.y = m_y - 1;
	}
	//std::cout << m_start.x << " " << m_start.y << std::endl; // test //
}

/////////////////////////////////////////////////////////////////////////////////

bool DFSMaze::getStatForPropagation(Direction d)
{
	return ((
		 m_current.getNextInDirection(d).getNextInDirection(d).isCorrect(m_x, m_y)
		 && maze(m_current.getNextInDirection(d).getNextInDirection(d))
		));
}

Direction DFSMaze::randomDirection()
{
	std::vector<Direction> existDirs;
	if (getStatForPropagation(D_LEFT)) {
		existDirs.push_back(D_LEFT);
	}
	if (getStatForPropagation(D_RIGHT)) {
		existDirs.push_back(D_RIGHT);
	}
	if (getStatForPropagation(D_UP)) {
		existDirs.push_back(D_UP);
	}
	if (getStatForPropagation(D_DOWN)) {
		existDirs.push_back(D_DOWN);
	}
	if (existDirs.size()) {
		return existDirs[rand() % existDirs.size()];
	}  else {
		return LAST_D;
	}
}

void DFSMaze::make()
{
	setStartPointer();
	Direction d;
	maze(m_start) = false;
	int maxLength = 0;
	m_current = m_start;
	do
	{
		d = randomDirection();
		if (d != LAST_D /*&& getStatForPropagation(d)*/) {
			maze(m_current.getNextInDirection(d)) = false;
			m_current = m_current.getNextInDirection(d).getNextInDirection(d);
			maze(m_current) = false;
			m_path.push_back(m_current);
			//std::cout << m_current.x << " " << m_current.y << std::endl; // test //
		} else {
			m_current = m_path.back();
			m_path.pop_back();
		}
		if(maxLength < static_cast<int>(m_path.size()) 
		   && (
		       m_path.back().x == 0
		       || m_path.back().x == m_x - 1
		       || m_path.back().y == m_y - 1
		       || m_path.back().y == 0
		      )){
			m_end = m_path.back();
			maxLength = m_path.size();
		}
	}
	while(m_path.size());
}
