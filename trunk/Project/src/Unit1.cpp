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

#define EIGHTxEIGHT 8
#define TENxTEN 10

Checker *c;
TImage *coinImage[40];
TImage *hintImage[5];
int mode = EIGHTxEIGHT;
int coinIndex;
int hintIndex;
int row1;
int col1;
int whiteStrategy = Checker::SELECT_BY_MOST_EAT;
int redStrategy = Checker::SELECT_BY_MOST_EAT;
int waitingTime = 2000;
bool isGameStarted;
bool isMoved;

void showCoin(int posX, int posY)
{
   if ((c->getTile(posY,posX)->getColor() == 0) && (c->getTile(posY,posX)->getStatus() == Tile::KING)) {
      coinImage[coinIndex] = new TImage(Form1);
      coinImage[coinIndex]->Parent = Form1;
      coinImage[coinIndex]->Picture->LoadFromFile("res/bidakputihraja.jpg");
      coinImage[coinIndex]->Top = (posY*60) + 12;
      coinImage[coinIndex]->Left = (posX*60) + 12;
      coinImage[coinIndex]->Height = 60;
      coinImage[coinIndex]->Width = 60;
   }
   else if ((c->getTile(posY,posX)->getColor() == 1) && (c->getTile(posY,posX)->getStatus() == Tile::KING)) {
      coinImage[coinIndex] = new TImage(Form1);
      coinImage[coinIndex]->Parent = Form1;
      coinImage[coinIndex]->Picture->LoadFromFile("res/bidakmerahraja.jpg");
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

void __fastcall TForm1::EightxEightClick(TObject *Sender)
{
   //ganti mode 8x8
   Form1->Board->Picture->LoadFromFile("res/kotak8x8.jpg");
   mode = EIGHTxEIGHT;

   if (isGameStarted == true) {
      for (int i=0; i<hintIndex; i++) {
         delete hintImage[i];
      }
      hintIndex = 0;

      for (int i=0; i<coinIndex; i++) {
         delete coinImage[i];
      }
      coinIndex = 0;

      delete c;
      AITurn->OnTimer = 0;
      AIRed->OnTimer = 0;
      AIWhite->OnTimer = 0;
      StaticText1->Caption = "";
      isGameStarted = false;
   }
}
//---------------------------------------------------------------------------


void __fastcall TForm1::TenxTenClick(TObject *Sender)
{
   //ganti mode 10x10
   Form1->Board->Picture->LoadFromFile("res/kotak10x10.jpg");
   mode = TENxTEN;

   if (isGameStarted == true) {
      for (int i=0; i<hintIndex; i++) {
         delete hintImage[i];
      }
      hintIndex = 0;

      for (int i=0; i<coinIndex; i++) {
         delete coinImage[i];
      }
      coinIndex = 0;

      delete c;
      AITurn->OnTimer = 0;
      AIRed->OnTimer = 0;
      AIWhite->OnTimer = 0;
      StaticText1->Caption = "";
      isGameStarted = false;
   }
}
//---------------------------------------------------------------------------


void __fastcall TForm1::PlayervsAIClick(TObject *Sender)
{
   //mulai permainan
   if (isGameStarted == false) {
      c = new Checker(mode);
      for (int i=0; i<c->getSize(); i++) {
         for (int j=0; j<c->getSize(); j++) {
            if ((c->getTile(i,j))->isCoinInTile()) {
               showCoin(j,i);
               coinImage[coinIndex-1]->OnMouseDown = coinMouseDown;
            }
         }
      }
      
      isGameStarted = true;
   }
   else {
      for (int i=0; i<hintIndex; i++) {
         delete hintImage[i];
      }
      hintIndex = 0;
      
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
   }

   StaticText1->Caption = "GILIRAN ANDA";
   AITurn->OnTimer = 0;
   AIRed->OnTimer = 0;
   AIWhite->OnTimer = 0;
}
//---------------------------------------------------------------------------


void __fastcall TForm1::AIvsPlayerClick(TObject *Sender)
{
   //mulai permainan
   if (isGameStarted == false) {
      c = new Checker(mode);
      for (int i=0; i<c->getSize(); i++) {
         for (int j=0; j<c->getSize(); j++) {
            if ((c->getTile(i,j))->isCoinInTile()) {
               showCoin(j,i);
            }
         }
      }
      
      isGameStarted = true;
   }
   else {
      for (int i=0; i<hintIndex; i++) {
         delete hintImage[i];
      }
      hintIndex = 0;

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
   }

   StaticText1->Caption = "MENUNGGU...";
   AITurn->OnTimer = AITurnTimer;
   AIRed->OnTimer = 0;
   AIWhite->OnTimer = 0;
}
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
            AITurn->OnTimer = 0;
            AIRed->OnTimer = 0;
            AIWhite->OnTimer = 0;

            if (c->getTurn() == 0) {
               ShowMessage("MERAH MENANG");
            }
            else {
               ShowMessage("PUTIH MENANG");
            }
         }
         else {
            AITurn->OnTimer = AITurnTimer;
            StaticText1->Caption = "MENUNGGU...";
         }
      }
   }
   else {

   }

   //hapus hint
   for (int i=0; i<hintIndex; i++) {
      delete hintImage[i];
   }
   hintIndex = 0;

   //hapus koin
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


