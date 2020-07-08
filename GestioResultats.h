#define MAX_MILLORSJUGADORS 5

typedef struct
{
	char Nom[15];
	int puntuacio;
}TipusJugador;

void InicialitzarTaulaMillorJugadors(TipusJugador MillorsJugadors[]);
int ComprovarSiEsTop5(TipusJugador MillorsJugadors[], int punts);
void DesplacarArray(TipusJugador MillorsJugadors[], int posicio);
void EmplenarPosicioTaula(TipusJugador &PosicioAOmplir, int punts);
void EscriuRanking(TipusJugador MillorsJugadors[]);