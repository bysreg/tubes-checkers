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

vector<GamePoint> Checker::getWalkableFromCoinInTile(int aRow, int aCol) {
	vector<GamePoint> arrGamePoint;
	if(!getTile(aRow,aCol)->isCoinInTile()) {
		return arrGamePoint;
	}
	Tile* aCoin = getTile(aRow,aCol);
	GamePoint p;
	if((aCoin->getColor()==1 || aCoin->getStatus()==Tile::KING)) {
		if(aRow>0 && aCol>0 && !getTile(aRow-1,aCol-1)->isCoinInTile()) {
			p.row = aRow-1;p.col = aCol-1;
			arrGamePoint.push_back(p);
		}else if(aRow>0 && aCol>0 && getTile(aRow-1,aCol-1)->isCoinInTile() && getTile(aRow-1,aCol-1)->getColor()!=aCoin->getColor() && aRow-2>=0 && aCol-2>=0 && !getTile(aRow-2,aCol-2)->isCoinInTile()) {
			p.row = aRow-2;p.col = aCol-2;
			arrGamePoint.push_back(p);
		}
		if(aRow>0 && aCol+1<mSize && !getTile(aRow-1,aCol+1)->isCoinInTile()) {
			p.row =aRow-1;p.col=aCol+1;
			arrGamePoint.push_back(p);
		}else if(aRow>0 && aCol+1<mSize && getTile(aRow-1,aCol+1)->isCoinInTile() && getTile(aRow-1,aCol+1)->getColor()!=aCoin->getColor() && aRow-2>=0 && aCol+2<mSize && !getTile(aRow-2,aCol+2)->isCoinInTile()) {
			p.row = aRow-2;p.col=aCol+2;
			arrGamePoint.push_back(p);
		}
	}
	if(aCoin->getColor()==0 || aCoin->getStatus()==Tile::KING) {
		if(aRow<mSize-1 && aCol>0 && !getTile(aRow+1,aCol-1)->isCoinInTile()) {
			p.row =aRow+1;p.col=aCol-1;
			arrGamePoint.push_back(p);
		}else if(aRow<mSize-1 && aCol>0 && getTile(aRow+1,aCol-1)->isCoinInTile() && getTile(aRow+1,aCol-1)->getColor()!=aCoin->getColor() && !getTile(aRow+2,aCol-2)->isCoinInTile()) {
			p.row =aRow+2;p.col=aCol-2;
			arrGamePoint.push_back(p);
		}
		if(aRow<mSize-1 && aCol+1<mSize && !getTile(aRow+1,aCol+1)->isCoinInTile()) {
			p.row =aRow+1;p.col=aCol+1;
			arrGamePoint.push_back(p);
		}else if(aRow<mSize-1 && aCol+1<mSize && getTile(aRow+1,aCol+1)->isCoinInTile() && getTile(aRow+1,aCol+1)->getColor()!=aCoin->getColor() && aRow-2>=0 && aCol+2<mSize && !getTile(aRow+2,aCol+2)->isCoinInTile()) {
			p.row =aRow+2;p.col=aCol+2;
			arrGamePoint.push_back(p);
		}
	}
	return arrGamePoint;
}

bool Checker::isCoinAllowedToMove(int row1,int col1,int row2,int col2) {
	GamePoint p1;p1.row = row1;p1.col=col1;
	GamePoint p2;p2.row = row2;p2.col=col2;
	vector<GamePoint> arrGamePoint = getWalkableFromCoinInTile(p1.row,p1.col);
	for(int i=0;i<arrGamePoint.size();i++) {
		if(p2.row==arrGamePoint[i].row && p2.col==arrGamePoint[i].col) {
			return true;
		}
	}
	return false;
}

//pemain(bisa manusia atau AI) memindahkan koin dari satu titik ke titik lain
//ada pengecekan apakah perpindahan itu legal
bool Checker::moveCoin(int row1,int col1,int row2,int col2) {
	GamePoint p1;p1.row = row1;p1.col = col1;
	GamePoint p2;p2.row = row2;p2.col = col2;
	//cek apakah di-petak itu ada koin
	if(!getTile(p1.row,p1.col)->isCoinInTile()) {
		return false;
	}
	//jika sekarang bukan giliran dia jalan
	if(getTile(p1.row,p1.col)->getColor()!=getTurn()) {
		return false;
	}
	Tile* aCoin = getTile(p1.row,p1.col);
	//cek apakah koin di petak itu bisa pindah ke titik p2?
	if(!isCoinAllowedToMove(p1.row,p1.col,p2.row,p2.col)) {
		return false;
	}
	//pindahin dari p1 ke p2
	aCoin->removeCoin();
	getTile(p2.row,p2.col)->setCoin(aCoin->getColor(),aCoin->getStatus());
	return true;
}

void Checker::greedyMove() {
	
}

int main() {
	int row1,col1,row2,col2;
	Checker c(10);
	GamePoint p;
	do {
		c.printBoard();
		cout<<"giliran pemain : "<<c.getTurn()<<endl;
			cout<<"masukkan koin di petak yang mana dan ke petak yang mana : ";
			cin>>row1>>col1>>row2>>col2;
			while(!c.moveCoin(row1,col1,row2,col2)) {
				cout<<"illegal move!"<<endl;
				cout<<"masukkan koin di petak yang mana dan ke petak yang mana : ";
				cin>>row1>>col1>>row2>>col2;
			}
	}while(c.nextTurn());
	return 0;
}

