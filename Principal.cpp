#include "Graphics_Console.h"
#include <stdio.h>
#include <conio.h>
#include "joc.h"
#include "menu.h"
#include "GestioResultats.h"
#include <iostream>
using namespace std;

//==================================//

#define JUGAR '1'
#define CONFIGURAR '2'
#define PUNTUACIO '3'
#define SORTIR '4'
#define MUR 219
#define INICI_X 4
#define INICI_Y 5
#define FIN_X 36
#define FIN_Y 25

//==================================//

void main() //Aquest és el procediment principal, inicialitza el programa i els menús permet canviar entre els diferents menús.
{
	TipusJugador MillorsJugadors[MAX_MILLORSJUGADORS];
	int nivell = 1;
	int punts = 0;
	int posicio = -1;
	char opcio;
	char Tecla;
	system("cls");
	InicialitzarTaulaMillorJugadors(MillorsJugadors);
	
	//Aquí es mostra el menú i permet escollir una opció
	
	do
	{
		MenuPrincipal();
		Tecla = _getch();
		switch (Tecla)
		{
		case JUGAR: //Aquesta opció inicia el joc.
			system("cls"); /*Aquesta linia impedeix que la pantalla principal es mostri múltiples vegades,
						   o inclús la imprimeixi infinitament.*/
			punts = joc(nivell);
			system("cls");
			posicio = ComprovarSiEsTop5(MillorsJugadors, punts);
			if ((posicio >= 0) && (posicio <= 5))
			{
				DesplacarArray(MillorsJugadors, posicio);
				EmplenarPosicioTaula(MillorsJugadors[posicio], punts);
			}
			system("cls");
			break;

		case CONFIGURAR: //Aquesta opció mostra el menú de dificultat, i permet canviar-la.
			do {
				system("cls");
				MenuNivellDificultat();
				cout << endl;
				cin >> nivell;
			} while ((nivell < 1) || (nivell > 3));
			system("cls");
			break;

		case PUNTUACIO: //Aquesta opció ens mostra la taula de millors jugadors.
			system("CLS");
			EscriuRanking(MillorsJugadors);
			system("PAUSE");
			system("cls");
			break;

		case SORTIR: //Amb aquesta opció es tanca el joc.
			system("cls");
			break;

		default: /*Amb el default fem que cada vegada que es premi una tecla "incorrecta",
				 s'esborri la pantalla per no tornar a imprimir el menú principal.*/
			system("cls");
			break;
		}
	} while (Tecla != SORTIR);
}