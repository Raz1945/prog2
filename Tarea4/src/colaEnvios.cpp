#include "../include/colaEnvios.h"

// Estructura para el Min-Heap basado en un arreglo
struct rep_cola_envios {
  TEnvio* heap;
  int cantElementos;
  int maxElementos;
};


TColaEnvios crearTColaEnvios(int N) {
  TColaEnvios nuevaCola = new rep_cola_envios;
  nuevaCola->heap = new TEnvio[N + 1];    // el +1 es para comenzar en el indice 1
  nuevaCola->cantElementos = 0;
  nuevaCola->maxElementos = N;
  return nuevaCola;
}

// Funciones Auxiliares:
int padre(int pos) {
  return pos / 2;
}

int hijoIzquierdo(int pos) {
  return 2 * pos;
}

int hijoDerecho(int pos) {
  return 2 * pos + 1;
}

//* Aux: realiza el filtrado ascendente en el heap de forma recursiva.
void filtradoAscendente(int pos, TColaEnvios &colaEnvios) {
    // Verificamos si pos > 1 y comparamos la fecha del nodo actual con la de su padre
    if (pos > 1) {
        TFecha fechaActual = obtenerFechaTEnvio(colaEnvios->heap[pos]);
        TFecha fechaPadre = obtenerFechaTEnvio(colaEnvios->heap[padre(pos)]);

        if (compararTFechas(fechaActual, fechaPadre) > 0) {
            // Intercambiamos el nodo actual con su padre
            TEnvio temp = colaEnvios->heap[pos];
            colaEnvios->heap[pos] = colaEnvios->heap[padre(pos)];
            colaEnvios->heap[padre(pos)] = temp;

            // Llamada recursiva con la nueva posición del nodo (el padre)
            filtradoAscendente(padre(pos), colaEnvios);
        }
    }
}

void encolarEnvioTColaEnvios(TColaEnvios &colaEnvios, TEnvio envio) {
  if (colaEnvios->cantElementos < colaEnvios->maxElementos) {
    colaEnvios->cantElementos++;
    int pos = colaEnvios->cantElementos;    // Es la ultima posicion libre
    colaEnvios->heap[pos] = envio;
    filtradoAscendente(pos, colaEnvios);
  }
}

int cantidadTColaEnvios(TColaEnvios colaEnvios) { 
  return colaEnvios->cantElementos;
}

void imprimirTColaEnvios(TColaEnvios colaEnvios) {
  int nivel = 1;
  int inicioNivel = 1;   // Primer indice de cada nivel, porque comenzamos en el indice 1
  int finNivel = 1;   // Ultimo indice de cada nivel, porque comenzamos en el indice 1

  printf("Nivel %d: \n", nivel);
  for (int i = 1; i < colaEnvios->cantElementos; i++) {
    printf("%d", i);
    imprimirTEnvio(colaEnvios->heap[i]);
    printf("\n");

    if (i == finNivel)  {
      nivel++;
      inicioNivel = finNivel + 1;
      finNivel = finNivel * 2 + 1;
      if (inicioNivel <= colaEnvios->cantElementos) {
        printf("Nivel %d:\n", nivel);
      }
    }
  }
}

//* Aux: realiza el filtrado descendente en el heap de forma recursiva
void filtradoDescendente(int pos, TColaEnvios &colaEnvios) {
    int mayor = pos;  // Suponemos inicialmente que el mayor es el nodo actual
    int izq = hijoIzquierdo(pos);
    int der = hijoDerecho(pos);

    // Verificar si el hijo izquierdo existe y tiene mayor prioridad que el nodo actual
    if (izq <= colaEnvios->cantElementos &&
        compararTFechas(obtenerFechaTEnvio(colaEnvios->heap[izq]), obtenerFechaTEnvio(colaEnvios->heap[mayor])) > 0) {
        mayor = izq;
    }

    // Verificar si el hijo derecho existe y tiene mayor prioridad que el nodo actual o el hijo izquierdo (si es mayor)
    if (der <= colaEnvios->cantElementos &&
        compararTFechas(obtenerFechaTEnvio(colaEnvios->heap[der]), obtenerFechaTEnvio(colaEnvios->heap[mayor])) > 0) {
        mayor = der;
    }

    // Si el mayor no es el nodo actual, intercambiamos y seguimos descendiendo
    if (mayor != pos) {
        TEnvio temp = colaEnvios->heap[pos];
        colaEnvios->heap[pos] = colaEnvios->heap[mayor];
        colaEnvios->heap[mayor] = temp;

        // Llamada recursiva para continuar el filtrado hacia abajo
        filtradoDescendente(mayor, colaEnvios);
    }
}

// PRE: cantidadTColaEnvios > 0
TEnvio desencolarTColaEnvios(TColaEnvios &colaEnvios) { 
  if (cantidadTColaEnvios(colaEnvios) > 0)  {
    TEnvio envio = colaEnvios->heap[1];
    colaEnvios->heap[1] = colaEnvios->heap[colaEnvios->cantElementos];
    colaEnvios->cantElementos--;
    filtradoDescendente(1, colaEnvios);
    return envio;    
  }
  return NULL;
}

void liberarTColaEnvios(TColaEnvios &colaEnvios) {
  for (int i = 1; i < colaEnvios->cantElementos; i++) {
    liberarTEnvio(colaEnvios->heap[i]); 
  }
    
  delete[] colaEnvios->heap;
  delete colaEnvios;
  colaEnvios = nullptr; 
}

//! --> Aqui
void invertirPrioridadTColaEnvios(TColaEnvios &colaEnvio) {
  
}

TEnvio masPrioritarioTColaEnvios(TColaEnvios colaEnvio) { return NULL; }

int maxTColaEnvios(TColaEnvios colaEnvio) {
    return 0;
}