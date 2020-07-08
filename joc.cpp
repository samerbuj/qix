#include "Graphics_Console.h"
#include "joc.h"
#include <conio.h>
#include <stdio.h>
#include <iostream>
#include <time.h>
#include "menu.h"
#include <mmsystem.h>
using namespace std;

void Taulell(HANDLE hScreen)//TABLERO
{
	//Aquests dos 'for' delimiten el nostre taulell.
	TextColor(LIGHTGREY, BLACK, hScreen); //Aquest procediment serveix per canviar la lletra i el fons del nostre caracter.

	for (int x = INICI_X; x <= FIN_X; x++)
	{
		GotoXY(x, INICI_Y, hScreen); //GotoXY envia el cursor de la consola a les coordenades corresponents.
		cout.put(MUR);
		GotoXY(x, FIN_Y, hScreen);
		cout.put(MUR);
	}

	for (int y = INICI_Y; y <= FIN_Y; y++)
	{
		GotoXY(INICI_X, y, hScreen);
		cout.put(MUR);
		GotoXY(FIN_X, y, hScreen);
		cout.put(MUR);
	}
}

//==================================//

void InfoPuntsPartida(int punts, HANDLE hScreen)//Mostra els punts 
{
	TextColor(YELLOW, BLACK, hScreen);
	GotoXY(INICI_X + 2, INICI_Y - 4, hScreen);
	cout << "PUNTS: " << punts;
}

//==================================//

void InfoVidesPartida(int vides, HANDLE hScreen)//Mostra les vides 
{
	TextColor(MAGENTA, BLACK, hScreen);
	GotoXY(INICI_X + 2, INICI_Y - 2, hScreen);
	cout << "VIDES: "<<vides;
}

//==================================//

void InfoNivellPartida(int nivell,HANDLE hScreen)//Mostra el nivell
{
	TextColor(RED, BLACK, hScreen);
	GotoXY(FIN_X - 8, INICI_Y - 4, hScreen);
	cout << "NIVELL: "<<nivell;
}

//==================================//

void GameOver(HANDLE hScreen)//Mostra el text GAMEOVER a la pantalla quan s'ha perdut
{
	PlaySound(TEXT("Wasted.wav"), NULL, SND_ASYNC);
	TextColor(WHITE, BLACK, hScreen);
	GotoXY(((INICI_X + FIN_X) / 2) - 4, (INICI_Y + FIN_Y) / 2, hScreen);
	cout << "GAME OVER";
	Sleep(5000);
}

//==================================//

void PintarObjecte(int X, int Y, char Obj, int ColorObj, HANDLE hScreen)//Pinta un objecte
{
	GotoXY(X, Y, hScreen);
	TextColor(ColorObj, BLACK, hScreen);
	cout.put(Obj);
}

//==================================//

void EsborrarObjecte(int X, int Y, char Obj, HANDLE hScreen)//Borra un objecte
{
	GotoXY(X, Y, hScreen);
	TextColor(BLACK, BLACK, hScreen);
	cout.put(Obj);
}

//==================================//

void PintarQIX(int qixX, int qixY, HANDLE hScreen)//Aplicació de PintarObjecte al Qix
{
	PintarObjecte(qixX, qixY, MUR, MAGENTA, hScreen);
}

//==================================//

void EsborrarQIX(int qixX, int qixY, HANDLE hScreen)//Aplicació de EsborrarObjecte al Qix
{
	EsborrarObjecte(qixX, qixY, MUR, hScreen);
}

//==================================//

void MoureQIX(int&qixX, int&qixY, int&DirQixX, int&DirQixY, int IniciX, int IniciY, int FiX, int FiY, HANDLE hScreen) 
		/*Fa el moviment erràtic del Qix dins del camp delimitat, i detecta si rebota per canviar de sentit*/
{
	static int RecorregutQix = 0;
	EsborrarQIX(qixX, qixY, hScreen);

	if (!RecorregutQix)
	{
		InicialitzaDirQIX(DirQixX, DirQixY);
		RecorregutQix = Aleatori(5, 20);
		//InicialitzaDirQIX(DirQixX, DirQixY);
	}

	if ((qixX + DirQixX <= IniciX) || (qixX + DirQixX >= FiX))
	{
		DirQixX *= -1;
	}
	if ((qixY + DirQixY <= IniciY) || (qixY + DirQixY >= FiY))
	{
		DirQixY *= -1;
	}
	qixY += DirQixY;
	qixX += DirQixX;
	PintarQIX(qixX, qixY, hScreen);

	RecorregutQix--;
}

