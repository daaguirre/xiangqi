#ifndef CIRCUNFERENCIA_H
#define CIRCUNFERENCIA_H
#include <math.h>
#define Pi 3.14159265

struct Circunferencia{
	float x[100];
	float y[100];
	float cx, xy, r;
	Circunferencia(float cx = 0, float cy = 0, float r = 1.5){
		for (int i = 0; i < 100; i++){
			x[i] = cx + cos(2 * Pi*i / 100)*r;
			y[i] = cy + sin(2 * Pi*i / 100)*r;
		}
	}
};
#endif
