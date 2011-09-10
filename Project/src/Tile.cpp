#include "Tile.h"
#include <iostream>

using namespace std;

int const Tile::KING = 1;
int const Tile::PION = 0;

Tile::Tile() {
	mColor=0;
	mStatus=0;
	mIsThereCoin=false;
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
	return mIsThereCoin;
}

void Tile::setCoin(int aColor,int aStatus) {
	mColor = aColor;
	mStatus = aStatus;
	mIsThereCoin = true;
}

void Tile::removeCoin() {
	mIsThereCoin = false;
}