//==================================//

void PintarCursor(int cursorX, int cursorY, HANDLE hScreen)//Aplicació de PintarObjecte al Cursor
{
	PintarObjecte(cursorX, cursorY, MUR, RED, hScreen);
}

//==================================//

void EsborrarCursor(int cursorX, int cursorY, HANDLE hScreen)//Aplicació de EsborrarObjecte al Cursor
{
	EsborrarObjecte(cursorX, cursorY, MUR, hScreen);
	PintarObjecte(cursorX, cursorY, MUR, LIGHTGREY, hScreen);
}

//==================================//

int Aleatori(int min, int max) //Genera una aleatorietat en el moviment del Qix
{
	return (rand() % (max - min + 1) - min);
}

//==================================//

void InicialitzaDirQIX(int &DirQixX, int &DirQixY)
{
	do {
		DirQixX = Aleatori(-1, 1);
		DirQixY = Aleatori(-1, 1);
	} while (DirQixX == 0 || DirQixY == 0);
}

//==================================//

void MoureCursor(int &CursorX, int &CursorY, int DirCursorX, int DirCursorY, HANDLE hScreen)//Permet simular el moviment del cursor.
{
	EsborrarCursor(CursorX, CursorY, hScreen);
	CursorX += DirCursorX;
	CursorY += DirCursorY;
	PintarCursor(CursorX, CursorY, hScreen);
}

//==================================//

char LlegirEvent()//Detecta quines tecles s'estàn polsant.
{
	unsigned char tecla = 0;
	tecla = _getch();

	if (tecla == TECLA_ESTESA)
	{
		tecla = _getch();
	}
	return tecla;
}

//==================================//

void PintarStix(int CursorX, int CursorY,
	HANDLE hScreen) //Pinta el mur que genera el Qix
{
	PintarObjecte(CursorX, CursorY, MUR, LIGHTGREY, hScreen);
}

//==================================//

int MovimentSTIX_Dreta(int &CursorX, int &CursorY, int IniciX, int IniciY, int FiX, int FiY, int &DirSTIX, HANDLE hScreen)
{
	int DirCursorX, DirCursorY;
	int StixAconseguit = 0;

	if ((CursorX == IniciX) && (DirSTIX == MOV_PARAT))
	{
		DirCursorX = 1; DirCursorY = 0;
		MoureCursor(CursorX, CursorY, DirCursorX, DirCursorY, hScreen);
		DirSTIX = MOV_DRETA;
	}
	else
	{
		if ((CursorX<FiX) && (DirSTIX == MOV_DRETA))
		{
			PintarStix(CursorX, CursorY, hScreen);
			CursorX++;
			PintarCursor(CursorX, CursorY, hScreen);
			if (CursorX == FiX)
			{
				DirSTIX = MOV_PARAT;
				StixAconseguit = 1;
			}
		}
	}
	return StixAconseguit;
}

//==================================//

int MovimentSTIX_Esquerra(int &CursorX, int &CursorY, int IniciX, int IniciY,
	int FiX, int FiY, int &DirSTIX, HANDLE hScreen)
{
	int DirCursorX, DirCursorY;
	int StixAconseguit = 0;
	if ((CursorX == FiX) && (DirSTIX == MOV_PARAT))
	{
		DirCursorX = -1; DirCursorY = 0;
		MoureCursor(CursorX, CursorY, DirCursorX, DirCursorY, hScreen);
		DirSTIX = MOV_ESQUERRA;
	}
	else
	{
		if ((CursorX>IniciX) && (DirSTIX == MOV_ESQUERRA))
		{
			PintarStix(CursorX, CursorY, hScreen);
			CursorX--;
			PintarCursor(CursorX, CursorY, hScreen);
			if (CursorX == IniciX)
			{
				DirSTIX = MOV_PARAT;
				StixAconseguit = 1;
			}
		}
	}
	return StixAconseguit;
}

//==================================//

