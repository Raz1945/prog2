#include "../include/ldePerros.h"

struct AuxNodoLDE;
typedef AuxNodoLDE *nodoLDE;
struct AuxNodoLDE {
    TPerro perro;
    nodoLDE ant;
    nodoLDE sig;
};

struct rep_tldeperros {
    nodoLDE inicial;
    nodoLDE final;
    int cantidad;
};

TLDEPerros crearTLDEPerrosVacia(){
    TLDEPerros nueva = new rep_tldeperros;
    nueva->inicial = NULL;
    nueva->final = NULL;
    nueva->cantidad = 0;
    return nueva;
}

void insertarTLDEPerros(TLDEPerros &ldePerros, TPerro perro) {
  if (ldePerros != NULL) {
  nodoLDE nuevo = new AuxNodoLDE;
  nuevo->perro = perro;
  nuevo->ant = NULL;
  nuevo->sig = NULL;


  // Si la lista está vacía
  if (ldePerros->inicial == NULL) {
    ldePerros->inicial = nuevo;
    ldePerros->final = nuevo;
    ldePerros->cantidad++;
  } else {
    nodoLDE actual = ldePerros->inicial;

    // Buscar dónde insertar
    while (actual != NULL && edadTPerro(perro) > edadTPerro(actual->perro)) {
      actual = actual->sig;
    }

    // Insertar al final
    if (actual == NULL) {
      nuevo->ant = ldePerros->final;
      ldePerros->final->sig = nuevo;
      ldePerros->final = nuevo;
      ldePerros->cantidad++;
    }
    // Insertar al principio
    else if (actual == ldePerros->inicial) {
      nuevo->sig = actual;
      actual->ant = nuevo;
      ldePerros->inicial = nuevo;
      ldePerros->cantidad++;
    } 
    // Insertar en el medio
    else {
      nuevo->sig = actual;
      nuevo->ant = actual->ant;
      actual->ant->sig = nuevo;
      actual->ant = nuevo;
      ldePerros->cantidad++;
      }
    }
  }
}

// Funcion Auxiliar para liberar la memoria de un nodo
void liberarNodo(nodoLDE nodo) {
    if (nodo != NULL) {
        liberarTPerro(nodo->perro);
        delete nodo;
    }
}

void liberarTLDEPerros(TLDEPerros &ldePerros) {
    if (ldePerros != NULL) {
        nodoLDE actual = ldePerros->inicial;

        while (actual != NULL) {
            nodoLDE aBorrar = actual;
            actual = actual->sig;
            liberarNodo(aBorrar);
            ldePerros->cantidad--;
        }
        delete ldePerros;
        ldePerros = NULL;
    }
}

void imprimirTLDEPerros(TLDEPerros ldePerros){
  if (ldePerros != NULL)  {
    nodoLDE actual = ldePerros->inicial;
    printf("LDE Perros:\n");      

    while (actual != NULL)  {
      imprimirTPerro(actual->perro);
      actual = actual->sig;
    }
  }
}

void imprimirInvertidoTLDEPerros(TLDEPerros ldePerros){
  if (ldePerros != NULL)  {
    nodoLDE actual = ldePerros->final;
    printf("LDE Perros:\n");      

    while (actual != NULL)  {
      imprimirTPerro(actual->perro);
      actual = actual->ant;
    }
  }
}

nat cantidadTLDEPerros(TLDEPerros ldePerros){
  return (ldePerros == NULL) ? 0 : ldePerros->cantidad;
}

TPerro removerPerroTLDEPerros(TLDEPerros &ldePerros, int id){
  if (ldePerros != NULL && id > 0)  {
    nodoLDE actual = ldePerros->inicial;

    while (actual != NULL && idTPerro(actual->perro) != id) {
      actual = actual->sig;
    }
    
    if (actual != NULL) {
      TPerro perroARemover = actual->perro;

      // Caso 1 - No es el primer nodo
      if (actual->ant != NULL)  {
        actual->ant->sig = actual->sig; // Apuntamos el nodo anterior al 'actual' hacia el nodo siguiente al 'actual'
      } else {
        // Caso 2 - Es el primer nodo
        ldePerros->inicial = actual->sig; // Actualizamos el comienzo de la lista
      }
      
      // Caso 3 - No es el ultimo nodo
      if (actual->sig != NULL)  {
        actual->sig->ant = actual->ant; // Apuntamos el nodo siguiente al 'actual' hacia el nodo anterior al 'actual'
        // actual->sig->ant = SiguienteAlActual->ant
      } else {
        // Caso 4 - Es el ultimo nodo
        ldePerros->final = actual->ant;
      }
      
      delete actual;
      ldePerros->cantidad--;  
      return perroARemover;
    }
  }  
  return NULL;
}

TPerro obtenerPrimeroTLDEPerros(TLDEPerros ldePerros){  
  return ldePerros->inicial->perro;
}

TPerro obtenerUltimoTLDEPerros(TLDEPerros ldePerros){
  return ldePerros->final->perro;
}

// Funcion Auxiliar para obtener el perro en la posicion n (comenzando desde 1)
TPerro obtenerTLDEPerrosEnPosicion(TLDEPerros ldePerros, int n) {
  if (ldePerros != NULL && n > 0) {
    nodoLDE actual = ldePerros->inicial;
    int index = 1;

    while (actual != NULL) {
      if (index == n) {
        return actual->perro;
      }
      actual = actual->sig;
      index++;
    }
  }
  return NULL;
}

TPerro obtenerNesimoTLDEPerros(TLDEPerros ldePerros, int n){
  if (ldePerros != NULL && n > 0 && n <= ldePerros->cantidad) {
    return obtenerTLDEPerrosEnPosicion(ldePerros, n);
  }
  return NULL;
}

bool existePerroTLDEPerros(TLDEPerros ldePerros, int id){
  if (ldePerros != NULL && id > 0)  {
    nodoLDE actual = ldePerros->inicial;
    
    while (actual != NULL && idTPerro(actual->perro) != id) {
      actual = actual->sig;
    }

    return (actual != NULL);
  }
  return false;
}
