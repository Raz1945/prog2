#include "../include/tablaQuejas.h"

struct rep_tablaQuejas { 
  NodoQueja** tabla;
  int cantidad;   // Numero actual de quejas en la tabla
  int cota;       // Capacidad estimada de la tabla
};

struct NodoQueja{
  TQueja queja;
  NodoQueja* sig;
};

int funcionHash(TFecha fecha, int cantEstimadas){
    return (31 * (int) mesTFecha(fecha) + (int) diaTFecha(fecha)) % cantEstimadas;
}

// TODO TESTEAR 
TablaQuejas crearTablaQuejas(int cantEstimadas) { 
  TablaQuejas nuevaTabla = new rep_tablaQuejas;
  nuevaTabla->cantidad = 0;
  nuevaTabla->cota = cantEstimadas;
  nuevaTabla->tabla = new NodoQueja*[cantEstimadas](); // Inicializo cada posicion del array en NULL
  return nuevaTabla;
}

// TODO TESTEAR 
// PRE: no existe una queja con la misma fecha en la estructura.
void agregarQuejaTablaQuejas(TablaQuejas tabla, TQueja queja) {
  if (!perteneceQuejaTablaQuejas(tabla,fechaTQueja(queja))) {
    
    int indice = funcionHash(fechaTQueja(queja), tabla->cota);

    NodoQueja* nueva = new NodoQueja;
    nueva->sig = tabla->tabla[indice];
    tabla->tabla[indice] = nueva;
    tabla->cantidad++;
  }
}

// TODO TESTEAR 
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

// TODO TESTEAR 
bool perteneceQuejaTablaQuejas(TablaQuejas tabla, TFecha fecha) {
  int indice = funcionHash(fecha, tabla->cota);
  NodoQueja* lista = tabla->tabla[indice];

  while (lista != NULL && fechaTQueja(lista->queja) != fecha ) {
    lista = lista->sig;
  }
  
  return lista != NULL;
}

TQueja obtenerQuejaTablaQuejas(TablaQuejas tabla, TFecha fecha) {

  return NULL;
}

void liberarTablaQuejas(TablaQuejas &tabla) {}
