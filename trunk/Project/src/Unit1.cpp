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
TImage *hintImage[5];
int mode = EIGHT;
int coinIndex;
int hintIndex;
bool isGameStarted;

void showCoin(int posX, int posY) {
   if (posY < 3) {
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
      for (int i=0; i<c->getSize(); i++) {
         for (int j=0; j<c->getSize(); j++) {
            if ((c->getTile(i,j))->isCoinInTile()) {
               showCoin(j,i);
            }
         }
      }

      if ((c->getTurn()) == 0) {
         for (int i=0; i<24; i++) {
            if (i < 12) {
               coinImage[i]->OnMouseDown = coinMouseDown;
            }
            else {
               coinImage[i]->OnMouseDown = 0;
            }
         }
      }
      else {
         for (int i=0; i<24; i++) {
            if (i < 12) {
               coinImage[i]->OnMouseDown = 0;
            }
            else {
               coinImage[i]->OnMouseDown = coinMouseDown;
            }
         }
      }

      isGameStarted = TRUE;
   }
}
//---------------------------------------------------------------------------


void __fastcall TForm1::coinMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y) {
      TImage *coin = dynamic_cast<TImage *>(Sender);

      vector<GamePoint> arrGamePoint = c->getWalkableFromCoinInTile(((coin->Top)-12)/60,((coin->Left)-12)/60);

      for (int i=0; i<hintIndex; i++) {
         hintImage[i]->Picture = 0;
      }

      hintIndex = 0;

      for (int i=0; i<arrGamePoint.size(); i++) {
         hintImage[hintIndex] = new TImage(Form1);
         hintImage[hintIndex]->Parent = Form1;
         hintImage[hintIndex]->Picture->LoadFromFile("res/penunjuk.jpg");
         hintImage[hintIndex]->Top = (arrGamePoint[i].row*60) + 12;
         hintImage[hintIndex]->Left = (arrGamePoint[i].col*60) + 12;
         hintIndex++;
      }
}
