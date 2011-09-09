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

int mode = EIGHT;


void showCoin(int piece) {
   switch (piece) {
      case(0): {Form1->wh1->Picture->LoadFromFile("res/bidakputih.jpg");}
      case(1): {Form1->wh2->Picture->LoadFromFile("res/bidakputih.jpg");}
      case(2): {Form1->wh3->Picture->LoadFromFile("res/bidakputih.jpg");}
      case(3): {Form1->wh4->Picture->LoadFromFile("res/bidakputih.jpg");}
      case(4): {Form1->wh5->Picture->LoadFromFile("res/bidakputih.jpg");}
      case(5): {Form1->wh6->Picture->LoadFromFile("res/bidakputih.jpg");}
      case(6): {Form1->wh7->Picture->LoadFromFile("res/bidakputih.jpg");}
      case(7): {Form1->wh8->Picture->LoadFromFile("res/bidakputih.jpg");}
      case(8): {Form1->wh9->Picture->LoadFromFile("res/bidakputih.jpg");}
      case(9): {Form1->wh10->Picture->LoadFromFile("res/bidakputih.jpg");}
      case(10): {Form1->wh11->Picture->LoadFromFile("res/bidakputih.jpg");}
      case(11): {Form1->wh12->Picture->LoadFromFile("res/bidakputih.jpg");}

      case(12): {Form1->bl1->Picture->LoadFromFile("res/bidakmerah.jpg");}
      case(13): {Form1->bl2->Picture->LoadFromFile("res/bidakmerah.jpg");}
      case(14): {Form1->bl3->Picture->LoadFromFile("res/bidakmerah.jpg");}
      case(15): {Form1->bl4->Picture->LoadFromFile("res/bidakmerah.jpg");}
      case(16): {Form1->bl5->Picture->LoadFromFile("res/bidakmerah.jpg");}
      case(17): {Form1->bl6->Picture->LoadFromFile("res/bidakmerah.jpg");}
      case(18): {Form1->bl7->Picture->LoadFromFile("res/bidakmerah.jpg");}
      case(19): {Form1->bl8->Picture->LoadFromFile("res/bidakmerah.jpg");}
      case(20): {Form1->bl9->Picture->LoadFromFile("res/bidakmerah.jpg");}
      case(21): {Form1->bl10->Picture->LoadFromFile("res/bidakmerah.jpg");}
      case(22): {Form1->bl11->Picture->LoadFromFile("res/bidakmerah.jpg");}
      case(23): {Form1->bl12->Picture->LoadFromFile("res/bidakmerah.jpg");}
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
   for (int i = 0; i < 32; i++) showCoin(i);        
}
//---------------------------------------------------------------------------

