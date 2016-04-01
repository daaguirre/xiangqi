#include "..\..\include\dominio\Torre.h"


Torre::Torre() :Pieza()
{
}


Torre::~Torre()
{
}

void Torre::Dibuja(float r, float g, float b){
	Pieza::Dibuja(r, g, b);
}

void Torre::Movimientos(){
	GenMovimientos::MueveTorre();
}