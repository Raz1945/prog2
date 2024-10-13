#include "../include/PP_SETIEMBRE024.h"
#include <iostream>

Lista comune(Lista l1, Lista l2){
  Lista resultado = NULL;
  Lista ultimo = NULL;

  while (l1 != NULL && l2 != NULL){

    // Verificamos si hay elementos en comun entre las listas
    if (l1->dato == l2->dato) {
      Lista nuevoNodo = new nodoLista;
      nuevoNodo->dato = l1->dato;
      nuevoNodo->sig = NULL;

      if (resultado == NULL) { // La primera inserción en la lista resultado
        resultado = nuevoNodo; 
      } else {
        ultimo->sig = nuevoNodo; // Se inserta al final de la lista
      }

      // Actualizamos el puntero 'ultimo' para que apunte al nuevo nodo
      ultimo = nuevoNodo;

      l1 = l1->sig;
      l2 = l2->sig;

    } else if (l1->dato < l2->dato) {
      l1 = l1->sig;
    } else {
      l2 = l2->sig;
    }
  }
  
  return resultado;    
}

// Función para imprimir una lista
void imprimirLista(Lista l) {
    while (l != NULL) {
        std::cout << l->dato << " ";
        l = l->sig;
    }
    std::cout << std::endl;
}


void licenciar(ABB &t, int c){

  if (t != NULL) {
    if (t->codigo < c) {
      t->salario = 0;
      licenciar(t->der, c);
    }

    licenciar(t->izq, c);
  }  
}


ABB conAumento(ABB t, float piso, float aumento){
  
  if (t == NULL) return NULL;

  ABB nuevoArbol = new nodoABB;
  nuevoArbol->codigo = t->codigo;

  if (t->salario > piso) {
    nuevoArbol->salario = t->salario;
  } else {
    nuevoArbol->salario = t->salario + aumento;
  } 
  
  nuevoArbol->der = conAumento(t->der, piso, aumento);
  nuevoArbol->izq = conAumento(t->izq, piso, aumento);

  return nuevoArbol;
}


// Función para imprimir un árbol (inorden)
void imprimirABB(ABB t) {
    if (t == NULL) return;
    imprimirABB(t->izq);
    std::cout << "Código: " << t->codigo << ", Salario: " << t->salario << std::endl;
    imprimirABB(t->der);
}