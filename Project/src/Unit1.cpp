//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

#define TRUE 1
#define FALSE 0
#define EIGHT 8
#define TEN 10

Checker *c;
TImage *coinImage[40];
TImage *hintImage[5];
int mode = EIGHT;
int coinIndex;
int hintIndex;
int row1;
int col1;
bool isGameStarted;

void showCoin(int posX, int posY)
{
   if ((c->getTile(posY,posX)->getColor() == 0) && (c->getTile(posY,posX)->getStatus() == Tile::KING)) {
      coinImage[coinIndex] = new TImage(Form1);
      coinImage[coinIndex]->Parent = Form1;
      coinImage[coinIndex]->Picture->LoadFromFile("res/Checkers_king.jpg");
      coinImage[coinIndex]->Top = (posY*60) + 12;
      coinImage[coinIndex]->Left = (posX*60) + 12;
      coinImage[coinIndex]->Height = 60;
      coinImage[coinIndex]->Width = 60;
   }
   else if ((c->getTile(posY,posX)->getColor() == 1) && (c->getTile(posY,posX)->getStatus() == Tile::KING)) {
      coinImage[coinIndex] = new TImage(Form1);
      coinImage[coinIndex]->Parent = Form1;
      coinImage[coinIndex]->Picture->LoadFromFile("res/Checkers_king.jpg");
      coinImage[coinIndex]->Top = (posY*60) + 12;
      coinImage[coinIndex]->Left = (posX*60) + 12;
      coinImage[coinIndex]->Height = 60;
      coinImage[coinIndex]->Width = 60;
   }
   else if (c->getTile(posY,posX)->getColor() == 0) {
      coinImage[coinIndex] = new TImage(Form1);
      coinImage[coinIndex]->Parent = Form1;
      coinImage[coinIndex]->Picture->LoadFromFile("res/bidakputih.jpg");
      coinImage[coinIndex]->Top = (posY*60) + 12;
      coinImage[coinIndex]->Left = (posX*60) + 12;
      coinImage[coinIndex]->Height = 60;
      coinImage[coinIndex]->Width = 60;
   }
   else {
      coinImage[coinIndex] = new TImage(Form1);
      coinImage[coinIndex]->Parent = Form1;
      coinImage[coinIndex]->Picture->LoadFromFile("res/bidakmerah.jpg");
      coinImage[coinIndex]->Top = (posY*60) + 12;
      coinImage[coinIndex]->Left = (posX*60) + 12;
      coinImage[coinIndex]->Height = 60;
      coinImage[coinIndex]->Width = 60;
   }

   coinIndex++;
}

