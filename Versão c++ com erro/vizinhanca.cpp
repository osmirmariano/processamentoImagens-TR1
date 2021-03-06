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
	ComboBox1->Items->Add("AMPLIAR");
	ComboBox1->Items->Add("REDUZIR");
	ComboBox2->Items->Add("VIZINHOS PROXIMO");
	ComboBox2->Items->Add("BILINEAR");
	ComboBox1->Enabled = false;
	ComboBox2->Enabled = false;
	Label2->Enabled = false;
	Label3->Enabled = false;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::SpeedButton1Click(TObject *Sender)
{
	Image1->Picture->LoadFromFile("cg.bmp"); //Carregando a imagem do diretorio
	Image1->Stretch = true; //redimensiona
	Image1->Refresh(); //atualiza
	ComboBox1->Enabled = true;
	ComboBox2->Enabled = true;
	Label2->Enabled = true;
	Label3->Enabled = true;//
}
//---------------------------------------------------------------------------


void __fastcall TForm1::ComboBox1Change(TObject *Sender)
{
	int x, y, valor1, valor2, R[2], G[2], B[2], red, green, blue, media[3];
	estados = ComboBox1->Text;
	if(estados == "AMPLIAR"){
		if(interpolacao == "VIZINHOS PROXIMO"){
			for(x = 0; x < (Image1->Width)/2; x++){
				for(y = 0; y < (Image1->Height)/2; y++){
					valor1 = (x*2);
					valor2 = (y*2);
					cor = Image1->Canvas->Pixels[x][y];
					Image1->Canvas->Pixels[valor1][valor2] = cor;
					Image1->Canvas->Pixels[valor1+1][valor2] = cor;
					Image1->Canvas->Pixels[valor1][valor2+1] = cor;
					Image1->Canvas->Pixels[valor1+1][valor2+1] = cor;
				}
			}
		}
		else if(interpolacao == "BILINEAR"){
			for(x = 0; x < ((Image1->Width)/2); x++){
				for(y = 0; y < ((Image1->Height)/2); y++){
					valor1 = (x*2);
					valor2 = (y*2);

					cor = Image1->Canvas->Pixels[x][y];
					R[0] = GetRValue(cor);  //Retorna Intensidade de cor vermelha
					G[0] = GetGValue(cor);  //Retorna Intensidade de cor Verde
					B[0] = GetBValue(cor);  //Retorna Intensidade de cor Azul

					cor = Image1->Canvas->Pixels[x][y+1];
					R[1] = GetRValue(cor);  //Retorna Intensidade de cor vermelha
					G[1] = GetGValue(cor);  //Retorna Intensidade de cor Verde
					B[1] = GetBValue(cor);  //Retorna Intensidade de cor Azul

					red = ((R[0] + R[1])/2);
					green = ((G[0] + G[1])/2);
					blue = ((B[0] + B[1])/2);
					Image1->Canvas->Pixels[valor1][valor2] = RGB(red,green,blue);

					cor = Image1->Canvas->Pixels[x+1][y];
					R[0] = GetRValue(cor);  //Retorna Intensidade de cor vermelha
					G[0] = GetGValue(cor);  //Retorna Intensidade de cor Verde
					B[0] = GetBValue(cor);  //Retorna Intensidade de cor Azul

					cor = Image1->Canvas->Pixels[x+1][y+1];
					R[1] = GetRValue(cor);  //Retorna Intensidade de cor vermelha
					G[1] = GetGValue(cor);  //Retorna Intensidade de cor Verde
					B[1] = GetBValue(cor);  //Retorna Intensidade de cor Azul

					red = ((R[0] + R[1])/2);
					green = ((G[0] + G[1])/2);
					blue = ((B[0] + B[1])/2);
					Image1->Canvas->Pixels[valor1+1][valor2] = RGB(red,green,blue);

					cor = Image1->Canvas->Pixels[x][y];
					R[0] = GetRValue(cor);  //Retorna Intensidade de cor vermelha
					G[0] = GetGValue(cor);  //Retorna Intensidade de cor Verde
					B[0] = GetBValue(cor);  //Retorna Intensidade de cor Azul

					cor = Image1->Canvas->Pixels[x][y+1];
					R[1] = GetRValue(cor);  //Retorna Intensidade de cor vermelha
					G[1] = GetGValue(cor);  //Retorna Intensidade de cor Verde
					B[1] = GetBValue(cor);  //Retorna Intensidade de cor Azul

					red = ((R[0] + R[1])/2);
					green = ((G[0] + G[1])/2);
					blue = ((B[0] + B[1])/2);
					Image1->Canvas->Pixels[valor1][valor2] = RGB(red,green,blue);
				}
			}
		}
	}
	else if(estados == "REDUZIR"){
		if(interpolacao == "VIZINHOS PROXIMO"){
            for (x = 0; x < Image1->Width*2; x = x + 2) {
				for (y = 0; y < Image1->Height*2; y = y + 2) {
					cor = Image1->Canvas->Pixels[x][y];
					Image1->Canvas->Pixels[x/2][y/2];
				}
			}
		}
		else if(interpolacao == "BILINEAR"){
			for(x = 0; x < ((Image1->Width)*2); x++){
				for(y = 0; y < ((Image1->Height)*2); y++){
					valor1 = x/2;
					valor2 = y/2;

					cor = Image1->Canvas->Pixels[x][y];
					R[0] = GetRValue(cor);  //Retorna Intensidade de cor vermelha
					G[0] = GetGValue(cor);  //Retorna Intensidade de cor Verde
					B[0] = GetBValue(cor);  //Retorna Intensidade de cor Azul

					cor = Image1->Canvas->Pixels[x+1][y];
					R[1] = GetRValue(cor);  //Retorna Intensidade de cor vermelha
					G[1] = GetGValue(cor);  //Retorna Intensidade de cor Verde
					B[1] = GetBValue(cor);  //Retorna Intensidade de cor Azul

					cor = Image1->Canvas->Pixels[x][y+1];
					R[2] = GetRValue(cor);  //Retorna Intensidade de cor vermelha
					G[2] = GetGValue(cor);  //Retorna Intensidade de cor Verde
					B[2] = GetBValue(cor);  //Retorna Intensidade de cor Azul

					cor = Image1->Canvas->Pixels[x+1][y+1];
					R[3] = GetRValue(cor);  //Retorna Intensidade de cor vermelha
					G[3] = GetGValue(cor);  //Retorna Intensidade de cor Verde
					B[3] = GetBValue(cor);  //Retorna Intensidade de cor Azul

					media[0] =  ((R[0] + R[1] + R[2] + R[3])/4);
					media[1] =  ((G[0] + G[1] + G[2] + G[3])/4);
					media[2] =  ((B[0] + B[1] + B[2] + B[3])/4);
					Image1->Canvas->Pixels[valor1][valor2] = RGB(media[0],media[1],media[3]);
				}
			}
		}
	}
}
//---------------------------------------------------------------------------


void __fastcall TForm1::ComboBox2Change(TObject *Sender)
{
	interpolacao = ComboBox2->Text;
}
//---------------------------------------------------------------------------




