// Ejercicio 2 - Modularizacion (o parte de este)
#include "include/punto.h"
#include <iostream>

//> Programa Principal 
int main()
  printf("¡Bienvenido!\n");
  
  printf("Dado los puntos: \n");
  Punto p1 = crearPunto(3.0, 5.5);
  Punto p2 = crearPunto(0, 9.5);
  Punto p3 = crearPunto(-2.0, 17.5);

  imprimirPunto(p1);
  imprimirPunto(p2);
  imprimirPunto(p3);

  double res1 = distanciaEuclidiana(p1, p2);
  printf("Distancia Euclidiana entre p1 y p2: %.2f\n", res1);
  
  double res2 = distanciaEuclidiana(p1, p3);
  printf("Distancia Euclidiana entre p1 y p3: %.2f\n", res2);

  double res3 = distanciaEuclidiana(p2, p3);
  printf("Distancia Euclidiana entre p2 y p3: %.2f\n", res3);

  liberarPunto(p1);
  liberarPunto(p2);
  liberarPunto(p3);
  return 0;
}

// Para correr el programa:
// g++ -o principal principal.cpp src/punto.cpp -Iinclude
// ./principal
