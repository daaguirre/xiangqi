#include "..\..\include\dominio\GenMovimientos.h"
#include <math.h>
#include <stdio.h>
#define Pi 3.14159265

//inicializacion de los atributos static
Pieza* GenMovimientos::map[10][9] = { 0 };
Pieza* GenMovimientos::ptrPieza = { 0 };
unsigned int GenMovimientos::posibilidades = 0;
Vector2D GenMovimientos::avances[20] = { 0 };
Vector2D GenMovimientos::avancesXY[20] = { 0 };
bool GenMovimientos::mov = false;
Vector2D GenMovimientos::interActual = 0;
bool GenMovimientos::avancesPantalla = false;

GenMovimientos::GenMovimientos()
{
	for (int i = 0; i < 10; i++){
		for (int j = 0; j < 9;j++)
			map[i][j] = 0;//se inicializa la matriz de punteros que sirve para mapear las piezas del tablero
	}
}


GenMovimientos::~GenMovimientos()
{
}

void GenMovimientos::setPtrPieza(Pieza *pieza){
	ptrPieza = pieza;
}

//convierte posiciones x,y en intersecciones[i][k]
Vector2D GenMovimientos::PosToInter(int x, int y){
	int i, k;//indices de la matriz intersecciones
	//printf("x,y: %d, %d\n", x, y);
	Vector2D interseccion; //vector con los indices de la interseccion
	if (y <= 12){
		k = x / 3;
		i = y / 3;
		//printf("\n i,k: %d, %d\n", i, k);
		interseccion.setXY((float)i, (float)k);
		//printf("interseccion: %f, %f\n", interseccion.getX(), interseccion.getY());
		return interseccion;
	}
	if (y >= 16){
		k = x / 3;
		i = 1 + (y / 4);
		interseccion.setXY(i, k);
		return interseccion;
	}
}

//rastreo de las posiciones de las piezas en el tablero
void GenMovimientos::Mapeo(Pieza *pieza[],int numPiezas){
	Vector2D interM;//almacena las intersecciones
	for (int j = 0; j < numPiezas; j++){
		interM = PosToInter(pieza[j]->getPosicion().getX(), pieza[j]->getPosicion().getY());
		map[int(interM.getX())][int(interM.getY())] = pieza[j];
	}
}

//convierte intersecciones[i][k] en posiciones x,y
Vector2D GenMovimientos::InterToPos(Vector2D inter){
	Vector2D pos;//almacena la posicion
	float x, y;
	x = inter.getY() * 3;
	if (inter.getX() < 5) y = inter.getX() * 3;
	else y = (inter.getX() * 4)-4;
	pos.setXY(x, y);
	return pos;
}

void GenMovimientos::MueveSoldado(){
	bool rio=false; //dice si soldado ha cruzado el rio
	//interActual = PosToInter(ptrPieza->getPosicion().getX(), ptrPieza->getPosicion().getY());
	//printf("\n posicion: %f, %f \n", ptrPieza->getPosicion().getX(), ptrPieza->getPosicion().getY());
	if (interActual.getX() >= 5) rio = true;
	if (rio) posibilidades = 3;
	else posibilidades = 1;
	int movi = 1;//autoriza el movimiento en el indice i de la interseccion (intersecciones[i][k])
	int movk = 1;//autoriza movimiento hacia la izquierda
	for (int j = 0; j < posibilidades; j++){
		if (j != 0) movi = 0;
		if (j == 2)movk = -0.5;
		avances[j].setXY(interActual.getX() + (j + 1)*movi, interActual.getY() + j*movk);
	}
	//avance.setXY(interActual.getX() + 1, interActual.getY())
	for (int k = 0; k < posibilidades; k++){
		if (map[int(avances[k].getX())][int(avances[k].getY())] == 0) {
			mov = true;
			 avancesXY[k]= InterToPos(avances[k]); //avance en coordenadas x,y
		}
	}

	avancesPantalla = true;
}

