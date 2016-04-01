#include "..\..\include\dominio\Tablero.h"
#include "..\..\include\comun\glut.h"
#include <math.h>
#include <stdio.h>

//Inicializacion de los miembros static
int Tablero::numPiezasA = 13;
int Tablero::numPiezasR = 13;
Vector2D Tablero::avanzar = Vector2D(); //almacena las coordenadas de la interseccion de destino
bool Tablero::moverFicha=false;
Vector2D Tablero::SelActual = Vector2D();

Tablero::Tablero(void)
{	
	piezasA = new Pieza*[numPiezasA];
	for (int i = 0; i < numPiezasA; i++){
		if (i<5) piezasA[i] = new Soldado;//crea dinamicamente todas las piezas soldado azules
		if (i>=5 && i<7) piezasA[i] = new Torre;
		if (i >= 7 && i < 9) piezasA[i] = new Caballo;
		if (i >= 9 && i < 11) piezasA[i] = new Elefante;
		if (i >= 11 && i < 13) piezasA[i] = new CConsejero;
	}

	piezasR = new Pieza*[numPiezasR];
	for (int i = 0; i < numPiezasR; i++){
		if (i<5) piezasR[i] = new Soldado;//crea dinamicamente todas las piezas soldado azules
		if (i >= 5 && i<7) piezasR[i] = new Torre;
		if (i >= 7 && i < 9) piezasR[i] = new Caballo;
		if (i >= 9 && i < 11) piezasR[i] = new Elefante;
		if (i >= 11 && i < 13) piezasR[i] = new CConsejero;
	}
	mouseFunc = 1;
}


Tablero::~Tablero(void)
{
	for (int i = 0; i < numPiezasA; i++)
		delete piezasA[i]; //borra las piezas

	for (int i = 0; i < numPiezasR; i++)
		delete piezasR[i]; //borra las piezas
}

void Tablero::Inicializa() 
{
	//posicion del ojo
	x_ojo = 12.0F;
	y_ojo = -15.0F; 
	z_ojo = 30.0F;

	intersecciones.Inicializa();
	//posiciona correctamente a cada soldado en el tablero
	for (int i = 0; i < numPiezasA; i++){
		if (i < 5)
			piezasA[i]->setPos(intersecciones.getInterseccion(3, 2 * i));//2*i es porque las piezas van intercaladas
		if (i >= 5 && i<7)
			piezasA[i]->setPos(intersecciones.getInterseccion(0, (i - 5) * 8));//torre se situa en interseccion [0][0] y [0][8]
		if (i >= 7 && i < 9)
			piezasA[i]->setPos(intersecciones.getInterseccion(0, 6 * i - 41));//Caballo situado en interseccion [0][1] y [0][7]
		if (i >= 9 && i < 11)
			piezasA[i]->setPos(intersecciones.getInterseccion(0, 4 * i - 34));//Elefentes situados en interseccion [0][2] y [0][6]
		if (i >= 11 && i < 13)
			piezasA[i]->setPos(intersecciones.getInterseccion(0, 2 * i - 19));//Consejeros situados en interseccion [0][2] y [0][6]
	}

	for (int i = 0; i < numPiezasR; i++){
		if (i < 5)
			piezasR[i]->setPos(intersecciones.getInterseccion(6, 2 * i));//2*i es porque las piezas van intercaladas
		if (i >= 5 && i<7)
			piezasR[i]->setPos(intersecciones.getInterseccion(9, (i - 5) * 8));//torre se situa en interseccion [9][0] y [9][8]
		if (i >= 7 && i < 9)
			piezasR[i]->setPos(intersecciones.getInterseccion(9, 6 * i - 41));//Caballo situado en interseccion [9][1] y [9][7]
		if (i >= 9 && i < 11)
			piezasR[i]->setPos(intersecciones.getInterseccion(9, 4 * i - 34));//Elefentes situados en interseccion [9][2] y [0][6]
		if (i >= 11 && i < 13)
			piezasR[i]->setPos(intersecciones.getInterseccion(9, 2 * i - 19));//Consejeros situados en interseccion [9][2] y [9][6]
	}
	
	//inicializacion del mapeo
	GenMovimientos::Mapeo(piezasA,numPiezasA);
	GenMovimientos::Mapeo(piezasR,numPiezasR);
}

