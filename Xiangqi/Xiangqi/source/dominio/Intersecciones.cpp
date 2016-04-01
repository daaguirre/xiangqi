#include "..\..\include\dominio\Intersecciones.h"


Intersecciones::Intersecciones()
{
}


Intersecciones::~Intersecciones()
{
}

void Intersecciones::Inicializa(){
	//se le asigna a cada interseccion del tablero una posicion 
	for (int i = 0; i<10; i++){
		for (int j = 0; j<9; j++){
			Vector2D horizontal(3.0f, 0.0f);//vector director de las horizontales del tablero
			Vector2D vertical(0, 3.0f);//vector director de las verticales del tablero
			Vector2D verticalFondo(0, 4.0f);//vector director de la vertical del tablero del fondo
			Vector2D rio(0, -4.0f);//separacion en el tablero provocada por el rio
			if (i>4)
				interseccion[i][j] = verticalFondo*i + horizontal*j + rio;
			else
				interseccion[i][j] = vertical*i + horizontal*j;
		}
	}
}

void Intersecciones::Dibuja(){
	//El talero se divide en dos cuadrantes(el del fondo y el mas cercano)
	//dibuja el cuadrante mas cercano
	glColor3f(255.0f, 255.0f, 255.0f); //color blanco (provisional)
	glPushMatrix();
	glBegin(GL_POLYGON); //dibuja la primera mitad del tablero
	glVertex3f(interseccion[0][0].getX(), interseccion[0][0].getY(), 0);
	glVertex3f(interseccion[4][0].getX(), interseccion[4][0].getY(), 0);
	glVertex3f(interseccion[4][8].getX(), interseccion[4][8].getY(), 0);
	glVertex3f(interseccion[0][8].getX(), interseccion[0][8].getY(), 0);
	glEnd();
	//dibuja el duadrante del fondo
	glColor3f(255.0f, 255.0f, 255.0f);
	glBegin(GL_POLYGON);
	glVertex3f(interseccion[5][0].getX(), interseccion[5][0].getY(), 0);
	glVertex3f(interseccion[9][0].getX(), interseccion[9][0].getY(), 0);
	glVertex3f(interseccion[9][8].getX(), interseccion[9][8].getY(), 0);
	glVertex3f(interseccion[5][8].getX(), interseccion[5][8].getY(), 0);
	glEnd();
	//provisionalmente el rio es un rectangulo negro
	//Dibujo de las rectas del tablero
	for (int i = 0; i < 10; i++){
		glColor3f(0.0f, 0.0f, 0.0f);
		if (i < 9){ //rectas verticales(9 rectas)
			glBegin(GL_LINES);
			glVertex3f(interseccion[0][i].getX(), interseccion[0][i].getY(), 0.1f);
			glVertex3f(interseccion[4][i].getX(), interseccion[4][i].getY(), 0.1f);
			glEnd();
			glBegin(GL_LINES);
			glVertex3f(interseccion[5][i].getX(), interseccion[5][i].getY(), 0.1f);
			glVertex3f(interseccion[9][i].getX(), interseccion[9][i].getY(), 0.1f);
			glEnd();
		}
		//rectas horizantales (10 rectas)
		glColor3f(0.0f, 0.0f, 0.0f);
		glBegin(GL_LINES);
		glVertex3f(interseccion[i][0].getX(), interseccion[i][0].getY(), 0.01f);
		glVertex3f(interseccion[i][8].getX(), interseccion[i][8].getY(), 0.01f);
		glEnd();
	}
	glPopMatrix();
}
