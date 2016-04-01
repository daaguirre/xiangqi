#include "..\..\include\dominio\Consejero.h"


CConsejero::CConsejero() :Pieza(){
}


CConsejero::~CConsejero()
{
}

void CConsejero::Dibuja(float r,float g, float b){
	Pieza::Dibuja(r, g, b);
}

void CConsejero::Movimientos(){
	GenMovimientos::MueveConsejero();
}