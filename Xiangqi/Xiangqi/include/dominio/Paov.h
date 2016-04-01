#pragma once
#include "Pieza.h"
#include "GenMovimientos.h"

//Canon
class Paov :
	public Pieza
{
public:
	Paov();
	virtual ~Paov();
	virtual void Dibuja(float, float, float);
	virtual void Movimientos();
};

