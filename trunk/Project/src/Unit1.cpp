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

#define EIGHT 0
#define TEN 1

Checker *c;
int mode = EIGHT;


void showCoin(int posX, int posY) {
   if ((posY == 0) && (posX == 1)) {
      Form1->wh1->Picture->LoadFromFile("res/bidakputih.jpg");
   }
   else if ((posY == 0) && (posX == 3)) {
      Form1->wh5->Picture->LoadFromFile("res/bidakputih.jpg");
   }
   else if ((posY == 0) && (posX == 5)) {
      Form1->wh8->Picture->LoadFromFile("res/bidakputih.jpg");
   }
   else if ((posY == 0) && (posX == 7)) {
      Form1->wh11->Picture->LoadFromFile("res/bidakputih.jpg");
   }
   else if ((posY == 1) && (posX == 0)) {
      Form1->wh2->Picture->LoadFromFile("res/bidakputih.jpg");
   }
   else if ((posY == 1) && (posX == 2)) {
      Form1->wh4->Picture->LoadFromFile("res/bidakputih.jpg");
   }
   else if ((posY == 1) && (posX == 4)) {
      Form1->wh7->Picture->LoadFromFile("res/bidakputih.jpg");
   }
   else if ((posY == 1) && (posX == 6)) {
      Form1->wh10->Picture->LoadFromFile("res/bidakputih.jpg");
   }
   else if ((posY == 2) && (posX == 1)) {
      Form1->wh3->Picture->LoadFromFile("res/bidakputih.jpg");
   }
   else if ((posY == 2) && (posX == 3)) {
      Form1->wh6->Picture->LoadFromFile("res/bidakputih.jpg");
   }
   else if ((posY == 2) && (posX == 5)) {
      Form1->wh9->Picture->LoadFromFile("res/bidakputih.jpg");
   }
   else if ((posY == 2) && (posX == 7)) {
      Form1->wh12->Picture->LoadFromFile("res/bidakputih.jpg");
   }
   else if ((posY == 5) && (posX == 0)) {
      Form1->bl1->Picture->LoadFromFile("res/bidakmerah.jpg");
   }
   else if ((posY == 5) && (posX == 2)) {

   }
   else if ((posY == 5) && (posX == 4)) {

   }
   else if ((posY == 5) && (posX == 6)) {

   }
   else if ((posY == 6) && (posX == 1)) {

   }
   else if ((posY == 6) && (posX == 3)) {

   }
   else if ((posY == 6) && (posX == 5)) {

   }
   else if ((posY == 6) && (posX == 7)) {

   }
   else if ((posY == 7) && (posX == 0)) {

   }
   else if ((posY == 7) && (posX == 2)) {

   }
   else if ((posY == 7) && (posX == 4)) {

   }
   else if ((posY == 7) && (posX == 6)) {

   }
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
   c = new Checker(8);
   for (int i=0; i<8; i++) {
      for (int j=0; j<8; j++) {
         if ((c->getTile(i,j))->isCoinInTile()) {
            showCoin(j,i);
         }
      }
   }
}
//---------------------------------------------------------------------------


