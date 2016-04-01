#include "..\..\include\comun\glut.h"
#include "..\..\include\dominio\Tablero.h"
#include <stdio.h>

Tablero tablero;

//los callback, funciones que seran llamadas automaticamente por la glut
//cuando sucedan eventos
//NO HACE FALTA LLAMARLAS EXPLICITAMENTE
void OnDraw(void); //esta funcion sera llamada para dibujar
void OnTimer(int value); //esta funcion sera llamada cuando transcurra una temporizacion
void OnKeyboardDown(unsigned char key, int x, int y); //cuando se pulse una tecla	
void OnSpecialKeyboardDown(int key, int x, int y);
void OnMouseButton(int button, int state, int x, int y);
void OnMousePassiveMotion(int x, int y);

int main(int argc, char* argv[])
{
	//Inicializar el gestor de ventanas GLUT
	//y crear la ventana
	glutInit(&argc, argv);
	glutInitWindowSize(800, 600);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutCreateWindow("MiJuego");

	//habilitar luces y definir perspectiva
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	glMatrixMode(GL_PROJECTION);
	gluPerspective(40.0, 800 / 600.0f, 0.1, 150);


	//Registrar los callbacks
	glutDisplayFunc(OnDraw);
	glutTimerFunc(25, OnTimer, 0);//le decimos que dentro de 25ms llame 1 vez a la funcion OnTimer()
	glutKeyboardFunc(OnKeyboardDown);
	glutSpecialFunc(OnSpecialKeyboardDown); //gestion de los cursores
	//interaccion con el mouse
	glutMouseFunc(OnMouseButton);

	
	//inicializacion de la escena
	tablero.Inicializa();
	
	//pasarle el control a GLUT,que llamara a los callbacks
	glutMainLoop();

	return 0;
}

void OnDraw(void)
{
	//Borrado de la pantalla	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Para definir el punto de vista
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//Dibujo de nuestro mundo
	tablero.Dibuja();
	/*glTranslatef(12, 16, 0);
	glutSolidSphere(1, 20, 20);
	glTranslatef(-21, 0, 0);
	glutSolidSphere(1, 20, 20);
	glTranslatef(21, 0, 0);
	glColor3f(255.0, 0, 0);
	glTranslatef(21, 0, 0);
	glutSolidSphere(1, 20, 20);
	glTranslatef(-21, 0, 0);
	glTranslatef(0, 32, 0);
	glutSolidSphere(1, 20, 20);
	glTranslatef(0, -32, 0);
	glTranslatef(0, -17.5, 0);
	glutSolidSphere(1, 20, 20);*/

	
	//no borrar esta linea ni poner nada despues
	glutSwapBuffers();

}
void OnKeyboardDown(unsigned char key, int x_t, int y_t)
{
	//poner aqui el código de teclado

	glutPostRedisplay();
}

void OnTimer(int value)
{
	//poner aqui el código de animacion
	tablero.Mover();
	//tablero.Seleccion();
	//no borrar estas lineas
	glutTimerFunc(25, OnTimer, 0);
	glutPostRedisplay();
}

void OnSpecialKeyboardDown(int key, int x, int y)
{
	//tablero.TeclaEspecial(key);
}

void OnMouseButton(int button, int state, int x, int y){
	tablero.OnMouse(button, state, x, y);
	
}

void OnMousePassiveMotion(int x, int y){
	

}

