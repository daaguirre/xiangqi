#pragma once
#include "Pieza.h"
#include "GenMovimientos.h"
#include "..\comun\Circunferencia.h"

class Soldado :
	public Pieza
{
public:
	Soldado();
	virtual ~Soldado();

	virtual void Dibuja(float,float,float);
	virtual bool Mueve(float,const Vector2D&,bool);
	virtual void Movimientos();
	//virtual void setPos(float,float);
	//virtual void setVel(float,float);
};

