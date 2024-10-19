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
  return NULL;   
}

//* PRE: no existe promocion con el mismo id en la lista  
void agregarPromocionTListaPromociones(TListaPromociones &listaPromociones, TPromocion promocion) {
  TListaPromociones nuevoNodo = new rep_listaPromociones;
  nuevoNodo->prom = promocion;
  nuevoNodo->sig = NULL;

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

void imprimirTListaPromociones(TListaPromociones listaPromociones) {
  TListaPromociones actual = listaPromociones;

  while (actual != NULL){
    imprimirTPromocion(actual->prom);
    actual = actual->sig;
  }
}

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

bool esVaciaTListaPromociones(TListaPromociones promociones) {
  return promociones == NULL;
}

bool pertenecePromocionTListaPromociones(TListaPromociones listaPromociones, int idPromocion) {
  TListaPromociones idActual = listaPromociones;

  while (idActual != NULL && idTPromocion(idActual->prom) != idPromocion){
    idActual = idActual->sig;
  }
  
  return idActual != NULL;
}

//* PRE: La promocion pertenece a la lista.
TPromocion obtenerPromocionTListaPromociones(TListaPromociones listaPromociones, int idPromocion) {
  TListaPromociones idActual = listaPromociones;
  
  while (idActual != NULL && idTPromocion(idActual->prom) != idPromocion){
    idActual = idActual->sig;
  }
  return idActual->prom;
}

TListaPromociones obtenerPromocionesFinalizadas(TListaPromociones &listaPromociones, TFecha fecha) {
    TListaPromociones finalizadas = NULL;
    TListaPromociones actual = listaPromociones;
    TListaPromociones anterior = NULL;

    while (actual != NULL) {
        TListaPromociones siguiente = actual->sig;

        // Si la promoción ha finalizado
        if (compararTFechas(fechaFinTPromocion(actual->prom), fecha) < 0) {
            // Desenganchamos el nodo de la lista original
            if (anterior == NULL) {
                listaPromociones = siguiente;
            } else {
                anterior->sig = siguiente;
            }

            // Insertamos el nodo en la lista finalizadas de manera ordenada
            TListaPromociones posInsert = finalizadas;
            TListaPromociones anteriorInsert = NULL;

            while (posInsert != NULL && compararTFechas(fechaInicioTPromocion(posInsert->prom), fechaInicioTPromocion(actual->prom)) < 0) {
                anteriorInsert = posInsert;
                posInsert = posInsert->sig;
            }

            // Enganchamos el nodo actual en la posición correcta
            if (anteriorInsert == NULL) {
                actual->sig = finalizadas;
                finalizadas = actual;
            } else {
                actual->sig = posInsert;
                anteriorInsert->sig = actual;
            }
        } else {
            anterior = actual;
        }

        actual = siguiente;
    }

    return finalizadas;
}

TListaPromociones obtenerPromocionesActivas(TListaPromociones &listaPromociones, TFecha fecha) {
  TListaPromociones activas = NULL;
  TListaPromociones actual = listaPromociones;
  TListaPromociones anterior = NULL;

  while (actual != NULL) {
      TListaPromociones siguiente = actual->sig;

      // Verificamos si la promoción está activa
      if (compararTFechas(fechaFinTPromocion(actual->prom), fecha) > 0 && 
          compararTFechas(fechaInicioTPromocion(actual->prom), fecha) <= 0) {

          // Desenganchamos el nodo de la lista original
          if (anterior == NULL) {
              listaPromociones = siguiente;
          } else {
              anterior->sig = siguiente;
          }

          // Insertamos el nodo en la lista activas de manera ordenada
          TListaPromociones posInsert = activas;
          TListaPromociones anteriorInsert = NULL;

          while (posInsert != NULL && compararTFechas(fechaInicioTPromocion(posInsert->prom), fechaInicioTPromocion(actual->prom)) < 0) {
              anteriorInsert = posInsert;
              posInsert = posInsert->sig;
          }

          // Enganchamos el nodo actual en la posición correcta
          if (anteriorInsert == NULL) {
              actual->sig = activas;
              activas = actual;
          } else {
              actual->sig = posInsert;
              anteriorInsert->sig = actual;
          }
      } else {
          anterior = actual;
      }

      actual = siguiente;
  }

  return activas;
}


bool esCompatibleTListaPromociones(TListaPromociones listaPromociones, TPromocion promocion) {
  TListaPromociones actual = listaPromociones;
  
  while (actual != NULL && sonPromocionesCompatibles(actual->prom, promocion)){
    actual = actual->sig;
  }
  
  return actual == NULL;
}

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
