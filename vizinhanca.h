//---------------------------------------------------------------------------

#ifndef vizinhancaH
#define vizinhancaH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Buttons.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.CheckLst.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TSpeedButton *SpeedButton1;
	TImage *Image1;
	TLabel *Label1;
	TComboBox *ComboBox1;
	TComboBox *ComboBox2;
	TLabel *Label2;
	TLabel *Label3;
	void __fastcall SpeedButton1Click(TObject *Sender);
	void __fastcall ComboBox1Change(TObject *Sender);
	void __fastcall ComboBox2Change(TObject *Sender);
private:	// User declarations
	TColor cor;
	AnsiString interpolacao;
	AnsiString estados;
	RGBTRIPLE* pixel;
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
