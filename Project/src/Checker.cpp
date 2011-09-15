#include "Checker.h"
#include <iostream>
#include <cmath>

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
	return false;//pemain ini kalah
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

//mengambil petak mana aja yang bisa koin tersebut bisa jalan
//sudah memperhitungkan di petak tersebut ada koin atau tidak
//sudah memperhitungkan si pemain harus makan atau tidak
vector<GamePoint> Checker::getWalkableFromCoinInTile(int aRow, int aCol) {
	vector<GamePoint> arrGamePoint;
	if(!getTile(aRow,aCol)->isCoinInTile() || getTile(aRow,aCol)->getColor()!=getTurn()) {
		return arrGamePoint;
	}
	Tile* aCoin = getTile(aRow,aCol);
	GamePoint p;
	bool mustEat = isThereEatable();
	if((aCoin->getColor()==1 || aCoin->getStatus()==Tile::KING)) {
		//atas kiri makan
		if(aRow>0 && aCol>0 && getTile(aRow-1,aCol-1)->isCoinInTile() && getTile(aRow-1,aCol-1)->getColor()!=aCoin->getColor() && aRow-2>=0 && aCol-2>=0 && !getTile(aRow-2,aCol-2)->isCoinInTile()) {
			p.row = aRow-2;p.col = aCol-2;
			arrGamePoint.push_back(p);
		}
		//atas kanan makan
		if(aRow>0 && aCol+1<mSize && getTile(aRow-1,aCol+1)->isCoinInTile() && getTile(aRow-1,aCol+1)->getColor()!=aCoin->getColor() && aRow-2>=0 && aCol+2<mSize && !getTile(aRow-2,aCol+2)->isCoinInTile()) {
			p.row = aRow-2;p.col=aCol+2;
			arrGamePoint.push_back(p);
		}
		//atas kiri
		if(!mustEat && aRow>0 && aCol>0 && !getTile(aRow-1,aCol-1)->isCoinInTile()) {
			p.row = aRow-1;p.col = aCol-1;
			arrGamePoint.push_back(p);
		}
		//atas kanan
		if(!mustEat && aRow>0 && aCol+1<mSize && !getTile(aRow-1,aCol+1)->isCoinInTile()) {
			p.row =aRow-1;p.col=aCol+1;
			arrGamePoint.push_back(p);
		} 
	}
	if(aCoin->getColor()==0 || aCoin->getStatus()==Tile::KING) {
		//bawah kanan makan
		if(aRow<mSize-1 && aCol>0 && getTile(aRow+1,aCol-1)->isCoinInTile() && getTile(aRow+1,aCol-1)->getColor()!=aCoin->getColor() && aRow+2<mSize && aCol-2>=0 && !getTile(aRow+2,aCol-2)->isCoinInTile()) {
			p.row =aRow+2;p.col=aCol-2;
			arrGamePoint.push_back(p);			
		}
		//bawah kiri makan
		if(aRow<mSize-1 && aCol+1<mSize && getTile(aRow+1,aCol+1)->isCoinInTile() && getTile(aRow+1,aCol+1)->getColor()!=aCoin->getColor() && aRow+2>=0 && aCol+2<mSize && !getTile(aRow+2,aCol+2)->isCoinInTile()) {
			p.row =aRow+2;p.col=aCol+2;
			arrGamePoint.push_back(p);			
		}
		//bawah kiri
		if(!mustEat && aRow<mSize-1 && aCol>0 && !getTile(aRow+1,aCol-1)->isCoinInTile()) {
			p.row =aRow+1;p.col=aCol-1;
			arrGamePoint.push_back(p);
		} 
		//bawah kanan
		if(!mustEat && aRow<mSize-1 && aCol+1<mSize && !getTile(aRow+1,aCol+1)->isCoinInTile()) {
			p.row =aRow+1;p.col=aCol+1;
			arrGamePoint.push_back(p);
		} 
	}
	return arrGamePoint;
}

vector<GameMove> Checker::getAllLegalMove() {
	vector<GameMove> arrMove;
	for(int i=0;i<mSize;i++) {
		for(int j=0;j<mSize;j++) {
			if(getTile(i,j)->isCoinInTile() && getTile(i,j)->getColor()==getTurn()) {
				vector<GamePoint> arrGamePoint = getWalkableFromCoinInTile(i,j);
				for(int k=0;k<arrGamePoint.size();k++) {
					GameMove m;
					m.from.row = i;
					m.from.col = j;
					m.to.row = arrGamePoint[k].row;
					m.to.col = arrGamePoint[k].col;
					arrMove.push_back(m);
				}
			}
		}
	}
	return arrMove;
}

