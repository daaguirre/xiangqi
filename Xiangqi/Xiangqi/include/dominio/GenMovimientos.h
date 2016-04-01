#ifndef GENMOVIMIENTOS_H
#define GENMOVIMIENTOS_H

#include "Pieza.h"
#include "Intersecciones.h"

class GenMovimientos
{
public:
	GenMovimientos();
	~GenMovimientos();

	static void MueveSoldado();
	static void MueveTorre();
	static void MuevePaov();//mueve el cañon
	static void MueveElefante();
	static void MueveCaballo();
	static void MueveGeneral();
	static void MueveConsejero();

	static void setPtrPieza(Pieza *pieza);
	static Vector2D PosToInter(int x, int y);
	static void Mapeo(Pieza *pieza[],int numPiezas);//mapeo de las fichas del tablero al ritmo de los movimientos
	static 	Vector2D InterToPos(Vector2D);//convierte intersecciones en posiciones con coords x,y
	static void DibujaAvances();
	static bool getMov() { return mov; }
	static void DestruirAvances();
	static int getPTR() { return (unsigned int)ptrPieza; }
	static void SetInterActual();
	void setAvances();
	Vector2D* getAvance();


	static Vector2D getAvanceXY(int indicador){ return avancesXY[indicador]; }
	static Vector2D* getAvanceXY(){ return avancesXY; }
	static unsigned int getPosibilidades(){ return posibilidades; }

	//funcion que determina si un par de valores 
	//son validos para la variable map[i][k]
	static bool ValorMap(int i, int k);
	//funcion que determina si un par de valores 
	//pertenecen al palacio
	static bool EnPalacio(int i, int k);

private:
	static Pieza *map[10][9];
	static Pieza *ptrPieza;//apunta a una ficha del tablero
	static unsigned int posibilidades; //posibles movimientos
	static Vector2D interActual;//interseccion en la que se encuentra la pieza
	static bool mov;// autoriza el movimiento de la ficha
	static Vector2D avances[20];
	static Vector2D avancesXY[20];
	static bool avancesPantalla;//determina si los avances deben aparecer en pantalla 
};

#endif GENMOVIMIENTOS_H

