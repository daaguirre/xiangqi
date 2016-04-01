#include "..\..\include\dominio\Elefante.h"


Elefante::Elefante() :Pieza(){
}


Elefante::~Elefante()
{
}

void Elefante::Dibuja(float r, float g, float b){
	Pieza::Dibuja(r, g, b);
}

void Elefante::Movimientos(){
	GenMovimientos::MueveElefante();
}
