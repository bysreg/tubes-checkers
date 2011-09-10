#ifndef TILE_H
#define TILE_H

class Tile {
private:
	int mColor;//0 atau 1. Yang jalan duluan 0
	int mStatus;//0 orang biasa, 1 raja
	bool mIsThereCoin;//apakah disini ada koin
public:
	static const int KING;
	static const int PION;
	
	Tile();
	int getColor();
	void setColor(int);
	int getStatus();
	void setStatus(int);
	bool isCoinInTile();
	void setCoin(int,int);
	void removeCoin();
};
#endif