void GenMovimientos::MueveTorre(){
	posibilidades = 0; //me aseguro de que posibilidades este en 0
	int i = interActual.getX();//interseccion[i][k]
	int k = interActual.getY();
	int up = 1, down = -1, left = -1, right = 1;
	bool NoUp = false, NoDown = false, NoLeft = false, NoRight = false;
	while (1){
		//analiza poisibilidades en la vertical hacia arriba
		if (map[i + up][k] == 0 && ValorMap(i + up, k)) {
			avances[posibilidades].setXY(i + up, k);
			posibilidades++;
			up++;
		}
		else NoUp = true;//no hay mas posibilidades en la vertical hacia arriba

		//analiza poisibilidades en la vertical hacia abajo
		if (map[i + down][k] == 0 && ValorMap(i + down, k)) {
			avances[posibilidades].setXY(i + down, k);
			posibilidades++;
			down--;
		}
		else NoDown = true;//no hay mas posibilidades en la vertical hacia arriba

		//analiza poisibilidades en la horizontal a la izquierda
		if (map[i][k + left] == 0 && ValorMap(i, k + left)) {
			avances[posibilidades].setXY(i, k + left);
			posibilidades++;
			left--;
		}
		else NoLeft = true;//no hay mas posibilidades en la horizantal hacia la izquierda

		//analiza poisibilidades en la horizontal a la derecha
		if (map[i][k + right] == 0 && ValorMap(i, k + right)) {
			avances[posibilidades].setXY(i, k + right);
			posibilidades++;
			right++;
		}
		else NoRight = true;//no hay mas posibilidades en la horizantal hacia la izquierda

		if (NoUp && NoDown && NoLeft && NoRight) break;
	}

	for (int k = 0; k < posibilidades; k++){
		avancesXY[k] = InterToPos(avances[k]); //avance en coordenadas x,y
	}
	mov = true;
	avancesPantalla = true;//permite que los avances aparezcan en pantalla

}

void GenMovimientos::MuevePaov(){
	
}

void GenMovimientos::MueveElefante(){
	posibilidades = 0; //me aseguro de que posibilidades este en 0
	int i = interActual.getX();//interseccion[i][k]
	int k = interActual.getY();
	if (map[i + 2][k + 2] == 0 && GenMovimientos::ValorMap(i + 2, k + 2)){//movimiento en diagonal arriba a la derecha
		avances[posibilidades].setXY(i + 2, k + 2);
		posibilidades++;
	}
	if (map[i - 2][k - 2] == 0 && GenMovimientos::ValorMap(i - 2, k - 2)){//diagonal abajo a la izquierda
		avances[posibilidades].setXY(i - 2, k - 2);
		posibilidades++;
	}
	if (map[i + 2][k - 2] == 0 && GenMovimientos::ValorMap(i + 2, k - 2)){//diagonal arriba a la izquierda
		avances[posibilidades].setXY(i + 2, k - 2);
		posibilidades++;
	}
	if (map[i - 2][k + 2] == 0 && GenMovimientos::ValorMap(i - 2, k + 2)){//diagonal abajo a la derecha
		avances[posibilidades].setXY(i - 2, k + 2);
		posibilidades++;
	}
	for (int k = 0; k < posibilidades; k++){
		avancesXY[k] = InterToPos(avances[k]); //avance en coordenadas x,y
	}
	mov = true;
	avancesPantalla = true;//permite visualizar los avances en pantalla

}

