// Ejercicio 1 - Modularizacion (parte de este)

#include <iostream>

const int MAX = 10;
typedef unsigned int nat; // Defino el tipo de naturales 'nat'

// Estructura bási  ca de Fecha
struct rep_fecha {
  nat dia, mes, anio;
};
typedef struct rep_fecha *TFecha;

// Arreglo con tope de Fechas
struct rep_ArrFechas {
  TFecha fechas[MAX];
  int tope;
};
typedef struct rep_ArrFechas *TArrFechas;

//> Fechas 
// Función para crear una fecha
TFecha crearTFecha(nat d, nat m, nat a) {
  TFecha nueva = new rep_fecha;
  nueva->dia = d;
  nueva->mes = m;
  nueva->anio = a;
  return nueva;
}

// Función para imprimir una fecha
void imprimirTFecha(TFecha fecha) {
  printf("%d/%d/%d\n", fecha->dia, fecha->mes, fecha->anio);
}

void liberarTFechas(TFecha &fecha){
  delete fecha;
  fecha = NULL;
}

int compararTFechas(TFecha fecha1, TFecha fecha2) {
  if (fecha1->anio > fecha2->anio) return 1;
  if (fecha1->anio < fecha2->anio) return -1;
  if (fecha1->mes > fecha2->mes) return 1;
  if (fecha1->mes < fecha2->mes) return -1;
  if (fecha1->dia > fecha2->dia) return 1;
  if (fecha1->dia < fecha2->dia) return -1;
  return 0;
}

//> Arreglo de Fechas 
// Función para inicializar un TArrFechas vacío
TArrFechas crearTArrFechas() {
  TArrFechas nuevo = new rep_ArrFechas;
  nuevo->tope = 0;
  return nuevo;
}

// Agregar una fecha de forma ordenada en el arreglo
void agregarTFecha(TArrFechas &arr, TFecha fecha) {
  if (arr->tope < MAX) {
    int i = arr->tope;
    while (i > 0 && compararTFechas(arr->fechas[i - 1], fecha) > 0) {
      arr->fechas[i] = arr->fechas[i - 1];
      i--;
    };
    
    arr->fechas[i] = fecha;
    arr->tope++;
  }
}

void liberarTArrFechas(TArrFechas &arr){
  if (arr != NULL)  {
    for (int i = 0; i < arr->tope; i++) {
      liberarTFechas(arr->fechas[i]);
    }
    delete arr;
    arr = NULL;  
  }
  
}

// Función para imprimir todas las fechas
void imprimirTArrFechas(TArrFechas arr) {
  for (int i = 0; i < arr->tope; i++) {
    imprimirTFecha(arr->fechas[i]);
  }
}

//> Programa Principal 
int main() {
  printf("¡Bienvenido!\n");

  // Inicializar la estructura de fechas
  TArrFechas arr = crearTArrFechas();

  // Agregar fechas
  agregarTFecha(arr, crearTFecha(22, 8, 2022));
  agregarTFecha(arr, crearTFecha(12, 9, 2021));
  agregarTFecha(arr, crearTFecha(22, 2, 2024));

  // Imprimir las fechas ordenadas
  printf("Fechas en el arreglo:\n");
  imprimirTArrFechas(arr);

  // Agregar una nueva fecha
  printf("\nAgrego fecha 1/1/2025:\n");
  agregarTFecha(arr, crearTFecha(1, 1, 2025));
  imprimirTArrFechas(arr);

  // Liberar memoria antes de salir
  liberarTArrFechas(arr);

  return 0;
}
