#pragma once
#include "Pieza.h"
#include "GenMovimientos.h"

class Caballo :
	public Pieza
{
public:
	Caballo();
	virtual ~Caballo();

	virtual void Dibuja(float, float, float);
	//virtual bool Mueve(float,const Vector2D&,bool);
	virtual void Movimientos();
};