void __fastcall TForm1::Button1Click(TObject *Sender)
{
   //ganti mode 8x8 atau 10x10
   if (mode == EIGHT) {
      Form1->Board->Picture->LoadFromFile("res/kotak10x10.jpg");
      mode = TEN;
   }
   else {
      Form1->Board->Picture->LoadFromFile("res/kotak8x8.jpg");
      mode = EIGHT;
   }

   if (isGameStarted == TRUE) {
      for (int i=0; i<coinIndex; i++) {
         delete coinImage[i];
      }
      coinIndex = 0;

      delete c;
      c = new Checker(mode);
      for (int i=0; i<c->getSize(); i++) {
         for (int j=0; j<c->getSize(); j++) {
            if ((c->getTile(i,j))->isCoinInTile()) {
               showCoin(j,i);
               coinImage[coinIndex-1]->OnMouseDown = coinMouseDown;
            }
         }
      }

      StaticText1->Caption = "IT'S RED TURN";
   }
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Button2Click(TObject *Sender)
{
   //mulai permainan
   if (isGameStarted == FALSE) {
      c = new Checker(mode);
      for (int i=0; i<c->getSize(); i++) {
         for (int j=0; j<c->getSize(); j++) {
            if ((c->getTile(i,j))->isCoinInTile()) {
               showCoin(j,i);
               coinImage[coinIndex-1]->OnMouseDown = coinMouseDown;
            }
         }
      }

      //StaticText1->Caption = "IT'S RED TURN";
      isGameStarted = TRUE;
   }
   else {
      for (int i=0; i<coinIndex; i++) {
         delete coinImage[i];
      }
      coinIndex = 0;

      delete c;
      c = new Checker(mode);
      for (int i=0; i<c->getSize(); i++) {
         for (int j=0; j<c->getSize(); j++) {
            if ((c->getTile(i,j))->isCoinInTile()) {
               showCoin(j,i);
               coinImage[coinIndex-1]->OnMouseDown = coinMouseDown;
            }
         }
      }

      //StaticText1->Caption = "IT'S RED TURN";
   }
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------


void __fastcall TForm1::coinMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
   TImage *coin = dynamic_cast<TImage *>(Sender);

   vector<GamePoint> arrGamePoint = c->getWalkableFromCoinInTile(((coin->Top)-12)/60,((coin->Left)-12)/60);

   for (int i=0; i<hintIndex; i++) {
      delete hintImage[i];
   }
   hintIndex = 0;

   for (int i=0; i<arrGamePoint.size(); i++) {
      hintImage[hintIndex] = new TImage(Form1);
      hintImage[hintIndex]->Parent = Form1;
      hintImage[hintIndex]->Picture->LoadFromFile("res/penunjuk.jpg");
      hintImage[hintIndex]->Top = (arrGamePoint[i].row*60) + 12;
      hintImage[hintIndex]->Left = (arrGamePoint[i].col*60) + 12;
      hintImage[hintIndex]->Height = 60;
      hintImage[hintIndex]->Width = 60;
      hintImage[hintIndex]->OnMouseDown = hintMouseDown;
      hintIndex++;
   }

   row1 = ((coin->Top)-12)/60;
   col1 = ((coin->Left)-12)/60;
}
//---------------------------------------------------------------------------


void __fastcall TForm1::hintMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
   TImage *hint = dynamic_cast<TImage *>(Sender);

   //player vs AI
   if(c->isCoinAllowedToMove(row1,col1,((hint->Top)-12)/60,((hint->Left)-12)/60)) {
      c->moveCoin(row1,col1,((hint->Top)-12)/60,((hint->Left)-12)/60);

      if(abs(row1-((hint->Top)-12)/60)==2 && c->isThereEatable()) {//jika si pemain barusan memakan, suru jalan lagi jika masih ada yang bisa dimakan

      }
      else {
         if (!(c->nextTurn())) {
            if (c->getTurn() == 0) {
               ShowMessage("RED WINS");
            }
            else {
               ShowMessage("WHITE WINS");
            }
         }
         else {
            if (c->getTurn() == 0) {
               StaticText1->Caption = "IT'S WHITE TURN";
               c->selectMove(c->getAllLegalMove(),0);
               c->nextTurn();
            }
            if (c->getTurn() == 1) {
               StaticText1->Caption = "IT'S RED TURN";
            }
         }
      }
   }
   else {

   }

   for (int i=0; i<hintIndex; i++) {
      delete hintImage[i];
   }
   hintIndex = 0;

   for (int i=0; i<coinIndex; i++) {
      delete coinImage[i];
   }
   coinIndex = 0;

   //tampilkan koin
   for (int i=0; i<c->getSize(); i++) {
      for (int j=0; j<c->getSize(); j++) {
         if ((c->getTile(i,j))->isCoinInTile()) {
            showCoin(j,i);
            coinImage[coinIndex-1]->OnMouseDown = coinMouseDown;
         }
      }
   }
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Button3Click(TObject *Sender)
{
   //mulai permainan
   if (isGameStarted == FALSE) {
      c = new Checker(mode);
      for (int i=0; i<c->getSize(); i++) {
         for (int j=0; j<c->getSize(); j++) {
            if ((c->getTile(i,j))->isCoinInTile()) {
               showCoin(j,i);
            }
         }
      }

      //StaticText1->Caption = "IT'S RED TURN";
      isGameStarted = TRUE;
   }
   else {
      for (int i=0; i<coinIndex; i++) {
         delete coinImage[i];
      }
      coinIndex = 0;

      delete c;
      c = new Checker(mode);
      for (int i=0; i<c->getSize(); i++) {
         for (int j=0; j<c->getSize(); j++) {
            if ((c->getTile(i,j))->isCoinInTile()) {
               showCoin(j,i);
            }
         }
      }

      //StaticText1->Caption = "IT'S RED TURN";
   }
   //

   //AI vs AI
   for (int i=0; i<99999; i++) {
      c->selectMove(c->getAllLegalMove(),0);

      //for (int i=0; i<1000000000; i++) {}
      Sleep(10);
      
      if (!(c->nextTurn())) {
         if (c->getTurn() == 0) {
            ShowMessage("RED WINS");
            break;
         }
         else {
            ShowMessage("WHITE WINS");
            break;
         }
      }
      else {
         if (c->getTurn() == 0) {
            //StaticText1->Caption = "IT'S WHITE TURN";
            c->selectMove(c->getAllLegalMove(),0);
            c->nextTurn();
         }
         if (c->getTurn() == 1) {
            //StaticText1->Caption = "IT'S RED TURN";
         }
      }

      for (int i=0; i<coinIndex; i++) {
         delete coinImage[i];
      }
      coinIndex = 0;

      //tampilkan koin
      for (int i=0; i<c->getSize(); i++) {
         for (int j=0; j<c->getSize(); j++) {
            if ((c->getTile(i,j))->isCoinInTile()) {
               showCoin(j,i);
            }
         }
      }
   }
}
//---------------------------------------------------------------------------


