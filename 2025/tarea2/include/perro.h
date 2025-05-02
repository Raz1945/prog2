/*
  Módulo de definición de 'TPerro'.

  Los elementos de tipo TPerro son elementos que almacenan un id, un nombre, una edad, una descripción, una fecha de ingreso al refugio y un entero positivo indicando su nivel de salud actual.

  Laboratorio de Programación 2.
  InCo-FIng-UDELAR
 */
#ifndef PERRO_H
#define PERRO_H

#include <string.h>

#include "fecha.h"

// Constantes para definir el largo máximo del nombre y la descripción de un perro
const int MAX_NOMBRE = 50;
const int MAX_DESCRIPCION = 100;

// Define el tipo TPerro como un puntero a rep_perro
typedef struct rep_perro *TPerro;

// Crea y retorna un elemento de tipo TPerro con los valores dados
TPerro crearTPerro(int id, const char nombre[MAX_NOMBRE], nat edad, nat vitalidad, const char descripcion[MAX_DESCRIPCION], TFecha fechaIngreso);

// Libera la memoria asignada para el perro 'p'
// Debe liberar también la memoria de la fecha asociada
void liberarTPerro(TPerro &p);

// Retorna el id del perro 'p'
int idTPerro(TPerro p);

// Retorna el nombre del perro 'p'
// El nombre retornado comparte memoria con el parámetro. 
char* nombreTPerro(TPerro p); 

// Retorna la edad del perro 'p'
nat edadTPerro(TPerro p); 

// Retorna la vitalidad del perro 'p' 
nat vitalidadTPerro(TPerro p);

// Retorna la descripción del perro 'p'
// La descripción retornada comparte memoria con el parámetro. 
char* descripcionTPerro(TPerro p); 

// Retorna la fecha de ingreso del perro 'p' al refugio.
// La fecha retornada comparte memoria con el parámetro. 
TFecha fechaIngresoTPerro(TPerro p);

// Imprime la información del perro 'p' en el siguiente formato:
// Perro <id>
// Nombre: <nombre>
// Edad: <edad> 
// Descripcion: <descripcion>
// Fecha de ingreso: <fecha de ingreso>
// Vitalidad: <vitalidad>
void imprimirTPerro(TPerro p);

// Retorna una copia del perro 'p' que no comparte memoria con el parámetro.
TPerro copiarTPerro(TPerro p);

// Actualiza la edad del perro 'p' por 'nuevaEdad'
void actualizarEdadTPerro(TPerro &p, nat nuevaEdad);

// Actualiza la vitalidad del perro 'p' por 'nuevaVitalidad'
void actualizarVitalidadTPerro(TPerro &p, nat nuevaVitalidad);

#endif  // PERRO_H