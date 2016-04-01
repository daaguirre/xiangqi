#ifndef PIEZA_H
#define PIEZA_H
#pragma once
#include "..\comun\Vector2D.h"
#include "..\comun\glut.h"
#include "..\comun\Circunferencia.h"
#include "Intersecciones.h"
//#include "GenMovimientos.h"


class Pieza
{
public:
	Pieza();
	virtual ~Pieza();

	virtual void Dibuja(float,float,float)=0;
	virtual bool Mueve(float,const Vector2D&,bool);
	virtual void setPos(Vector2D);
	virtual void setVel(float, float);
	virtual void setAcel(float, float);
	//virtual void setOrigen(Vector2D);
	virtual Vector2D getPosicion() const { return posicion; }
	virtual bool getPicked() const { return picked; }
	virtual void setPicked(bool p){ picked = p; }
	virtual void Movimientos();

	void MovimientoContinuo(float);

private:
	//Vector2D origen;
	Vector2D aceleracion;
	Vector2D velocidad;
	Vector2D posicion;
	bool picked;
	
};
#endif
