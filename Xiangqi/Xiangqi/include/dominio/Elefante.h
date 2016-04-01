#pragma once
#include "Pieza.h"
#include "GenMovimientos.h"

class Elefante :
	public Pieza
{
public:
	Elefante();
	virtual ~Elefante();

	virtual void Dibuja(float, float, float);
	//virtual bool Mueve(float,const Vector2D&,bool);
	virtual void Movimientos();
};

