#include "../include/tablaQuejas.h"

struct rep_tablaQuejas { };

int funcionHash(TFecha fecha, int cantEstimadas){
    return (31 * (int) mesTFecha(fecha) + (int) diaTFecha(fecha)) % cantEstimadas;
}

TablaQuejas crearTablaQuejas(int cantEstimadas) { 
  return NULL;
}

void agregarQuejaTablaQuejas(TablaQuejas tabla, TQueja queja) { }

void imprimirTablaQuejas(TablaQuejas tabla) { }

bool perteneceQuejaTablaQuejas(TablaQuejas tabla, TFecha fecha) {
  return false;
}

TQueja obtenerQuejaTablaQuejas(TablaQuejas tabla, TFecha fecha) {
  return NULL;
}

void liberarTablaQuejas(TablaQuejas &tabla) {}
