#include "Checker.h"
#include <iostream>

using namespace std;

Checker::Checker(int aSize) {
	initBoard(aSize);
}

void Checker::initBoard(int aSize) {
	if(aSize!=8 && aSize!=10) {
		return ;
	}
	mSize = aSize;
	
	for(int i=0;i<mSize;i++) {
		for(int j=0;j<mSize;j++) {
			mBoard[i][j]=new Tile(i,j);
			if(i%2==j%2 || i==mSize/2-1 || i==mSize/2) {
				continue;
			}
			if(i<mSize/2) {
				getTile(i,j)->setCoin(0,0);
			}else {
				getTile(i,j)->setCoin(1,0);
			}
		}
	}
}

void Checker::printBoard() {
	for(int i=0;i<mSize;i++) {
		for(int j=0;j<mSize;j++) {
			if(getTile(i,j)->isCoinInTile()) {
				cout<<getTile(i,j)->getColor();
			}
			cout<<" ";
		}
		cout<<endl;
	}
}

Tile* Checker::getTile(int aRow,int aCol) {
	return mBoard[aRow][aCol];
}

void Checker::greedyMove() {
	
}

int main() {
	Checker c(10);
	c.printBoard();
	return 0;
}

