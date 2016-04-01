#pragma once
#include "Pieza.h"
#include "Tablero.h"

class Torre :
	public Pieza
{
public:
	Torre();
	virtual ~Torre();

	virtual void Dibuja(float,float,float);
	virtual void Movimientos();
};

