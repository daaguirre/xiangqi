#include <math.h>
#include "..\..\include\comun\Vector2D.h"


Vector2D::Vector2D(float xv,float yv)
{
	x = xv;
	y = yv;
}


Vector2D::~Vector2D(void)
{
}

void Vector2D::setXY(float px,float py){
	x = px;
	y = py;
}

Vector2D Vector2D::operator + (Vector2D &v) { 
	Vector2D res; 
	res.x=x+v.x; 
	res.y=y+v.y; 
	return res; 
}

Vector2D Vector2D::operator - (Vector2D &v) {
	Vector2D res;
	res.x = x - v.x;
	res.y = y - v.y;
	return res;
}

Vector2D Vector2D::operator *(float n){
	Vector2D res;
	res.x = n*x;
	res.y = n*y;
	return res;
}

bool Vector2D::operator == (const Vector2D& vect){
	if (x - vect.x<0.01F&&x - vect.x>-0.01F&&y - vect.y<0.01F&&y - vect.y>-0.01F)
		return true;
	return false;
}

Vector2D& Vector2D::Unitario(){
	float modulo = (float)sqrt(x*x + y*y);
	x = x / modulo;
	y = y / modulo;
	return *this;
}