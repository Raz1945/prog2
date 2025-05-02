/*
  Módulo de definición de 'TLSEAdopciones'.

  Un elemento de tipo TLSEAdopciones es una lista simplemente enlazada, en la que cada elemento contiene un TPersona, un TPerro y un TFecha 
  para representar que una persona adoptó un perro en una fecha determinada.
  Una adopción se identifica por la cédula de la persona y el id del perro.

  Laboratorio de Programación 2.
  InCo-FIng-UDELAR
 */
#ifndef LSEADOPCIONES_H
#define LSEADOPCIONES_H

#include "persona.h"

// Define el tipo TLSEAdopciones como un puntero a rep_lseadopciones
typedef struct rep_lseadopciones *TLSEAdopciones;

// Función para crear un elemento de tipo TLSEAdopciones vacío.
// Devuelve una lista sin elementos.
/* Requisitos específicos de la implementación solicitada: */
// Debe ejecutar en Theta(1) peor caso
TLSEAdopciones crearTLSEAdopcionesVacia();

// Funcion para verificar si una lista de adopciones es vacía, retorna true si y solo si la lista es vacía.
/* Requisitos específicos de la implementación solicitada: */
// Debe ejecutar en Theta(1) peor caso
bool esVaciaTLSEAdopciones(TLSEAdopciones lseAdopciones);

// Función para imprimir todas las adopciones de una lista de adopciones.
// Las adopciones se imprimen en el orden en que aparecen en la lista de la siguiente manera (las líneas de printf copiarlas tal como están):
//
// printf("---------------------------\n");
// Adopcion en fecha <imprimirTFecha(fecha)>: 
// Adoptante:
// Persona <nombre> <apellido>
// CI: <CI Persona>
// Adoptado:
// Perro <ID Perro>
// Nombre: <Nombre Perro>
// Fecha de ingreso: <Fecha de ingreso Perro>
// printf("---------------------------\n");
//
// Si la lista está vacía no imprime nada.
/* Requisitos específicos de la implementación solicitada: */
// La función es Theta(n) peor caso, siendo n la cantidad de adopciones en la lista. */
void imprimirTLSEAdopciones(TLSEAdopciones lseAdopciones);

// Función para liberar una lista de adopciones.
// Recibe un elemento de tipo TLSEAdopciones y libera su memoria.
// Libera además la memoria de cada una de las personas, perros y fechas en la lista.
/* Requisitos específicos de la implementación solicitada: */
// La función es Theta(n) peor caso, siendo n la cantidad de adopciones en la lista.
void liberarTLSEAdopciones(TLSEAdopciones &lseAdopciones);

// Función para agregar una entrada a la lista de adopciones.
// Inserta la adopción, representada por la fecha, persona y perro pasados por parámetro, 
// ordenada de menor a mayor por fecha de adopción.
// Si existen otra adopción en la misma fecha, la que se está ingresando queda después.
// PRE: no existe una entrada en la lista para la misma CI de persona y mismo ID de perro.
/* Requisitos específicos de la implementación solicitada: */
// La función es Theta(n) peor caso, siendo n la cantidad de adopciones en la lista.
void insertarTLSEAdopciones(TLSEAdopciones &lseAdopciones, TFecha fecha, TPersona persona, TPerro perro);

// todo 
// Función para verificar si existe una adopción determinada en la lista.
// Recibe una CI de una persona y un id de perro y regresa un booleano indicando si existe una adopción
// de la persona con esa CI y el perro con ese id.
/* Requisitos específicos de la implementación solicitada: */
// La función es Theta(n) peor caso, siendo n la cantidad de adopciones en la lista.
bool existeAdopcionTLSEAdopciones(TLSEAdopciones lseAdopciones, int ciPersona, int idPerro);

// Función para remover una adopción de una lista de adopciones.
// Recibe una lista de adopciones, una CI de una persona y un id de un perro, elimina
// la adopción de esa persona para ese perro, incluida la memoria asociada a dicha persona, fecha y perro.
// PRE: existeAdopcionTLSEAdopciones(lseAdopciones, ciPersona, idPerro) == true
/* Requisitos específicos de la implementación solicitada: */
// La función es Theta(n) peor caso, siendo n la cantidad de adopciones en la lista.
void removerAdopcionTLSEAdopciones(TLSEAdopciones &lseAdopciones, int ciPersona, int idPerro);

#endif // LSEADOPCIONES_H  
