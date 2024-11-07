#include "../include/tablaQuejas.h"

struct NodoQueja{
  TQueja queja;
  NodoQueja* sig;
};

struct rep_tablaQuejas { 
  NodoQueja** tabla;
  int cantidad;   // Numero actual de quejas en la tabla
  int cota;       // Capacidad estimada de la tabla
};


int funcionHash(TFecha fecha, int cantEstimadas){
    return (31 * (int) mesTFecha(fecha) + (int) diaTFecha(fecha)) % cantEstimadas;
}

TablaQuejas crearTablaQuejas(int cantEstimadas) { 
  TablaQuejas nuevaTabla = new rep_tablaQuejas;
  nuevaTabla->cantidad = 0;
  nuevaTabla->cota = cantEstimadas;
  nuevaTabla->tabla = new NodoQueja*[cantEstimadas]();
  return nuevaTabla;
}

// PRE: no existe una queja con la misma fecha en la estructura.
void agregarQuejaTablaQuejas(TablaQuejas tabla, TQueja queja) {
  if (!perteneceQuejaTablaQuejas(tabla,fechaTQueja(queja))) {
    int indice = funcionHash(fechaTQueja(queja), tabla->cota);
    NodoQueja* nueva = new NodoQueja;
    nueva->queja = queja;
    nueva->sig = tabla->tabla[indice];
    tabla->tabla[indice] = nueva;
    tabla->cantidad++;
  }
}

void imprimirTablaQuejas(TablaQuejas tabla) { 
    for (int i = 0; i < tabla->cota; i++) {
        if (tabla->tabla[i] != NULL) {
            printf("Elementos en la posicion %d de la tabla:\n", i);
            NodoQueja* nodo = tabla->tabla[i];
            
            while (nodo != NULL) {
                imprimirTQueja(nodo->queja);
                nodo = nodo->sig;
            }
        } else {
            printf("No hay elementos guardados en la posicion %d de la tabla.\n", i);
        }
    }
}

bool perteneceQuejaTablaQuejas(TablaQuejas tabla, TFecha fecha) {
  int indice = funcionHash(fecha, tabla->cota);
  NodoQueja* lista = tabla->tabla[indice];

  while (lista != NULL && compararTFechas(fechaTQueja(lista->queja), fecha) != 0) {
    lista = lista->sig;
  }
  
  return lista != NULL;
}

TQueja obtenerQuejaTablaQuejas(TablaQuejas tabla, TFecha fecha) {
  int indice = funcionHash(fecha, tabla->cota);
  NodoQueja* nodo = tabla->tabla[indice];

  while (nodo != NULL) {
    if (compararTFechas(fechaTQueja(nodo->queja), fecha) == 0) {
        return nodo->queja;
    }
    nodo = nodo->sig;
  }
  
  return NULL;
}

void liberarTablaQuejas(TablaQuejas &tabla) {
  for (int i = 0; i < tabla->cota; i++) {
    NodoQueja* nodo = tabla->tabla[i];

    while (nodo != NULL) {
      NodoQueja* aBorrar = nodo;
      nodo = nodo->sig;
      liberarTQueja(aBorrar->queja); 
      delete aBorrar;
    }
  }

  delete[] tabla->tabla;
  delete tabla;
  tabla = NULL;
}
