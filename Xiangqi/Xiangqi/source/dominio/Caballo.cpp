#include "..\..\include\dominio\Caballo.h"


Caballo::Caballo() :Pieza(){
}


Caballo::~Caballo()
{
}

void Caballo::Dibuja(float r, float g, float b){
	Pieza::Dibuja(r, g, b);
}

void Caballo::Movimientos(){
	GenMovimientos::MueveCaballo();
}
