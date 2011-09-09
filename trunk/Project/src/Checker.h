#ifndef CHECKER_H
#define CHECKER_H
#include "Tile.h"
class Checker {
private:
	int mSize;
	Tile* mBoard[10][10];
	
public:
	Checker(int);
	void greedyMove();
	void initBoard(int);
	void printBoard();
	Tile* getTile(int,int);
};

#endif

