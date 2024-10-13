#ifndef PP_SETIEMBRE024_H
#define PP_SETIEMBRE024_H

// Estructura de Arbol binario
struct nodoABB {
  int codigo;
  float salario;
  nodoABB *izq, *der;
};

typedef nodoABB * ABB;

// Estructura de una lista
struct nodoLista {
  int dato;
  nodoLista *sig;
};
typedef nodoLista * Lista;

Lista comune(Lista l1, Lista l2);

void licenciar(ABB &t, int c);

void imprimirLista(Lista l);

ABB conAumento(ABB t, float piso, float aumento);

void imprimirABB(ABB t);

#endif // PP_SETIEMBRE024_H
