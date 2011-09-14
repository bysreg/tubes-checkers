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
#include <DBCtrls.hpp>
#include <Menus.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TImage *Board;
        TStaticText *StaticText1;
        TEdit *DialogBox;
        TMainMenu *MainMenu;
        TMenuItem *Permainan;
        TMenuItem *PlayervsAI;
        TMenuItem *AIvsPlayer;
        TMenuItem *Mode;
        TMenuItem *EightxEight;
        TMenuItem *TenxTen;
        TTimer *AIRed;
        TTimer *AIWhite;
        TMenuItem *Kecepatan;
        TMenuItem *Lambat;
        TMenuItem *Sedang;
        TMenuItem *Cepat;
        TTimer *AITurn;
        TMenuItem *AIvsAI;
        void __fastcall coinMouseDown(TObject *Sender, TMouseButton Button,
               TShiftState Shift, int X, int Y);
        void __fastcall hintMouseDown(TObject *Sender, TMouseButton Button,
               TShiftState Shift, int X, int Y);
        void __fastcall PlayervsAIClick(TObject *Sender);
        void __fastcall AIvsPlayerClick(TObject *Sender);
        void __fastcall AIvsAIClick(TObject *Sender);
        void __fastcall EightxEightClick(TObject *Sender);
        void __fastcall TenxTenClick(TObject *Sender);
        void __fastcall AITurnTimer(TObject *Sender);
        void __fastcall AIRedTimer(TObject *Sender);
        void __fastcall AIWhiteTimer(TObject *Sender);
        void __fastcall LambatClick(TObject *Sender);
        void __fastcall SedangClick(TObject *Sender);
        void __fastcall CepatClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