void GenMovimientos::MueveCaballo(){
	posibilidades = 0; //me aseguro de que posibilidades este en 0
	int i = interActual.getX();//interseccion[i][k]
	int k = interActual.getY();
	int up = i + 1, down = i - 1, left = k - 1, right = k + 1;


	if (map[up][k] == 0 && ValorMap(up, k)) {
		for (int j = 0; j < 2; j++){
			if ((map[up + 1][k - 1 + (2 * j)] == 0 && ValorMap(up + 1, k - 1 + (2 * j)))){
				avances[posibilidades].setXY(up + 1, k - 1 + (2 * j));
				posibilidades++;
			}
		}
	}
	if (map[down][k] == 0 && ValorMap(down, k)) {
		for (int j = 0; j = 2; j++){
			if ((map[down - 1][k - 1 + (2 * j)] == 0 && ValorMap(down - 1, k - 1 + (2 * j)))){
				avances[posibilidades].setXY(down - 1, k - 1 + (2 * j));
				posibilidades++;
			}
		}
	}
	if (map[i][left] == 0 && ValorMap(i, left)) {
		for (int j = 0; j = 2; j++){
			if ((map[i - 1 + (2 * j)][left - 1] == 0 && ValorMap(i - 1 + (2 * j), left - 1))){
				avances[posibilidades].setXY(i - 1 + (2 * j), left - 1);
				posibilidades++;
			}
		}
	}
	if (map[i][right] == 0 && ValorMap(i, right)) {
		for (int j = 0; j = 2; j++){
			if ((map[i - 1 + (2 * j)][right + 1] == 0 && ValorMap(i - 1 + (2 * j), right + 1))){
				avances[posibilidades].setXY(i - 1 + (2 * j), right + 1);
				posibilidades++;
			}
		}
	}
	for (int k = 0; k < posibilidades; k++){
		avancesXY[k] = InterToPos(avances[k]); //avance en coordenadas x,y
	}
	//permiten visualizar los avances en pantalla
	mov = true;
	avancesPantalla = true;
}

void GenMovimientos::MueveConsejero(){
	posibilidades = 0; //me aseguro de que posibilidades este en 0
	int i = interActual.getX();//interseccion[i][k]
	int k = interActual.getY();
	for (int j = 0; j < 2; j++){
		if ((map[i + 1][k - 1 + (2 * j)] == 0 && EnPalacio(i + 1, k - 1 + (2 * j)))){
			avances[posibilidades].setXY(i + 1, k - 1 + (2 * j));
			posibilidades++;
		}
		if ((map[i - 1][k - 1 + (2 * j)] == 0 && EnPalacio(i - 1, k - 1 + (2 * j)))){
			avances[posibilidades].setXY(i - 1, k - 1 + (2 * j));
			posibilidades++;
		}
		if ((map[i - 1 + (2 * j)][k - 1] == 0 && EnPalacio(i - 1 + (2 * j), k - 1))){
			avances[posibilidades].setXY(i - 1 + (2 * j), k - 1);
			posibilidades++;
		}
		if ((map[i - 1 + (2 * j)][k + 1] == 0 && EnPalacio(i - 1 + (2 * j), k + 1))){
			avances[posibilidades].setXY(i - 1 + (2 * j), k + 1);
			posibilidades++;
		}
	}

	for (int k = 0; k < posibilidades; k++){
		avancesXY[k] = InterToPos(avances[k]); //avance en coordenadas x,y
	}
	//permiten visualizar los avances en pantalla
	mov = true;
	avancesPantalla = true;
}

void GenMovimientos::MueveGeneral(){

}



void GenMovimientos::DibujaAvances(){
	if (avancesPantalla){
		for (int i = 0; i < posibilidades; i++){
			float x[100];
			float y[100];
			for (int j = 0; j < 100; j++){
				x[j] = avancesXY[i].getX() + cos(2 * Pi*j / 100)*0.5;
				y[j] = avancesXY[i].getY() + sin(2 * Pi*j / 100)*0.5;
			}
			glPushMatrix();
			glColor3f(255.0f, 0.0f, 0.0f);
			glBegin(GL_POLYGON);
			for (int k = 0; k < 100; k++){
				glVertex3f(x[k], y[k], 0.2f);
			}
			glEnd();
			glFlush();

			glPopMatrix();
		}
	}
}

void GenMovimientos::DestruirAvances(){
	avancesPantalla = false;
	for (int k = 0; k < posibilidades; k++){
			avancesXY[k]=NULL;
			avances[k] =NULL;
	}
}

void GenMovimientos::SetInterActual(){
	interActual = PosToInter(ptrPieza->getPosicion().getX(), ptrPieza->getPosicion().getY());
}

bool GenMovimientos::ValorMap(int i, int k){
	if (i < 10 && i >= 0 && k < 9 && k >= 0) return true;
	else return false;
}

bool GenMovimientos::EnPalacio(int i, int k){
	if (i < 3 && i >= 0 && k < 6 && k >= 3) return true;
	else return false;
}