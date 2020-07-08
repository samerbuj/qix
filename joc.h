#pragma once
#include "Graphics_Console.h"

#define MUR 219
#define INICI_X 4
#define INICI_Y 5
#define FIN_X 36
#define FIN_Y 25

#define TECLA_ESTESA 224
#define TECLA_ESC 27

#define TECLA_ESQUERRA 75
#define TECLA_DRETA 77
#define TECLA_ADALT 72
#define TECLA_ABAIX 80

#define MOV_PARAT 0
#define MOV_DRETA 2
#define MOV_ESQUERRA 4
#define MOV_ADALT 1
#define MOV_ABAIX 3

#define TECLA_CTRESQUERRA 'a'
#define TECLA_CTRDRETA 'd'
#define TECLA_CTRADALT 'w'
#define TECLA_CTRABAIX 's'

#define AREARECTANGLE (FIN_X-INICI_X)*(FIN_Y-INICI_Y)

#define VELOCITATPC 2222

int joc(int nivell);
void Taulell(HANDLE hScreen);
void InfoPuntsPartida(int punts, HANDLE hScreen);
void InfoVidesPartida(int vides,HANDLE hScreen);
void InfoNivellPartida(int nivell, HANDLE hScreen);
void GameOver(HANDLE hScreen);
void PintarObjecte(int X, int Y, char Obj, int ColorObj, HANDLE hScreen);
void EsborrarObjecte(int X, int Y, char Obj, HANDLE hScreen);
void PintarQIX(int qixX, int qixY, HANDLE hScreen);
void PintarCursor(int cursorX, int cursorY, HANDLE hScreen);
void EsborrarQIX(int qixX, int qixY, HANDLE hScreen);
void EsborrarCursor(int CursorX, int CursorY, HANDLE hScreen);
char LlegirEvent();
void MoureQIX(int&qixX, int&qixY, int&DirQixX, int&DirQixY, int IniciX, int IniciY, int FiX, int FiY, HANDLE hScreen);
void InicialitzaDirQIX(int&DirQixX, int&DirQixY);
void TractarEvent(char tecla, int &CursorX, int &CursorY, int qixX, int qixY, int &IniciX, int &IniciY, int &FiX, int &FiY, int&DirSTIX, int &Area, HANDLE hScreen);
void MoureCursor(int &CursorX, int &CursorY, int DirCursorX, int DirCursorY, HANDLE hScreen);
int Aleatori(int min, int max);
int QiXXocStix(int qixX, int qixY, int cursorX, int cursorY, int DirStix);