int MovimentSTIX_Adalt(int &CursorX, int &CursorY, int IniciX, int IniciY,
	int FiX, int FiY, int &DirSTIX, HANDLE hScreen)
{

	int DirCursorX, DirCursorY;
	int StixAconseguit = 0;
	if ((CursorY == FiY) && (DirSTIX == MOV_PARAT))
	{
		DirCursorX = 0; DirCursorY = -1;
		MoureCursor(CursorX, CursorY, DirCursorX, DirCursorY, hScreen);
		DirSTIX = MOV_ADALT;
	}
	else
	{
		if ((CursorY>IniciY) && (DirSTIX == MOV_ADALT))
		{
			PintarStix(CursorX, CursorY, hScreen);
			CursorY--;
			PintarCursor(CursorX, CursorY, hScreen);
			if (CursorY == IniciY)
			{
				DirSTIX = MOV_PARAT;
				StixAconseguit = 1;
			}
		}
	}
	return StixAconseguit;
}

//==================================//

int MovimentSTIX_Abaix(int &CursorX, int &CursorY, int IniciX, int IniciY,
	int FiX, int FiY, int &DirSTIX, HANDLE hScreen)
{
	int DirCursorX, DirCursorY;
	int StixAconseguit = 0;
	if ((CursorY == IniciY) && (DirSTIX == MOV_PARAT))
	{
		DirCursorX = 0; DirCursorY = 1;
		MoureCursor(CursorX, CursorY, DirCursorX, DirCursorY, hScreen);
		DirSTIX = MOV_ABAIX;
	}
	else
	{
		if ((CursorY<FiY) && (DirSTIX == MOV_ABAIX))
		{
			PintarStix(CursorX, CursorY, hScreen);
			CursorY++;
			PintarCursor(CursorX, CursorY, hScreen);
			if (CursorY == FiY)
			{
				DirSTIX = MOV_PARAT;
				StixAconseguit = 1;
			}
		}
	}
	return StixAconseguit;
}

//==================================//

void TractarEvent(char tecla, int &CursorX, int &CursorY, int qixX, int qixY, int &IniciX, int &IniciY, int &FiX, int &FiY, int &DirSTIX, int &Area, HANDLE hScreen)
{
	int Stix;
	switch (tecla)
	{
	case TECLA_DRETA:
		if (CursorX + 1 <= FiX && (CursorY == IniciY || CursorY == FiY))
			MoureCursor(CursorX, CursorY, 1, 0, hScreen);
		break;

	case TECLA_ESQUERRA:
		if (CursorX - 1 >= IniciX && (CursorY == IniciY || CursorY == FiY))
			MoureCursor(CursorX, CursorY, -1, 0, hScreen);
		break;

	case TECLA_ADALT:
		if (CursorY - 1 >= IniciY && (CursorX == IniciX || CursorX == FiX))
			MoureCursor(CursorX, CursorY, 0, -1, hScreen);
		break;

	case TECLA_ABAIX:
		if (CursorY + 1 <= FiY && (CursorX == IniciX || CursorX == FiX))
			MoureCursor(CursorX, CursorY, 0, 1, hScreen);
		break;

	case TECLA_CTRDRETA:
		Stix = MovimentSTIX_Dreta(CursorX, CursorY, IniciX, IniciY, FiX, FiY, DirSTIX, hScreen);
		if (Stix)
		{
			if (CursorY > qixY)
			{
				FiY = CursorY;
				Area = (FiX - IniciX)*(CursorY-IniciY);
			}
			else
			{
				IniciY = CursorY;
				Area = (FiX - IniciX)*(CursorY - IniciY);
			}
		}
		break;

	case TECLA_CTRESQUERRA:
		Stix = MovimentSTIX_Esquerra(CursorX, CursorY, IniciX, IniciY, FiX, FiY, DirSTIX, hScreen);
		if (Stix)
		{
			if (CursorY > qixY)
			{
				FiY = CursorY;
				Area = (FiX - IniciX)*(CursorY-IniciY);
			}
			else
			{
				IniciY = CursorY;
				Area = (FiX - IniciX)*(CursorY - IniciY);
			}
		}
		break;

	case TECLA_CTRADALT:
		Stix = MovimentSTIX_Adalt(CursorX, CursorY, IniciX, IniciY, FiX, FiY, DirSTIX, hScreen);
		if (Stix)
		{
			if (CursorX > qixX)
			{
				FiX = CursorX;
				Area = (CursorX - IniciX)*(FiY - IniciY);
			}
			else
			{
				IniciX = CursorX;
				Area = (FiX - CursorX)*(FiY - IniciY);
			}
		}
		break;

	case TECLA_CTRABAIX:
		Stix = MovimentSTIX_Abaix(CursorX, CursorY, IniciX, IniciY, FiX, FiY, DirSTIX, hScreen);
		if (Stix)
		{
			if (CursorX > qixX)
			{
				FiX = CursorX;
				Area = (CursorX - IniciX)*(FiY - IniciY);
			}
			else
			{
				IniciX = CursorX;
				Area = (FiX - CursorX)*(FiY - IniciY);
			}
		}
		break;
	}
}

