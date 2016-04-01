#include "..\..\include\dominio\Soldado.h"


Soldado::Soldado() :Pieza(){ //llama al constructor de la clase base

}


Soldado::~Soldado(){
}

void Soldado::Dibuja(float r, float g, float b){
	Pieza::Dibuja(r,g,b);

	Circunferencia cabeza(0.0, 0.5, 0.3);//cabeza del soldado
	glColor3f(0.0, 0.0, 0.0);
	glTranslatef(getPosicion().getX(), getPosicion().getY(), 0.1);
	glBegin(GL_POLYGON);
	glVertex3f(0.5, -0.5, 1.1);
	glVertex3f(0.5, 0.5, 1.1);
	glVertex3f(-0.5, 0.5, 1.1);
	glVertex3f(-0.5, -0.5, 1.1);
	glEnd();
	glBegin(GL_POLYGON);
	for (int i = 0; i < 100; i++){
		glVertex3f(cabeza.x[i], cabeza.y[i], 1.0f);
	}
	glEnd();
	glTranslatef(-getPosicion().getX(), -getPosicion().getY(), -0.1);
	glFlush();
}

bool Soldado::Mueve(float t,const Vector2D& destino,bool validacion){
	bool testeo = false;
	testeo = Pieza::Mueve(t, destino, validacion);
	return testeo;
	Vector2D movVert = (0, 3);//movimiento vertical hacia arriba de una interseccion
}

void Soldado::Movimientos(){
	GenMovimientos::MueveSoldado();
}

/*void Soldado::setPos(float px,float py){

}*/

/*void Soldado::setVel(float vx, float vy) {

}*/
