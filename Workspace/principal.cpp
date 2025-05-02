// Ejercicio 5 - Algoritmo de ordenacion
// #include "include/pp.h"
#include <iostream>

// Funcion para ordenar el arreglo de manera creciente
// F -> O(n)
// rango [1 .. k]
int MAX = 5;

void Sort1_k( int *Arr, int n){
  for (int i = 0; i < MAX; i++) {
    if (A[i] > A[i + 1]) {
      swap(A[i], A[i+1]); // Intercambia las posiciones
    }
  }
  
}


//> Programa Principal 
int main() {

  return 0;
}

// Para correr el programa:
// g++ -o principal principal.cpp src/punto.cpp -Iinclude
// ./principal
