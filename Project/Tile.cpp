#include "Tile.h"
#include <iostream>

using namespace std;

Tile::Tile(int aRow, int aCol) {
	mRow=aRow;
	mCol=aCol;
	mColor=0;
	mStatus=0;
	mIsThereCoin=false;
}

int Tile::getRow() {
	return mRow;
}

void Tile::setRow(int aRow) {
	mRow = aRow;
}

int Tile::getCol() {
	return mCol;
}

void Tile::setCol(int aCol) {
	mCol = aCol;
}

int Tile::getColor() {
	return mColor;
}

void Tile::setColor(int aColor) {
	mColor = aColor;
}

int Tile::getStatus() {
	return mStatus;
}

void Tile::setStatus(int aStatus) {
	mStatus = aStatus;
}

bool Tile::isCoinInTile() {
	//return true;
	return mIsThereCoin;
}

void Tile::setCoin(int aColor,int aStatus) {
	mColor = aColor;
	mStatus = aStatus;
	mIsThereCoin = true;
	//cout<<mRow<<" "<<mCol<<" "<<mIsThereCoin<<endl;
}
