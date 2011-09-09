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

        /*
        if (Form1->Image1->Visible == true) {
                Form1->Image1->Visible = false;
        }
        else {
                Form1->Image1->Visible = true;
        }
        */
}
//---------------------------------------------------------------------------
