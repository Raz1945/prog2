#include "../include/punto.h"

struct rep_punto {
  double x, y;
};

Punto crearPunto(double x, double y)  {
  Punto nuevo = new rep_punto;
  nuevo->x = x;
  nuevo->y = y;
  return nuevo; 
}

double coordX(Punto punto){ return punto->x; }

double coordY(Punto punto){ return punto->y; }

void imprimirPunto (Punto punto){
  printf("(%.2f, %.2f)\n", punto->x, punto->y); 
}

void liberarPunto (Punto &punto){
  delete punto;
  punto = NULL;
}

double distanciaEuclidiana(Punto punto1, Punto punto2) {
  double dx = coordX(punto2) - coordX(punto1);
  double dy = coordY(punto2) - coordY(punto1);
  return sqrt(dx * dx + dy * dy);
}