void __fastcall TForm1::AITurnTimer(TObject *Sender)
{
   AITurn->Interval = waitingTime;

   GameMove gameMove;

   if (c->getTurn() == 0) {
      gameMove = c->selectMove(c->getAllLegalMove(),whiteStrategy);
   }
   else {
      gameMove = c->selectMove(c->getAllLegalMove(),redStrategy);
   }

   if(abs(gameMove.from.row-gameMove.to.row)==2 && c->isThereEatable()) {//jika si pemain barusan memakan, suru jalan lagi jika masih ada yang bisa dimakan
      
   }
   else {
      if (!(c->nextTurn())) {
         AITurn->OnTimer = 0;
         AIRed->OnTimer = 0;
         AIWhite->OnTimer = 0;

         if (c->getTurn() == 0) {
            ShowMessage("MERAH MENANG");
         }
         else {
            ShowMessage("PUTIH MENANG");
         }
      }
      else {
         AITurn->OnTimer = 0;
         StaticText1->Caption = "GILIRAN ANDA";
      }
   }

   //hapus koin
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


//AI vs AI
void __fastcall TForm1::AIvsAIClick(TObject *Sender)
{
   //mulai permainan
   if (isGameStarted == false) {
      c = new Checker(mode);
      for (int i=0; i<c->getSize(); i++) {
         for (int j=0; j<c->getSize(); j++) {
            if ((c->getTile(i,j))->isCoinInTile()) {
               showCoin(j,i);
            }
         }
      }

      isGameStarted = true;
   }
   else {
      for (int i=0; i<hintIndex; i++) {
         delete hintImage[i];
      }
      hintIndex = 0;

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
   }

   StaticText1->Caption = "GILIRAN MERAH";
   AITurn->OnTimer = 0;
   AIRed->OnTimer = AIRedTimer;
   AIWhite->OnTimer = 0;
}
//---------------------------------------------------------------------------


void __fastcall TForm1::AIRedTimer(TObject *Sender)
{
   AIRed->Interval = waitingTime;

   GameMove gameMove = c->selectMove(c->getAllLegalMove(),redStrategy);

   if(abs(gameMove.from.row-gameMove.to.row)==2 && c->isThereEatable()) {//jika si pemain barusan memakan, suru jalan lagi jika masih ada yang bisa dimakan

   }
   else {
      if (!(c->nextTurn())) {
         AITurn->OnTimer = 0;
         AIRed->OnTimer = 0;
         AIWhite->OnTimer = 0;
         if (c->getTurn() == 0) {
            ShowMessage("MERAH MENANG");
         }
         else {
            ShowMessage("PUTIH MENANG");
         }
      }
      else {
         AIRed->OnTimer = 0;
         AIWhite->OnTimer = AIWhiteTimer;
         StaticText1->Caption = "GILIRAN PUTIH";
      }
   }

   //hapus koin
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
//---------------------------------------------------------------------------


void __fastcall TForm1::AIWhiteTimer(TObject *Sender)
{
   AIWhite->Interval = waitingTime;

   GameMove gameMove = c->selectMove(c->getAllLegalMove(),whiteStrategy);

   if(abs(gameMove.from.row-gameMove.to.row)==2 && c->isThereEatable()) {//jika si pemain barusan memakan, suru jalan lagi jika masih ada yang bisa dimakan
  
   }
   else {
      if (!(c->nextTurn())) {
         AITurn->OnTimer = 0;
         AIRed->OnTimer = 0;
         AIWhite->OnTimer = 0;

         if (c->getTurn() == 0) {
            ShowMessage("MERAH MENANG");
         }
         else {
            ShowMessage("PUTIH MENANG");
         }
      }
      else {
         AIRed->OnTimer = AIRedTimer;
         AIWhite->OnTimer = 0;
         StaticText1->Caption = "GILIRAN MERAH";
      }
   }

   //hapus koin
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
//---------------------------------------------------------------------------


void __fastcall TForm1::RedAIOffensiveClick(TObject *Sender)
{
   redStrategy = Checker::SELECT_BY_MOST_EAT;
   StaticText3->Caption = "AI Merah : Agresif";
}

void __fastcall TForm1::RedAIDefensiveClick(TObject *Sender)
{
   redStrategy = Checker::SELECT_BY_MOST_DEFENSE;
   StaticText3->Caption = "AI Merah : Bertahan";
}

void __fastcall TForm1::RedAIOffensiveDefensiveClick(TObject *Sender)
{
   redStrategy = Checker::SELECT_BY_MOST_EAT_AND_DEFENSE;
   StaticText3->Caption = "AI Merah : Agresif-Bertahan";
}

void __fastcall TForm1::WhiteAIOffensiveClick(TObject *Sender)
{
   whiteStrategy = Checker::SELECT_BY_MOST_EAT;
   StaticText4->Caption = "AI Putih : Agresif";
}

void __fastcall TForm1::WhiteAIDefensiveClick(TObject *Sender)
{
   whiteStrategy = Checker::SELECT_BY_MOST_DEFENSE;
   StaticText4->Caption = "AI Putih : Bertahan";
}

void __fastcall TForm1::WhiteAIOffensiveDefensiveClick(TObject *Sender)
{
   whiteStrategy = Checker::SELECT_BY_MOST_EAT_AND_DEFENSE;
   StaticText4->Caption = "AI Putih : Agresif-Bertahan";
}
//---------------------------------------------------------------------------


void __fastcall TForm1::LambatClick(TObject *Sender)
{
   waitingTime = 5000;
   StaticText5->Caption = "Kecepatan Permainan : Lambat";
}

void __fastcall TForm1::SedangClick(TObject *Sender)
{
   waitingTime = 3000;
   StaticText5->Caption = "Kecepatan Permainan : Sedang";
}

void __fastcall TForm1::CepatClick(TObject *Sender)
{
   waitingTime = 500;
   StaticText5->Caption = "Kecepatan Permainan : Cepat";
}
//---------------------------------------------------------------------------


