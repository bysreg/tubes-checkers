//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <jpeg.hpp>
#include "Tile.cpp"
#include "Checker.cpp"
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TImage *Board;
        TButton *Button1;
        TImage *wh5;
        TImage *wh8;
        TImage *wh11;
        TImage *wh2;
        TImage *wh4;
        TImage *wh7;
        TImage *wh10;
        TImage *wh3;
        TImage *wh6;
        TImage *wh9;
        TImage *wh12;
        TImage *bl1;
        TImage *bl4;
        TImage *bl7;
        TImage *bl10;
        TImage *bl3;
        TImage *bl6;
        TImage *bl9;
        TImage *bl12;
        TImage *bl2;
        TImage *bl5;
        TImage *bl8;
        TImage *bl11;
        TButton *Button2;
        TImage *wh1;
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall Button2Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif