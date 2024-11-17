#include "../include/colaEnvios.h"

// Estructura para el Min-Heap basado en un arreglo
struct rep_cola_envios {
  TEnvio* heap;
  int cantElementos;
  int maxElementos;
  bool prioridadInversa;
};


TColaEnvios crearTColaEnvios(int N) {
  TColaEnvios nuevaCola = new rep_cola_envios;
  nuevaCola->heap = new TEnvio[N + 1];    // el +1 es para comenzar en el indice 1
  nuevaCola->cantElementos = 0;
  nuevaCola->maxElementos = N;
  nuevaCola->prioridadInversa = false;
  return nuevaCola;
}

// Aux:
int padre(int pos) {
  return pos / 2;
}

int hijoIzquierdo(int pos) {
  return 2 * pos;
}

int hijoDerecho(int pos) {
  return 2 * pos + 1;
}

// Aux: realiza el filtrado ascendente en el heap de forma recursiva.
void filtradoAscendente(int pos, TColaEnvios &colaEnvios) {
  // Verificar si no es la raíz (posición 1)
  if (pos > 1) {
    // Obtener la fecha del elemento actual y de su padre
    TFecha fechaActual = obtenerFechaTEnvio(colaEnvios->heap[pos]);
    TFecha fechaPadre = obtenerFechaTEnvio(colaEnvios->heap[padre(pos)]);

    // Determinar si se debe hacer el intercambio basado en la prioridad
    bool debeIntercambiar = colaEnvios->prioridadInversa
                            ? (compararTFechas(fechaActual, fechaPadre) < 0)  // Fecha más lejana (invertida)
                            : (compararTFechas(fechaActual, fechaPadre) > 0); // Fecha más cercana

    // Si el actual debe subir (es más prioritario que su padre)
    if (debeIntercambiar) {
      // Intercambiar el elemento con su padre
      TEnvio temp = colaEnvios->heap[pos];
      colaEnvios->heap[pos] = colaEnvios->heap[padre(pos)];
      colaEnvios->heap[padre(pos)] = temp;

      // Llamar recursivamente para continuar subiendo el elemento
      filtradoAscendente(padre(pos), colaEnvios);
    }

  }
}

void encolarEnvioTColaEnvios(TColaEnvios &colaEnvios, TEnvio envio) {
  if (colaEnvios->cantElementos < colaEnvios->maxElementos) {
    colaEnvios->cantElementos++;
    colaEnvios->heap[colaEnvios->cantElementos] = envio;

    filtradoAscendente(colaEnvios->cantElementos, colaEnvios);
  }
}


int cantidadTColaEnvios(TColaEnvios colaEnvios) { 
  return colaEnvios->cantElementos;
}

//* Cmd : imprimirColaEnvios 
void imprimirTColaEnvios(TColaEnvios colaEnvios) {
    int nivel = 1;
    int inicioNivel = 1;
    int finNivel = 1;    

    printf("Nivel %d:\n", nivel);

    for (int i = 1; i <= colaEnvios->cantElementos; i++) {
        printf(" %d) ", i); 
        imprimirTEnvio(colaEnvios->heap[i]); 
        printf("\n");

        if (i == finNivel) {
            nivel++;
            inicioNivel = finNivel + 1;
            finNivel = finNivel * 2 + 1;  // El número de nodos por nivel se duplica

            if (inicioNivel <= colaEnvios->cantElementos) {
                printf("Nivel %d:\n", nivel);
            }
        }
    }
    printf("\n"); 
}

// Aux: realiza el filtrado descendente en el heap de forma recursiva
void filtradoDescendente(int pos, TColaEnvios &colaEnvios) {
    int mayor = pos;  // Suponemos inicialmente que el mayor es el nodo actual

    if (hijoIzquierdo(pos) <= colaEnvios->cantElementos) {
        TFecha fechaIzq = obtenerFechaTEnvio(colaEnvios->heap[hijoIzquierdo(pos)]);
        TFecha fechaMayor = obtenerFechaTEnvio(colaEnvios->heap[mayor]);

        bool compararIzq = colaEnvios->prioridadInversa
                           ? compararTFechas(fechaIzq, fechaMayor) < 0  // Invertido
                           : compararTFechas(fechaIzq, fechaMayor) > 0; // Normal

        if (compararIzq) {
            mayor = hijoIzquierdo(pos);
        }
    }

    if (hijoDerecho(pos) <= colaEnvios->cantElementos) {
        TFecha fechaDer = obtenerFechaTEnvio(colaEnvios->heap[hijoDerecho(pos)]);
        TFecha fechaMayor = obtenerFechaTEnvio(colaEnvios->heap[mayor]);

        bool compararDer = colaEnvios->prioridadInversa
                           ? compararTFechas(fechaDer, fechaMayor) < 0  // Invertido
                           : compararTFechas(fechaDer, fechaMayor) > 0; // Normal

        if (compararDer) {
            mayor = hijoDerecho(pos);
        }
    }

    // Si el mayor no es el nodo actual, intercambiamos y seguimos descendiendo
    if (mayor != pos) {
        TEnvio temp = colaEnvios->heap[pos];
        colaEnvios->heap[pos] = colaEnvios->heap[mayor];
        colaEnvios->heap[mayor] = temp;

        filtradoDescendente(mayor, colaEnvios);
    }
}

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

void invertirPrioridadTColaEnvios(TColaEnvios &colaEnvio) {  
  colaEnvio->prioridadInversa = !colaEnvio->prioridadInversa;

  for (int i = colaEnvio->cantElementos / 2; i >= 1; i--)  {
    filtradoDescendente(i, colaEnvio);
  }  
}

TEnvio masPrioritarioTColaEnvios(TColaEnvios colaEnvio) { 
    return colaEnvio->heap[1];
}

int maxTColaEnvios(TColaEnvios colaEnvio) {
    return colaEnvio->maxElementos;
}