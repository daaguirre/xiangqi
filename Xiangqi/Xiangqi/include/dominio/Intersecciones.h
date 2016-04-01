#pragma once
#ifndef INTERSECCIONES_H
#define INTERSECCIONES_H

#include "..\comun\Vector2D.h"
#include "..\comun\glut.h"

class Intersecciones
{
public:
	Intersecciones();
	~Intersecciones();

	void Inicializa(); //le da valores x,y a cada interseccion del tablero
	void Dibuja(); //dibuja las intersecciones del tablero 
	Vector2D getInterseccion(int i, int j)const{ return interseccion[i][j]; }
private:
	Vector2D interseccion[10][9];
};

#endif

