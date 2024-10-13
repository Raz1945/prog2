#ifndef ESTRUCTURAS_ARBORECENTES_EJ1_H
#define ESTRUCTURAS_ARBORECENTES_EJ1_H

// Estructura de Arbol binario
struct nodoAB {
  int elem;
  nodoAB *izq, *der;
};

typedef nodoAB * AB;

// Estructura de una lista
struct nodoLista {
  int elem;
  nodoLista *sig;
};
typedef nodoLista * Lista;


AB consArbol(AB izq, AB der, int elem);

int contarElems(AB arbol);

int contarHojas(AB arbol);

int altura(AB arbol);

AB copiar(AB arbol);

void liberarArbol(AB arbol);

Lista enOrden(AB arbol);

Lista preOrden(AB arbol);

Lista postOrden(AB arbol);

bool esCamino(AB arbol, Lista l);

Lista caminoMasLargo(AB arbol);

#endif // ESTRUCTURAS_ARBORECENTES_EJ1_H