//==================================//

int QiXXocStix(int qixX, int qixY, int cursorX, int cursorY, int DirStix)
{
	int xoc = 0;
	switch (DirStix)
	{
	case MOV_DRETA:
		if ((cursorY == qixY) && (cursorX >= qixX))
			xoc = 1;
		break;

	case MOV_ESQUERRA:
		if ((cursorY == qixY) && (cursorX <= qixX))
			xoc = 1;
		break;

	case MOV_ADALT:
		if ((cursorX == qixX) && (cursorY <= qixY))
			xoc = 1;
		break;

	case MOV_ABAIX:
		if ((cursorX == qixX) && (cursorY >= qixY))
			xoc = 1;
		break;
	}
	return xoc;
}

//==================================//

int joc(int nivell)//Funció principal del joc.
{
	HANDLE hScreen;
	hScreen = GetStdHandle(STD_OUTPUT_HANDLE);
	InitScreen(hScreen);

	int IniciX,FiX;
	int IniciY,FiY;

	unsigned char tecla;
	tecla = 0;
	
	srand((unsigned)time(NULL));//Fa que l'aleatorietat del joc vagi en funció del rellotge de Windows.
	int DirQixX;
	int DirQixY;

	int DirStix;

	bool viu = true;
	int vides = 3;

	int qixX;
	int qixY;

	//Cursor
	int cursorX;
	int cursorY;

	int XocStix = 0;

	int punts = 0;
	//int nivell = 1;
	int Area = 0;
	int AreaTotal = 0;
	bool nivellcompletat = false;

	int VelocitatQix = VELOCITATPC - (nivell*(VELOCITATPC / 5));
	int NCops = 0;

	do
	{
		IniciX = INICI_X, FiX = FIN_X;
		IniciY = INICI_Y, FiY = FIN_Y;
		
		viu = true;


		//TABLERO i diferents elements de la pantalla de joc
		system("cls");
		Taulell(hScreen);

		InfoPuntsPartida(punts,hScreen);

		InfoVidesPartida(vides,hScreen);

		InfoNivellPartida(nivell,hScreen);

		//Qix
		qixX = (INICI_X + FIN_X) / 2;
		qixY = FIN_Y - 5;

		PintarQIX(qixX, qixY, hScreen);

		InicialitzaDirQIX(DirQixX, DirQixY);
		DirQixX = Aleatori(-1, 1);
		DirQixY = Aleatori(-1, 1);
		


		//Cursor
		cursorX = (INICI_X + FIN_X) / 2;
		cursorY = FIN_Y;
		PintarCursor(cursorX, cursorY, hScreen);

		//Stix
		DirStix = MOV_PARAT;
		nivellcompletat = false;
		AreaTotal = 0;
		Area = 0;

		do {
			if (_kbhit())
			{
				tecla = LlegirEvent();
				TractarEvent(tecla, cursorX, cursorY, qixX, qixY, IniciX, IniciY, FiX, FiY, DirStix, Area, hScreen);
				if (Area)
				{
					punts += Area;
					InfoPuntsPartida(punts, hScreen);
					AreaTotal += Area;
					Area = 0;
					if (AreaTotal >= (3 * AREARECTANGLE / 4))//Per guanyar, comparem AreaTotal
						nivellcompletat = true;
				}
			}
			NCops++;
			if (NCops >= VelocitatQix)
			{
				MoureQIX(qixX, qixY, DirQixX, DirQixY, IniciX, IniciY, FiX, FiY, hScreen);
				if (DirStix != MOV_PARAT)
				{
					XocStix = QiXXocStix(qixX, qixY, cursorX, cursorY, DirStix);
					if (XocStix)
						viu = false;
				}
				NCops = 0;
			}

		} while (viu && !nivellcompletat && tecla != TECLA_ESC);
		if (!viu)
			vides--;
		if (vides <= 0)
		{
			GameOver(hScreen);
		}
		if (nivellcompletat)
			nivell++;
		TextColor(LIGHTGREY, BLACK, hScreen);
		Sleep(1500);
	} while (tecla != TECLA_ESC && vides>0 && nivell<4);
	return punts;

	system("cls");
}