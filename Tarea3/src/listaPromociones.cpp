#include "../include/listaPromociones.h"

// Estructura de tipo TListaPromociones:
//* -  Almacenará elementos del tipo TPromocion 
//  -  y se recomienda implementarla como una lista simplemente enlazada. 
//*    La lista debe estar ordenada por fecha de inicio de la promocion.
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

// check TESTEAR 
//* PRE: no existe promocion con el mismo id en la lista  
void agregarPromocionTListaPromociones(TListaPromociones &listaPromociones, TPromocion promocion) {
  TListaPromociones nuevoNodo = new rep_listaPromociones;
  nuevoNodo->prom = promocion;

  // Caso 1 - La lista está vacia o la nueva promocion va antes o es igual por fecha
  if (listaPromociones == NULL || compararTFechas(fechaInicioTPromocion(listaPromociones->prom), fechaInicioTPromocion(promocion)) >= 0) {
    nuevoNodo->sig = listaPromociones;
    listaPromociones = nuevoNodo;
  } else {
    // Caso 2 - Buscamos la posicion correcta para insertar la nueva promocion
    TListaPromociones actual = listaPromociones;
    TListaPromociones siguiente = actual->sig;

    while (siguiente != NULL && compararTFechas(fechaInicioTPromocion(siguiente->prom), fechaInicioTPromocion(promocion)) < 0) {
      actual = siguiente;
      siguiente = siguiente->sig;
    }

    // Insertamos la nueva promocion 
    nuevoNodo->sig = siguiente;
    actual->sig = nuevoNodo;
  }
}

// check TESTEAR 
void imprimirTListaPromociones(TListaPromociones listaPromociones) {
  TListaPromociones actual = listaPromociones;

  while (actual != NULL){
    imprimirTPromocion(actual->prom);
    actual = actual->sig;
  }
}

// check TESTEAR 
void liberarTListaPromociones(TListaPromociones &listaPromociones, bool liberarPromociones) {
  TListaPromociones actual = listaPromociones;

  while ((actual != NULL)){
    TListaPromociones temp = actual;
    
    // Solo liberamos la promocion si 'liberarPromociones' es true
    if (liberarPromociones) {
      liberarTPromocion(actual->prom);
    }
    
    actual = actual->sig;
    delete temp;
  }

  listaPromociones = NULL;  
}

// check TESTEAR 
bool esVaciaTListaPromociones(TListaPromociones promociones) {
  return promociones != NULL ? false : true;
}

// check TESTEAR 
bool pertenecePromocionTListaPromociones(TListaPromociones listaPromociones, int idPromocion) {
  TListaPromociones idActual = listaPromociones;

  while (idActual != NULL && idTPromocion(idActual->prom) != idPromocion){
    idActual = idActual->sig;
  }
  
  return idActual != NULL;
}

// check Testear 
//* PRE: La promocion pertenece a la lista.
TPromocion obtenerPromocionTListaPromociones(TListaPromociones listaPromociones, int idPromocion) {
  TListaPromociones idActual = listaPromociones;
  
  while (idActual != NULL && idTPromocion(idActual->prom) != idPromocion){
    idActual = idActual->sig;
  }
  return idActual->prom;
}

// check Testear 
TListaPromociones obtenerPromocionesFinalizadas(TListaPromociones &listaPromociones, TFecha fecha) {
  TListaPromociones finalizadas = NULL;
  TListaPromociones actual = listaPromociones;
  TListaPromociones anterior = NULL;

  while (actual != NULL) {
    // Verificamos si la promocion finalizo
    // Comparando que fecha de fin de la promocion actual sea mayor a la fecha dada
    if (compararTFechas(fechaFinTPromocion(actual->prom), fecha) < 0) {

      TPromocion promoAAgregar = actual->prom;
      agregarPromocionTListaPromociones(finalizadas, promoAAgregar);

      // Remover la promocion de la lista original
      if (anterior == NULL) {
        listaPromociones = actual->sig; 
      } else {
        anterior->sig = actual->sig; 
      }

      // Eliminar el nodo actual de la lista original
      TListaPromociones aBorrar = actual;
      actual = actual->sig;
      delete aBorrar;
    } else {
      anterior = actual;
      actual = actual->sig;
    }
  }

  return finalizadas;
}

// check Testear 
TListaPromociones obtenerPromocionesActivas(TListaPromociones &listaPromociones, TFecha fecha) {
  TListaPromociones activas = NULL;
  TListaPromociones actual = listaPromociones;
  TListaPromociones anterior = NULL;

  while (actual != NULL) {
    // Verificamos si la promocion esta activa
    // Comparando si la fecha de fin de la promocion actual es mayor que la fecha dada
    // y que la fecha de inicio de la promocion actual sea menor o igual a la fecha dada
    if (compararTFechas(fechaFinTPromocion(actual->prom), fecha) > 0 && 
        (compararTFechas(fechaInicioTPromocion(actual->prom), fecha) <= 0)) {

      TPromocion promoAAgregar = actual->prom;
      agregarPromocionTListaPromociones(activas, promoAAgregar);

      // Remover la promocion de la lista original
      if (anterior == NULL) {
        listaPromociones = actual->sig;
      } else {
        anterior->sig = actual->sig;
      }

      // Eliminar el nodo actual de la lista original
      TListaPromociones aBorrar = actual;
      actual = actual->sig;
      delete aBorrar;
    } else {
      anterior = actual;
      actual = actual->sig;
    }
  }

  return activas;
}

// check Testear 
bool esCompatibleTListaPromociones(TListaPromociones listaPromociones, TPromocion promocion) {
  TListaPromociones actual = listaPromociones;
  
  while (actual != NULL && sonPromocionesCompatibles(actual->prom, promocion)){
    actual = actual->sig;
  }
  
  return actual == NULL;
}

// check Testear 
//* PRE: las listas no tienen promociones en común (no tienen ids repetidos)
TListaPromociones unirListaPromociones(TListaPromociones listaPromociones1, TListaPromociones listaPromociones2) {
  TListaPromociones nuevaLista = NULL;

  // Agregar todas las promociones de la primera lista a la nueva lista
  TListaPromociones actual1 = listaPromociones1;
  while (actual1 != NULL) {
    agregarPromocionTListaPromociones(nuevaLista, actual1->prom);
    actual1 = actual1->sig;
  }

  // Agregar todas las promociones de la segunda lista a la nueva lista
  TListaPromociones actual2 = listaPromociones2;
  while (actual2 != NULL) {
    agregarPromocionTListaPromociones(nuevaLista, actual2->prom);
    actual2 = actual2->sig;
  }

  return nuevaLista;
}
