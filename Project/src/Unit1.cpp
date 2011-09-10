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
#define EIGHT 0
#define TEN 1

Checker *c;
TImage *coinImage[24];
TImage *hintImage;
int mode = EIGHT;
int coinIndex;
bool isGameStarted;

void showCoin(int posX, int posY) {
   if (posY < 3) {
      coinImage[coinIndex] = new TImage(Form1);
      coinImage[coinIndex]->Parent = Form1;
      coinImage[coinIndex]->Picture->LoadFromFile("res/bidakputih.jpg");
      coinImage[coinIndex]->Top = (posY*60) + 12;
      coinImage[coinIndex]->Left = (posX*60) + 12;
   }
   else {
      coinImage[coinIndex] = new TImage(Form1);
      coinImage[coinIndex]->Parent = Form1;
      coinImage[coinIndex]->Picture->LoadFromFile("res/bidakmerah.jpg");
      coinImage[coinIndex]->Top = (posY*60) + 12;
      coinImage[coinIndex]->Left = (posX*60) + 12;
   }

   coinIndex++;
}

void __fastcall TForm1::Button1Click(TObject *Sender)
{
   if (mode == EIGHT) {
      Form1->Board->Picture->LoadFromFile("res/kotak10x10.jpg");
      mode = TEN;
   }
   else {
      Form1->Board->Picture->LoadFromFile("res/kotak8x8.jpg");
      mode = EIGHT;
   }
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Button2Click(TObject *Sender)
{
   if (isGameStarted == FALSE) {
      c = new Checker(8);
      for (int i=0; i<8; i++) {
         for (int j=0; j<8; j++) {
            if ((c->getTile(i,j))->isCoinInTile()) {
               showCoin(j,i);
               coinImage[coinIndex-1]->OnMouseDown = coinMouseDown;
            }
         }
      }

      /*
      for (int i=0; i<8; i++) {
         for (int j=0; j<8; j++) {
            coinImage[24] = new TImage(Form1);
            coinImage[24]->Parent = Form1;
            coinImage[24]->Picture->LoadFromFile("res/bidakputih.jpg");
            coinImage[24]->Top = 10;
            coinImage[24]->Left = 10;
         }
      }
      */
      
      isGameStarted = TRUE;
   }
}
//---------------------------------------------------------------------------


void __fastcall TForm1::coinMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y) {
      TImage *coin = dynamic_cast<TImage *>(Sender);
      //coin->Visible = false;

      vector<GamePoint> arrGamePoint = c->getWalkableFromCoinInTile(((coin->Top)-12)/60,((coin->Left)-12)/60);

      for (int i=0; i<(sizeof(arrGamePoint)/sizeof(int)); i++) {
         hintImage = new TImage(Form1);
         hintImage->Parent = Form1;
         hintImage->Picture->LoadFromFile("res/penunjuk.jpg");
         hintImage->Top = (arrGamePoint[i].row*60) + 12;
         hintImage->Left = (arrGamePoint[i].col*60) + 12;
      }
}
