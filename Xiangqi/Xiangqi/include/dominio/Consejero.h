#pragma once
#include "Pieza.h"
#include "GenMovimientos.h"

class CConsejero :
	public Pieza
{
public:
	CConsejero();
	virtual ~CConsejero();
	virtual void Dibuja(float, float, float);
	virtual void Movimientos();

};

