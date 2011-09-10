#ifndef CHECKER_H
#define CHECKER_H
#include <vector>

#ifndef TILE_H
#include "Tile.h"
#endif

#ifndef POINT_H
#include "Point.h"
#endif

class Checker {

private:
	int mSize;
	Tile* mBoard[10][10];
	int mTurn;
	
public:
	Checker(int);
	int getSize();
	int getTurn();
	bool nextTurn();
	void initBoard(int);
	void printBoard();
	Tile* getTile(int,int);
	std::vector<Point> getWalkableFromCoinInTile(int,int);
	bool isCoinAllowedToMove(int,int,int,int);
	bool moveCoin(int,int,int,int);
	void greedyMove();
};

#endif

