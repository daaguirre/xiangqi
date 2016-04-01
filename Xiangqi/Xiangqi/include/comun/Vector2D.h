#ifndef _VECTOR2D_H 
#define _VECTOR2D_H

#pragma once
class Vector2D
{
public:
	Vector2D(float xv=0.0f,float yv=0.0f); // (1)
	virtual ~Vector2D();

	Vector2D operator + (Vector2D &); // (6) suma de vectores
	Vector2D operator - (Vector2D &);
	Vector2D operator *(float); // (8) producto por un escalar
	bool operator == (const Vector2D&);
	Vector2D& Unitario();
	float getX() const { return x; }
	float getY() const { return y; }
	void setXY(float, float);

private:
	float x;
	float y;

};

#endif