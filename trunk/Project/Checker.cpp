#include "Checker.h"
#include <iostream>

using namespace std;

Checker::Checker(int aSize) {
	initBoard(aSize);
}

int Checker::getSize() {
	return mSize;
}

int Checker::getTurn() {
	return mTurn;
}

bool Checker::nextTurn() {
	mTurn = (mTurn+1) % 2;
	for(int i=0;i<mSize;i++) {
		for(int j=0;j<mSize;j++) {
			if(getTile(i,j)->isCoinInTile() && getTile(i,j)->getColor()==mTurn && getWalkableFromCoinInTile(i,j).size() > 0) {
				return true;
			}
		}
	}
	return false;
}

void Checker::initBoard(int aSize) {
	mTurn = 1;//yang jalan duluan adalah yang di bawah papan
	if(aSize!=8 && aSize!=10) {
		return ;
	}
	mSize = aSize;
	
	for(int i=0;i<mSize;i++) {
		for(int j=0;j<mSize;j++) {
			mBoard[i][j]=new Tile();
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
				if(getTile(i,j)->getStatus()==Tile::KING) {
					cout<<getTile(i,j)->getColor()+2;
				}else{
					cout<<getTile(i,j)->getColor();
				}
			}else{
				cout<<" ";
			}
		}
		cout<<endl;
	}
}

Tile* Checker::getTile(int aRow,int aCol) {
	return mBoard[aRow][aCol];
}

vector<Point> Checker::getWalkableFromCoinInTile(int aRow, int aCol) {
	vector<Point> arrPoint;
	if(!getTile(aRow,aCol)->isCoinInTile()) {
		return arrPoint;
	}
	Tile* aCoin = getTile(aRow,aCol);
	Point p;
	if((aCoin->getColor()==1 || aCoin->getStatus()==Tile::KING)) {
		if(aRow>0 && aCol>0 && !getTile(aRow-1,aCol-1)->isCoinInTile()) {
			p.row = aRow-1;p.col = aCol-1;
			arrPoint.push_back(p);
		}else if(aRow>0 && aCol>0 && getTile(aRow-1,aCol-1)->isCoinInTile() && getTile(aRow-1,aCol-1)->getColor()!=aCoin->getColor() && aRow-2>=0 && aCol-2>=0 && !getTile(aRow-2,aCol-2)->isCoinInTile()) {
			p.row = aRow-2;p.col = aCol-2;
			arrPoint.push_back(p);
		}
		if(aRow>0 && aCol+1<mSize && !getTile(aRow-1,aCol+1)->isCoinInTile()) {
			p.row =aRow-1;p.col=aCol+1;
			arrPoint.push_back(p);
		}else if(aRow>0 && aCol+1<mSize && getTile(aRow-1,aCol+1)->isCoinInTile() && getTile(aRow-1,aCol+1)->getColor()!=aCoin->getColor() && aRow-2>=0 && aCol+2<mSize && !getTile(aRow-2,aCol+2)->isCoinInTile()) {
			p.row = aRow-2;p.col=aCol+2;
			arrPoint.push_back(p);
		}
	}
	if(aCoin->getColor()==0 || aCoin->getStatus()==Tile::KING) {
		if(aRow<mSize-1 && aCol>0 && !getTile(aRow+1,aCol-1)->isCoinInTile()) {
			p.row =aRow+1;p.col=aCol-1;
			arrPoint.push_back(p);
		}else if(aRow<mSize-1 && aCol>0 && getTile(aRow+1,aCol-1)->isCoinInTile() && getTile(aRow+1,aCol-1)->getColor()!=aCoin->getColor() && !getTile(aRow+2,aCol-2)->isCoinInTile()) {
			p.row =aRow+2;p.col=aCol-2;
			arrPoint.push_back(p);
		}
		if(aRow<mSize-1 && aCol+1<mSize && !getTile(aRow+1,aCol+1)->isCoinInTile()) {
			p.row =aRow+1;p.col=aCol+1;
			arrPoint.push_back(p);
		}else if(aRow<mSize-1 && aCol+1<mSize && getTile(aRow+1,aCol+1)->isCoinInTile() && getTile(aRow+1,aCol+1)->getColor()!=aCoin->getColor() && aRow-2>=0 && aCol+2<mSize && !getTile(aRow+2,aCol+2)->isCoinInTile()) {
			p.row =aRow+2;p.col=aCol+2;
			arrPoint.push_back(p);
		}
	}
	return arrPoint;
}

void Checker::greedyMove() {
	
}

int main() {
	int row1,col1,row2,col2;
	Checker c(10);
	c.printBoard();
	do {
		cout<<"giliran pemain : "<<c.getTurn()<<endl;
		cout<<"masukkan koin di petak yang mana dan ke petak yang mana : ";
		cin>>row1>>col1>>row2>>col2;
	}while(c.nextTurn());
	return 0;
}

