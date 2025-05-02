#ifndef PUNTO_H
#define PUNTO_H

#include <cstdio>  
#include <cstddef> 
#include <cmath> // Para sqrt

typedef struct rep_punto *Punto;

Punto crearPunto(double x, double y);

double coordX(Punto punto);

double coordY(Punto punto);

void imprimirPunto(Punto punto);

void liberarPunto(Punto &punto);

// Distancia Euclidiana en el plano entre dos puntos (x1, y1) y (x2, y2)
double distanciaEuclidiana(Punto punto1, Punto punto2);

#endif