void Tablero::Dibuja()
{
	gluLookAt(x_ojo, y_ojo, z_ojo, 12.0, 14.5, 0.0,  
		0.0, 1.0, 0.0); 
	//dibuja intersecciones en el tablero
	intersecciones.Dibuja();
	//dibuja los soldados en el tablero 
	for (int i = 0; i < numPiezasA; i++){
		piezasA[i]->Dibuja(0.0F,0.0F,255.0F);	
	}

	for (int i = 0; i < numPiezasR; i++){
		piezasR[i]->Dibuja(255.0F, 0.0F, 0.0F);
	}
	if (GenMovimientos::getMov()) GenMovimientos::DibujaAvances();
}
void Tablero::Mover(){
	//mapeo de las fichas del tablero al ritmo que se producen los movimientos
	GenMovimientos::Mapeo(piezasA, numPiezasA);
	GenMovimientos::Mapeo(piezasR,numPiezasR);
	//movimiento fichas
	Vector2D* gestion = 0;
	int cont = 0;
	for (int i = 0; i < numPiezasA; i++){
		if (moverFicha)
			piezasA[i]->Mueve(0.025f, avanzar, moverFicha);

	}

	for (int i = 0; i < numPiezasR; i++){
		if (moverFicha){
			piezasR[i]->Mueve(0.025f, avanzar, moverFicha);
		}
	}

}

// Interaccion con las flechas del teclado(si es necesario)
void Tablero::TeclaEspecial(unsigned char key){

}



//convierte las coordenadas del mouse respecto de la pantalla
//a coordendas virtuales. Devuelve un vector2d con las coordenadas xy.
//px0,px3,px6...representan los valores que toma la coordenada x virtual en el tablero
//px0->x=0;px3->x=3...
//esto se hace asi porque por ejemplo la coordenada virtual x=0 toma valores
//desde 92 a 218 de la coordenada X en coordenadas de la `pantalla. 
//Por ejemplo para la interseccion (0,0) se tienen (92,564) en coordenadas de pantalla
//para (0,3) se tiene (114,496) en coordenadas de pantalla
// en el caso anterior la coordenada X de la pantalla deberia mantenerse constante pero no lo hace por eso 
// se han ciertos valores en coordenadas de pantalla que toma el punto virtual x=0
// con estos valores se ha hecho ha sacado una recta por minimos cuadrados 
Vector2D Tablero::MouseCoords(int x, int y){
	int d = 30;//establece el rango de valores en el que pueden estar los distintos px para establecer un valor entero de la coordenada x
	int wx=0, wy;//coordenadas virtuales
	int px0 = -0.2706*y + 246.96;//con esta funcion se saca x de la pantalla a partir de y de la pantalla (valores que toma wx=0)
	int px3 = -0.213*y + 286.47;//valores que toma wx=3 en coordenadas de la pantalla
	int px6 = -0.1428*y + 324.44;//valores que toma wx=6 en coordenadas de la pantalla
	int px9 = -0.0711*y + 362.03;//valores que toma wx=9 en coordenadas de la pantalla
	int px15 = 0.0685*y + 438.18;//valores que toma wx=15 en coordenadas de la pantalla
	int px18 = 0.1457*y + 474.59;//valores que toma wx=18 en coordenadas de la pantalla
	int px21 = 0.2093*y + 514.35;//valores que toma wx=21 en coordenadas de la pantalla
	int px24 = 0.2808*y + 547.74;//valores que toma wx=24 en coordenadas de la pantalla

	if ((x<px0 + d) && (x>px0 - d)) wx = 0;
	if ((x<px3 + d) && (x>px3 - d)) wx = 3;
	if ((x<px6 + d) && (x>px6 - d)) wx = 6;
	if ((x<px9 + d) && (x>px9 - d)) wx = 9;
	if ((x<px15 + d) && (x>px15 - d)) wx = 15;
	if ((x<px18 + d) && (x>px18 - d)) wx = 18;
	if ((x<px21 + d) && (x>px21 - d)) wx = 21;
	if ((x<px24 + d) && (x>px24 - d)) wx = 24;
	if ((x<399 + d) && (x>399 - d)) wx = 12;//wx=12 siempre toma 399 en coordenadas de pantalla  

	//funcion de segundo grado que convierte los puntos y de pantalla en 
	//puntos y de las coordenadas virtuales
	wy = 0.00008408781 * y*y - 0.1258089880* y + 44.5343757457;
	if (wy == 2 || wy == 5 || wy == 8 || wy==11) ++wy;//compensacion para tener mayor precision 
	
	Vector2D mouse;//vector que alamacena las coordenadas virtuales
	mouse.setXY(wx, wy);
	return mouse;
}

