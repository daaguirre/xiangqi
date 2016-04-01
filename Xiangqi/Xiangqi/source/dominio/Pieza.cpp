#include "..\..\include\dominio\Pieza.h"

Pieza::Pieza() 
{
	picked = false;
	posicion.setXY(0.0F, 0.0F);
	velocidad.setXY(0.0F, 0.0F);
	aceleracion.setXY(0.0F, 0.0F);
}


Pieza::~Pieza()
{
}

void Pieza::Dibuja(float r, float g, float b){
	float red = r;
	float green = g;
	float blue = b;
	float radio = 1.0F;
	GLUquadricObj *qobj;
	qobj = gluNewQuadric();
	gluQuadricDrawStyle(qobj, GLU_FILL);
	Circunferencia circunferencia(0,0,radio);
	if (picked){
		r = 0.0F;
		g = 255.0F;
		b = 0.0F;
	}
	else{
		r = red;
		g = 0.0F;
		b = blue;
	}
	glPushMatrix();
		glColor3f(r, g, b);
		glTranslatef(posicion.getX(), posicion.getY(), 0);
		gluCylinder(qobj, radio, radio, 1, 20, 20); //(quadricobj*,radioBase, radioTapa, altura, segmentos,anillos)*/
		glBegin(GL_POLYGON);
		for (int i = 0; i < 100; i++){
			glVertex3f(circunferencia.x[i], circunferencia.y[i],1.0f);
		}
		glEnd();
		glFlush();
		glTranslatef(-posicion.getX(), -posicion.getY(), 0);
	glPopMatrix();
}

//establece el origen de la pieza pasandole un vector posicion 
void Pieza::setPos(Vector2D pos){
	posicion.setXY(pos.getX(), pos.getY());
}

bool Pieza::Mueve(float t,const Vector2D& destino,bool validacion){
	bool mov_realizado=false;
	if (validacion){
		Vector2D posicion_final;
		posicion_final.setXY(destino.getX(), destino.getY());
		Vector2D velocidad_unitario = (posicion_final - posicion).Unitario();
		setVel(velocidad_unitario.getX(), velocidad_unitario.getY());
		Vector2D Punto_medio = Vector2D((posicion.getX() + posicion_final.getX()) / 2, (posicion.getY() + posicion_final.getY()) / 2);
		if (posicion == Punto_medio)
			aceleracion = Vector2D()-aceleracion;
		if (posicion == posicion_final){
			mov_realizado = true;
			setVel(0.0F, 0.0F);
		}
		MovimientoContinuo(t);
	}

	else
		mov_realizado = false;

	return mov_realizado;
}


void Pieza::setVel(float vx, float vy){
	velocidad.setXY(vx, vy);
}

void Pieza::setAcel(float ax, float ay){
	aceleracion.setXY(ax, ay);
}

void Pieza::Movimientos(){

}


//Metodo que implementa de forma adecuada el movimiento fluido de cada pieza siguiendo las leyes de la cinematica
void Pieza::MovimientoContinuo(float tiempo){
	velocidad = velocidad + aceleracion*tiempo;
	posicion = posicion + velocidad*tiempo + aceleracion*(0.5*tiempo*tiempo);
}
