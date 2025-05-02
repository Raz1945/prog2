/*
  Módulo de definición de 'TRefugio'.

  Los elementos de tipo TRefugio almacenan la colección de TPerros ingresados en el refugio.

  Laboratorio de Programación 2.
  InCo-FIng-UDELAR
 */
#ifndef REFUGIO_H
#define REFUGIO_H

#include "perro.h"

// Constante para definir el número máximo de perros que puede alojar el refugio
const int MAX_PERROS = 100;

// Definición de tipo TRefugio como un puntero a rep_refugio
typedef struct rep_refugio* TRefugio;

// Función para crear TRefugio vacío que puede almacenar hasta MAX_PERROS perros. 
TRefugio crearTRefugio();

// Función para liberar la memoria asociada a un refugio. 
// Recibe una referencia a un elemento de tipo TRefugio y libera su memoria
// Debe liberar además la memoria de cada uno de los perros alojados en el refugio. 
void liberarTRefugio(TRefugio& r);

// Función para agregar un nuevo perro 'p' al refugio 'r'
// Recibe un elemento de tipo TRefugio y un elemento de tipo TPerro y lo agrega al refugio en orden por fecha de ingreso (de menor a mayor)
// Si dos perros tienen la misma fecha de ingreso, deben ordenarse por orden de creación, quedando antes el primero de ellos en ser ingresado (de más antiguo a más reciente). 
// Si la cantidad de perros en la agenda es igual a MAX_PERROS, la función no tiene efecto
void agregarEnTRefugio(TRefugio& r, TPerro p);

// Función para imprimir la información de todos los perros del refugio
// Recibe un elemento de tipo TRefugio e imprime la información de sus perros en orden cronológico por fecha de ingreso. 
// El formato en el que se debe imprimir la información del refugio es utilizando de forma secuencial la función ImprimirTPerro
// Perro <id1>
// Nombre: <nombre1>
// Edad: <edad1> 
// Descripcion: <descripcion1>
// Fecha de ingreso: <fecha de ingreso 1>
// Vitalidad: <vitalidad1>
// Perro <id2>
// Nombre: <nombre2>
// Edad: <edad2> 
// Descripcion: <descripcion2>
// Fecha de ingreso: <fecha de ingreso 2>
// Vitalidad: <vitalidad2>
// .... 
// Si el refugio está vacío no imprime nada
void imprimirTRefugio(TRefugio r);

// Función para verificar si un perro con identificador 'id' existe en el refugio 'r' 
// Recibe una refugio r y un identificador id y retorna true si y solo si el refugio r aloja a un perro con identificador 'id'
bool estaEnTRefugio(TRefugio r, int id);

// Función para obtener un perro de un refugio
// Recibe un refugio y un identificador y regresa el perro con ese id
// El perro retornado comparte memoria con el parámetro. 
// PRE: El perro debe estar en el refugio
TPerro obtenerDeTRefugio(TRefugio r, int id);

// Función que retorna true si y solo si existe algún perro en el refugio ingresado el día de la fecha pasada por parámetro.
// La función debe ejecutar un algoritmo de búsqueda binaria
bool ingresaronPerrosFechaTRefugio(TRefugio r, TFecha f);

// Función para imprimir todos los perros de un refugio que ingresaron en una fecha determinada
// Recibe un refugio y una fecha e imprime la información de los perros que ingresaron en esa fecha por orden de creación (más nuevo a más antiguo)
// Si no hay perros ingresados en esa fecha no imprime nada
void imprimirPerrosFechaTRefugio(TRefugio r, TFecha f);

// Función para remover un perro de un refugio
// Recibe un refugio y el identificador del perro y remueve el perro con ese identificador del refugio
// PRE: El perro debe estar en el refugio
void removerDeTRefugio(TRefugio& r, int id);

#endif  // REFUGIO_H