//si se hace click en la ficha se dice que esta seleccionada
//para que una ficha este seleccionada se debe pinchar en una zona cuadrada
//de lado el radio de la ficha con centro en el centro de la circunferencia de la ficha 
bool Tablero::Pick(int px,int py,Pieza *ficha){
	Vector2D mousePoint = MouseCoords(px, py);
	//puntos frontera(definen el cuadrado de seleccion)
	float bottom = ficha->getPosicion().getY() - 1.5;
	float left = ficha->getPosicion().getX() - 1.5;
	float top = ficha->getPosicion().getY() + 1.5;
	float right = ficha->getPosicion().getX() + 1.5;
	if ((mousePoint.getX() > left) && (mousePoint.getY() > bottom)
		&& (mousePoint.getX() < right) && (mousePoint.getY() < top))
			return true;//si la ficha esta seleccionado devuelve true
	else
		return false;
}

//funcion del mouse
void Tablero::OnMouse(int button, int state, int x, int y){
	//el mouse tendra 2 formas de funcionar si se ha dado antes click o no
	bool Seleccionado1[13] = { false };
	bool Seleccionado2[13] = { false };
	for (int i = 0; i  < numPiezasA; i++){
		Seleccionado1[i] = Pick(x, y, piezasA[i]);
	}

	for (int i = 0; i < numPiezasR; i++){
		Seleccionado2[i] = Pick(x, y, piezasR[i]);
	}
	switch (mouseFunc)
	{
	case 1:
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
			for (int j = 0; j < numPiezasA; j++){
				if (Seleccionado1[j]){
					piezasA[j]->setPicked(Seleccionado1[j]);
					glutPostRedisplay();
					mouseFunc = 2;
					break;
				}
			}

			//cuando se haga click sobre una ficha el apuntador 
			//ptrPieza de la clase GenMovimientos apuntara sobre esa ficha
			for (int k = 0; k < numPiezasA; k++){
				if (piezasA[k]->getPicked()){
					GenMovimientos::setPtrPieza(piezasA[k]);
					GenMovimientos::SetInterActual();
					piezasA[k]->Movimientos();
					break;
				}
			}

			for (int j = 0; j < numPiezasR; j++){
				if (Seleccionado2[j]){
					piezasR[j]->setPicked(Seleccionado2[j]);
					glutPostRedisplay();
					mouseFunc = 2;
					break;
				}
			}

			//cuando se haga click sobre una ficha el apuntador 
			//ptrPieza de la clase GenMovimientos apuntara sobre esa ficha
			for (int k = 0; k < numPiezasR; k++){
				if (piezasR[k]->getPicked()){
					GenMovimientos::setPtrPieza(piezasR[k]);
					GenMovimientos::SetInterActual();
					piezasR[k]->Movimientos();
					break;
				}
			}
			//generadorMov.MueveSoldado();
			glutPostRedisplay();
		}
		break;

	case 2:
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
			bool movimientos = false;//es true cuando se selecciona un punto rojo
			for (int i = 0; i < GenMovimientos::getPosibilidades(); i++){
				if (movimientos = Pick(x, y, GenMovimientos::getAvanceXY()[i])){//si se selecciona el punto rojo se guarda su posicion en avanzar
					avanzar.setXY(GenMovimientos::getAvanceXY()[i].getX(), GenMovimientos::getAvanceXY()[i].getY());
					moverFicha = true;
					break;//sale del ciclo for
				}
				else
					moverFicha = false;
			}
			printf("\nAvanzar a: (%f, %f)\n", avanzar.getX(),avanzar.getY());//imprime en pantalla avanzar a ...
			GenMovimientos::DestruirAvances();//destruye avances y pone su vector a 0
			glutPostRedisplay();//redibuja pantalla
			mouseFunc = 1;//vuelve al modo 1 del mouse
			for (int k = 0; k < numPiezasA; k++)
				piezasA[k]->setPicked(false);
			for (int k = 0; k < numPiezasR; k++)
				piezasR[k]->setPicked(false);
		}
		break;
	}


	printf("mouse: %d", mouseFunc);

}

bool Tablero::Pick(int ax, int ay, Vector2D aux){//ax y ay son las coordenadas del mouse en pantalla
	Vector2D mousePosition = MouseCoords(ax, ay);//coordenadas virtuales del mouse
	//forman el cuadrado de seleccion, si se hace click sobre este cuadrado 
	//se dice que esta seleccionado
	float bottom, left, top, right;
	bottom = aux.getY() - 0.5;
	left = aux.getX() - 0.5;
	top = aux.getY() + 0.5;
	right = aux.getX() + 0.5;
	if ((mousePosition.getX() > left) && (mousePosition.getY() > bottom)
		&& (mousePosition.getX() < right) && (mousePosition.getY() < top))
		return true;//si la posibilidad esta seleccionado devuelve true
	else
		return false;
}









