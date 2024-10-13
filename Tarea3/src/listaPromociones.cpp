#include "../include/listaPromociones.h"

// Estructura de tipo TListaPromociones:
//* -  Almacenará elementos del tipo TPromocion 
//  -  y se recomienda implementarla como una lista simplemente enlazada. 
//*    La lista debe estar ordenada por fecha de inicio de la promoción.
struct rep_listaPromociones {
  TPromocion prom;
  rep_listaPromociones *sig;
};

TListaPromociones crearTListaPromocionesVacia() { 
  TListaPromociones nuevaPromo = NULL;
  return nuevaPromo; 

//note Otra manera:
  // TListaPromociones nuevaPromo = new rep_listaPromociones;
  // nuevaPromo->prom = NULL;
  // nuevaPromo->sig = NULL;
  // return nuevaPromo; 
}

//*LISTA PRECONDICION: no existe promoción con el mismo id en la lista
// todo TESTEAR 
void agregarPromocionTListaPromociones(TListaPromociones &listaPromociones, TPromocion promocion) {
  TListaPromociones nuevoNodo = new rep_listaPromociones;
  nuevoNodo->prom = promocion;

  // Caso 1 - La lista esta vacia o la nueva promocion va antes por fecha
  if (listaPromociones == NULL || fechaInicioTPromocion(listaPromociones->prom) >= fechaInicioTPromocion(promocion)) {
    nuevoNodo->sig = listaPromociones;
    listaPromociones = nuevoNodo;
  } else {
    // Caso 2 - Buscamos la posicion correcta para insertar la nueva promocion
    TListaPromociones actual = listaPromociones;
    TListaPromociones siguiente = actual->sig;

    while (siguiente != NULL && (fechaInicioTPromocion(siguiente->prom) < fechaInicioTPromocion(promocion))) {
      actual = siguiente;
      siguiente = siguiente->sig;        
    }

    nuevoNodo->sig = siguiente;
    actual->sig = nuevoNodo;
  }
}

// todo TESTEAR 
void imprimirTListaPromociones(TListaPromociones listaPromociones) {
  TListaPromociones actual = listaPromociones;

  while (actual != NULL){
    imprimirTPromocion(actual->prom);
    actual = actual->sig;
  }
}

// todo TESTEAR 
void liberarTListaPromociones(TListaPromociones &listaPromociones, bool liberarPromociones) {
  TListaPromociones actual = listaPromociones;

  while ((actual != NULL)){
    TListaPromociones temp = actual;
    liberarTPromocion(actual->prom);
    actual = actual->sig;
    delete temp;
  }

  listaPromociones = NULL;  
}

// todo TESTEAR 
bool esVaciaTListaPromociones(TListaPromociones promociones) {
  return promociones != NULL ? false : true;
}


// todo TESTEAR 
bool pertenecePromocionTListaPromociones(TListaPromociones listaPromociones, int idPromocion) {
  TListaPromociones idActual = listaPromociones;

  while (idActual != NULL && idTPromocion(listaPromociones->prom) != idPromocion){
    idActual = idActual->sig;
  }
  
  return idActual != NULL;
}

// todo Testear 
//* PRE: La promoción pertenece a la lista.
TPromocion obtenerPromocionTListaPromociones(TListaPromociones listaPromociones, int idPromocion) {
  TListaPromociones idActual = listaPromociones;

  while (idActual != NULL && idTPromocion(listaPromociones->prom) != idPromocion){
    idActual = idActual->sig;
  }
  
  return idActual->prom;
}

// todo Testear 
TListaPromociones obtenerPromocionesFinalizadas(TListaPromociones &listaPromociones, TFecha fecha) {
  TListaPromociones finalizadas = NULL;
  TListaPromociones actual = listaPromociones;
  TListaPromociones anterior = NULL;

  while (actual != NULL) {
    if (fechaFinTPromocion(actual->prom) < fecha) {
      agregarPromocionTListaPromociones(finalizadas, actual->prom);
      
      if (anterior == NULL) {
        // Caso 1 - Si estamos eliminando el primer nodo
        listaPromociones = actual->sig;
      } else {
        // Caso 2 - Si estamos eliminando un nodo en el medio o al final
        anterior->sig = actual->sig;
      }

      TListaPromociones aBorrar = actual;
      actual = actual->sig; // Avanzamos el puntero 'actual' antes de liberar el nodo 
                            // para no perder la referencia de hacia dónde apunta el siguiente nodo antes de liberar el nodo actual.      
      liberarTPromocion(aBorrar->prom);
      delete aBorrar;
    } else {
      // Si la promocion no ha finalizado, simplemente avanzamos
      anterior = actual;
      actual = actual->sig;
    }
  }

  return finalizadas;
}


// todo Testear 
TListaPromociones obtenerPromocionesActivas(TListaPromociones &listaPromociones, TFecha fecha) {
  TListaPromociones activas = NULL;
  TListaPromociones actual = listaPromociones;
  TListaPromociones anterior = NULL;


  while (actual != NULL){
    if (fechaFinTPromocion(actual->prom) >= fecha){
      agregarPromocionTListaPromociones(activas, actual->prom);

      if (anterior == NULL) {
        listaPromociones = actual->sig;
      } else {
        anterior->sig = actual->sig;
      }
      
      TListaPromociones aBorrar = actual;
      actual = actual->sig;
      liberarTPromocion(aBorrar->prom);
      delete aBorrar;      
    } else {
      anterior = actual;
      actual = actual->sig;
    }
  }
  
  return activas;
}

// todo Testear 

bool esCompatibleTListaPromociones(TListaPromociones listaPromociones, TPromocion promocion) {

  return false;
}

TListaPromociones unirListaPromociones(TListaPromociones listaPromociones1,
                                       TListaPromociones listaPromociones2) {
  return NULL;
}