//mendapatkan jumlah koin yang bisa dimakan koin tersebut(bisa lebih dari 4 karena memperhitungkan koin di langkah2 didepan)
int Checker::countEatable(int aRow, int aCol, int parRow, int parCol) {
    //cek apakah di-petak itu ada koin
	int retval = 0;
	if((getTile(parRow,parCol)->getColor()==1 || getTile(parRow,parCol)->getStatus()==Tile::KING)) {
		//atas kiri makan
        if(aRow>0 && aCol>0 && getTile(aRow-1,aCol-1)->isCoinInTile() && getTile(aRow-1,aCol-1)->getColor()!=getTile(parRow,parCol)->getColor() && aRow-2>=0 && aCol-2>=0 && !getTile(aRow-2,aCol-2)->isCoinInTile() && aRow-2!=parRow && aCol-2!=parCol) {
            retval++;
			retval+=countEatable(aRow-2,aCol-2,aRow,aCol);
        }
        //atas kanan makan
        if(aRow>0 && aCol+1<mSize && getTile(aRow-1,aCol+1)->isCoinInTile() && getTile(aRow-1,aCol+1)->getColor()!=getTile(parRow,parCol)->getColor() && aRow-2>=0 && aCol+2<mSize && !getTile(aRow-2,aCol+2)->isCoinInTile()  && aRow-2!=parRow && aCol+2!=parCol) {
            retval++;
			retval+=countEatable(aRow-2,aCol+2,aRow,aCol); 
        }
	}
	if((getTile(parRow,parCol)->getColor()==0 || getTile(parRow,parCol)->getStatus()==Tile::KING)) {
        //bawah kiri makan
        if(aRow+1<mSize && aCol>0 && getTile(aRow+1,aCol-1)->isCoinInTile() && getTile(aRow+1,aCol-1)->getColor()!=getTile(parRow,parCol)->getColor() && aRow+2<mSize && aCol-2>=0 && !getTile(aRow+2,aCol-2)->isCoinInTile() && aRow+2!=parRow && aCol-2!=parCol) {
            retval++;
			retval+=countEatable(aRow+2,aCol-2,aRow,aCol); 
        }
        
        //bawah kanan makan
        if(aRow+1<mSize && aCol+1<mSize && getTile(aRow+1,aCol+1)->isCoinInTile() && getTile(aRow+1,aCol+1)->getColor()!=getTile(parRow,parCol)->getColor() && aRow+2<mSize && aCol+2<mSize && !getTile(aRow+2,aCol+2)->isCoinInTile() && aRow+2!=parRow && aCol+2!=parCol) {
            retval++;
			retval+=countEatable(aRow+2,aCol+2,aRow,aCol);  
        }
	} 
	return retval;
}

int Checker::countDefense(int aRow, int aCol, int parRow, int parCol) {
	int retval = 0;
	if(getTile(aRow,aCol)->getColor()==0) {
		if(aRow>0 && aCol>0 && aRow-1!=parRow && aCol-1!=parCol && getTile(aRow-1,aCol-1)->isCoinInTile() &&  getTile(aRow-1,aCol-1)->getColor()==0) {
			retval++;
			if(aRow+1<mSize && aCol+1<mSize && getTile(aRow+1,aCol+1)->isCoinInTile() && getTile(aRow+1,aCol+1)->getColor()!=getTile(aRow,aCol)->getColor()) {
				retval++;
			}
		}
		if(aRow>0 && aCol+1<mSize && aRow-1!=parRow && aCol+1!=parCol && getTile(aRow-1,aCol+1)->isCoinInTile() &&  getTile(aRow-1,aCol+1)->getColor()==0) {
			retval++;
			if(aRow+1<mSize && aCol>0 && getTile(aRow+1,aCol-1)->isCoinInTile() &&  getTile(aRow+1,aCol-1)->getColor()!=getTile(aRow,aCol)->getColor()) {
				retval++;
			}
		}
	}
	if(getTile(aRow,aCol)->getColor()==1) {
		if(aRow+1<mSize && aCol>0 && aRow+1!=parRow && aCol-1!=parCol &&  getTile(aRow+1,aCol-1)->isCoinInTile() && getTile(aRow+1,aCol-1)->getColor()==1) {
			retval++;
			if(aRow>0 && aCol+1<mSize && getTile(aRow-1,aCol+1)->isCoinInTile() &&  getTile(aRow-1,aCol+1)->getColor()!=getTile(aRow,aCol)->getColor()) {
				retval++;
			}
		}
		if(aRow+1<mSize && aCol+1<mSize && aRow+1!=parRow && aCol+1!=parCol &&  getTile(aRow+1,aCol+1)->isCoinInTile() &&  getTile(aRow+1,aCol+1)->getColor()==1) {
			retval++;
			if(aRow>0 && aCol>0 && getTile(aRow-1,aCol-1)->isCoinInTile() &&  getTile(aRow-1,aCol-1)->getColor()!=getTile(aRow,aCol)->getColor()) {
				retval++;
			}
		}
	}
	return retval;
}

