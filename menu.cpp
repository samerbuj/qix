#include "menu.h"
#include<iostream>
using namespace std;

void MenuPrincipal() //Mostra el menú principal amb les diferents opcions que podem escollir.
{
	cout << "------Menu Principal------" << endl << endl;
	cout << "1.- Jugar" << endl;
	cout << "2.- Configurar" << endl;
	cout << "3.- Millors Puntuacions" << endl;
	cout << "4.- Sortir" << endl << endl;
	cout << "--------------------------" << endl;
}

//==================================//

void MenuNivellDificultat() //Aquest és el menú que permet canviar entre les diferents dificultats del joc.
{
	cout << "------Menu Dificultat------" << endl << endl;
	cout << "1.- Principiant" << endl;
	cout << "2.- Mitja" << endl;
	cout << "3.- Expert" << endl << endl;
	cout << "---------------------------" << endl;
}