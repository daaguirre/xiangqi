#ifndef TABLERO_H
#define TABLERO_H
#pragma once
#include "Pieza.h"
#include "Soldado.h"
#include "Torre.h"
#include "Caballo.h"
#include "Elefante.h"
#include "Paov.h"
#include "Consejero.h"
#include "..\comun\Vector2D.h"
#include "..\comun\Vector2D.h"
#include "Intersecciones.h"
#include "GenMovimientos.h"
#include <math.h>

class Tablero
{
public:
	Tablero(void);
	~Tablero(void);
	void Dibuja();
	void Inicializa();
	void TeclaEspecial(unsigned char key);
	void Mover();
	Vector2D MouseCoords(int, int);
	bool Pick(int,int, Pieza* ficha);
	void OnMouse(int, int, int, int);

	static int getNumPiezasA(){ return numPiezasA; }
	static int getNumPiezasR(){ return numPiezasR; }
	bool Pick(int, int, Vector2D);
	static Vector2D getAvanzar(){ return avanzar; }
	static bool getMoverFicha(){ return moverFicha; }


private:
	//coordenadas de la camara
	float x_ojo;
	float y_ojo;
	float z_ojo;
	Pieza **piezasA;
	Pieza **piezasR;
	Intersecciones intersecciones;
	GenMovimientos generadorMov;
	static int numPiezasA;
	static int numPiezasR;
	int mouseFunc; //segunda forma de funcionar del mouse

	static Vector2D avanzar; //almacena las coordenadas de la interseccion de destino
	static bool moverFicha;

	static Vector2D SelActual;
};

#endif

