#ifndef TILE_H
#define TILE_H

class Tile {
private:
	int mRow;
	int mCol;
	int mColor;//0 atau 1. Yang jalan duluan 0
	int mStatus;//0 orang biasa, 1 raja
	bool mIsThereCoin;//apakah disini ada koin
	
public:
	bool test;
	Tile(int,int);
	int getRow();
	void setRow(int);
	int getCol();
	void setCol(int);
	int getColor();
	void setColor(int);
	int getStatus();
	void setStatus(int);
	bool isCoinInTile();
	void setCoin(int,int);
};
#endif