//arrMove berisi langkah-langkah legal checker
GameMove Checker::selectMove(vector<GameMove> arrMove, int selectType) {
	int maxIndex = 0;
		
	for(int i=1;i<arrMove.size();i++) {
		if (selectType==SELECT_BY_MOST_EAT && countEatable(arrMove[maxIndex].to.row,arrMove[maxIndex].to.col,arrMove[maxIndex].from.row,arrMove[maxIndex].from.col) < countEatable(arrMove[i].to.row,arrMove[i].to.col,arrMove[i].from.row,arrMove[i].from.col)) {
			maxIndex = i;
		}else if(selectType==SELECT_BY_MOST_DEFENSE && countDefense(arrMove[maxIndex].to.row,arrMove[maxIndex].to.col,arrMove[maxIndex].from.row,arrMove[maxIndex].from.col) < countDefense(arrMove[i].to.row,arrMove[i].to.col,arrMove[i].from.row,arrMove[i].from.col)) {
			maxIndex = i;
		}else if(selectType==SELECT_BY_MOST_EAT_AND_DEFENSE && countEatable(arrMove[maxIndex].to.row,arrMove[maxIndex].to.col,arrMove[maxIndex].from.row,arrMove[maxIndex].from.col) + countDefense(arrMove[maxIndex].to.row,arrMove[maxIndex].to.col,arrMove[maxIndex].from.row,arrMove[maxIndex].from.col) < countEatable(arrMove[i].to.row,arrMove[i].to.col,arrMove[i].from.row,arrMove[i].from.col) + countDefense(arrMove[i].to.row,arrMove[i].to.col,arrMove[i].from.row,arrMove[i].from.col)) {
			maxIndex = i;
		}
	}
	
	moveCoin(arrMove[maxIndex].from.row,arrMove[maxIndex].from.col,arrMove[maxIndex].to.row,arrMove[maxIndex].to.col);
	return arrMove[maxIndex];
}

bool Checker::isCoinAllowedToMove(int row1,int col1,int row2,int col2) {
	GamePoint p1;p1.row = row1;p1.col=col1;
	GamePoint p2;p2.row = row2;p2.col=col2;
	//jika tidak ada koin di petak tersebut
	if(!getTile(p1.row,p1.col)->isCoinInTile()) {
		return false;
	}
	//jika sekarang bukan giliran dia jalan
	if(getTile(p1.row,p1.col)->getColor()!=getTurn()) {
		return false;
	}
	//jika pemain giliran sekarang harus makan tapi dia malah gak makan
	if(isThereEatable() && abs(row1-row2)!=2) {
		cout<<"ada koin lawan yang bisa dimakan, anda harus memakan salah satunya"<<endl;
		return false;
	}
	vector<GamePoint> arrGamePoint = getWalkableFromCoinInTile(p1.row,p1.col);
	for(int i=0;i<arrGamePoint.size();i++) {
		if(p2.row==arrGamePoint[i].row && p2.col==arrGamePoint[i].col) {
			return true;
		}
	}
	return false;
}

