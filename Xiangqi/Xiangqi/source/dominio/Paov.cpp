#include "..\..\include\dominio\Paov.h"


Paov::Paov():Pieza(){

}


Paov::~Paov(){

}

void Paov::Dibuja(float r, float g, float b){
	Pieza::Dibuja(r, g, b);
}

void Paov::Movimientos(){
	GenMovimientos::MuevePaov();
}