//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <jpeg.hpp>
#include "vizinhanca.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
	Form1->Color = clWhite;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::SpeedButton1Click(TObject *Sender)
{
//	Image1->Picture->LoadFromFile("cg.bmp"); // Carregando imagem
	Image1->Picture->LoadFromFile("cg.bmp"); //
	Image1->Stretch = true; //redimensiona
	Image1->Refresh(); //atualiza
}
//---------------------------------------------------------------------------
void __fastcall TForm1::SpeedButton2Click(TObject *Sender)
{
	int x, y, a, b;
	ShowMessage(Image1->Width);
	ShowMessage(Image1->Height);
	TColor cor;

	for(x = 0; x < Image1->Width/2; x++){
		for(y = 0; y < Image1->Height/2; y++){
			a = (x*2);
			b = (y*2);
			cor = Image1->Canvas->Pixels[x][y];
			Image1->Canvas->Pixels[a][b];
			Image1->Canvas->Pixels[a+1][b];
			Image1->Canvas->Pixels[a][b+1];
			Image1->Canvas->Pixels[a+1][b+1];
		}
	}
}
//---------------------------------------------------------------------------