bool Checker::isEnemyNearbyCoinEatable(int aRow,int aCol) {
	//cek apakah di-petak itu ada koin
	if(!getTile(aRow,aCol)->isCoinInTile()) {
		return false;
	}
	Tile* aCoin = getTile(aRow,aCol);
	//atas kiri makan
	if((aCoin->getColor()==1 || aCoin->getStatus()==Tile::KING)&& aRow>0 && aCol>0 && getTile(aRow-1,aCol-1)->isCoinInTile() && getTile(aRow-1,aCol-1)->getColor()!=aCoin->getColor() && aRow-2>=0 && aCol-2>=0 && !getTile(aRow-2,aCol-2)->isCoinInTile()) {
		return true;
	}
	//atas kanan makan
	if((aCoin->getColor()==1 || aCoin->getStatus()==Tile::KING)&& aRow>0 && aCol+1<mSize && getTile(aRow-1,aCol+1)->isCoinInTile() && getTile(aRow-1,aCol+1)->getColor()!=aCoin->getColor() && aRow-2>=0 && aCol+2<mSize && !getTile(aRow-2,aCol+2)->isCoinInTile()) {
		return true;
	}
	//bawah kiri makan
	if((aCoin->getColor()==0 || aCoin->getStatus()==Tile::KING)&& aRow+1<mSize && aCol>0 && getTile(aRow+1,aCol-1)->isCoinInTile() && getTile(aRow+1,aCol-1)->getColor()!=aCoin->getColor() && aRow+2<mSize && aCol-2>=0 && !getTile(aRow+2,aCol-2)->isCoinInTile()) {
		return true;
	}
	//bawah kanan makan
	if((aCoin->getColor()==0 || aCoin->getStatus()==Tile::KING)&& aRow+1<mSize && aCol+1<mSize && getTile(aRow+1,aCol+1)->isCoinInTile() && getTile(aRow+1,aCol+1)->getColor()!=aCoin->getColor() && aRow+2<mSize && aCol+2<mSize && !getTile(aRow+2,aCol+2)->isCoinInTile()) {
		return true;
	}
	return false;
}

//pemain(bisa manusia atau AI) memindahkan koin dari satu titik ke titik lain
//ada mekanisme lompat dan TIDAK ada pengecekan sebelom jalan
bool Checker::moveCoin(int row1,int col1,int row2,int col2) {
	GamePoint p1;p1.row = row1;p1.col = col1;
	GamePoint p2;p2.row = row2;p2.col = col2;
	Tile* aCoin = getTile(p1.row,p1.col);
	//pindahin dari p1 ke p2
	aCoin->removeCoin();
	getTile(p2.row,p2.col)->setCoin(aCoin->getColor(),aCoin->getStatus());
	//jika pindah dua baris, berarti si coin memakan suatu coin lain
	if(p1.row-p2.row>1) {
		if(p1.col-p2.col>1) {
			getTile(p1.row-1,p1.col-1)->removeCoin();
		}else if(p2.col-p1.col>1) {
			getTile(p1.row-1,p1.col+1)->removeCoin();
		}
	}else if(p2.row-p1.row>1) {
		if(p2.col-p1.col>1) {
			getTile(p1.row+1,p1.col+1)->removeCoin();
		}else if(p1.col-p2.col>1) {
			getTile(p1.row+1,p1.col-1)->removeCoin();
		}
	}
	//jika setelah dipindahkan, koin berada di baris paling jauh board dari si pemain yang punya koin tersebut, jadikan raja
	if((getTurn()==1 && p2.row==0) || (getTurn()==0 && p2.row==mSize-1)) {
		getTile(p2.row,p2.col)->setStatus(Tile::KING);
	}
	return true;
}

//mengembalikan nilai true, jika pada giliran sekarang ada yang bisa dimakan 
bool Checker::isThereEatable() {
	for(int i=0;i<mSize;i++) {
		for(int j=0;j<mSize;j++) {
			if(getTile(i,j)->isCoinInTile() && getTile(i,j)->getColor()==getTurn() && isEnemyNearbyCoinEatable(i,j)) {
				return true;
			}
		}
	}
	return false;
}

int main() {
	int row1,col1,row2,col2;
	Checker c(8);
	GamePoint p;
	while(true) {
		c.printBoard();
		cout<<"giliran pemain : "<<c.getTurn()<<endl;	
		cout<<"masukkan koin di petak yang mana dan ke petak yang mana : ";
		cin>>row1>>col1>>row2>>col2;
		if(c.isCoinAllowedToMove(row1,col1,row2,col2)) {
			c.moveCoin(row1,col1,row2,col2);
			if(abs(row1-row2)==2 && c.isThereEatable()) {//jika si pemain barusan memakan, suru jalan lagi jika masih ada yang bisa dimakan
				cout<<"anda berhak jalan sekali lagi karena masih ada koin lawan yang bisa dimakan"<<endl;
				continue;
			}
			c.nextTurn();//ganti giliran
		}else{
			cout<<"illegal move!"<<endl;
		}
	};
	return 0;
}

