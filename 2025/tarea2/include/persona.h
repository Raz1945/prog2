/*
  Módulo de definición de 'TPersona'.

  Los elementos de tipo TPersona son elementos que almacenan una CI, un nombre, un apellido, una fecha de nacimiento
  y una colección de elementos de tipo TPerro, para indicar los perros adoptados por esta persona. 

  Laboratorio de Programación 2.
  InCo-FIng-UDELAR
 */
#ifndef TPERSONA_H
#define TPERSONA_H

#include <string.h>

#include "perro.h"
#include "fecha.h"

// Constante para definir el largo máximo del nombre y apellido de una persona
const int MAX_NOMBRE_PERSONA = 100;
const int MAX_APELLIDO_PERSONA = 100;
// Constante para definir la cantidad máxima de perros adoptados por una persona
const int MAX_PERROS_PERSONA = 5;

// Define el tipo TPersona como un puntero a rep_persona
typedef struct rep_persona *TPersona;

// Función que crea un elemento de tipo TPersona con los valores pasados por parámetro.
// La fecha de nacimiento se pasa como día, mes y anio de nacimiento respectivamente.
// Se incializa la colección de perros adoptados vacía.
/* Requisitos específicos de la implementación solicitada: */
// Se recomienda implementar la colección de perros como un arreglo con tope de elementos de tipo TPerro.
// Debe ejecutar en O(1) peor caso 
TPersona crearTPersona(int ci, const char nombre[MAX_NOMBRE_PERSONA], const char apellido[MAX_APELLIDO_PERSONA], nat diaNac, nat mesNac, nat anioNac);

// Función que imprime la información de la persona en el siguiente formato (donde los perros se imprimen en el orden en el que fueron agregados a la colección):
  // Persona <nombre> <apellido>
  // CI: <CI Persona>
  // Fecha de Nacimiento: <Fecha de Nacimiento>
  // Perros adoptados:
  //     <para cada perro adoptado>
  //     <imprimirTPerro>
/* Requisitos específicos de la implementación solicitada: */
// Debe ejecutar en O(1) peor caso 
void imprimirTPersona(TPersona persona);

// Función que libera la memoria asignada para una persona, incluída su fecha de nacimiento.
/* Requisitos específicos de la implementación solicitada: */
// Debe ejecutar en O(1) peor caso 
void liberarTPersona(TPersona &persona);

// Función que retorna la ci de la persona.
/* Requisitos específicos de la implementación solicitada: */
// Debe ejecutar en O(1) peor caso 
int ciTPersona(TPersona persona);

// Función que retorna el nombre de la persona.
/* Requisitos específicos de la implementación solicitada: */
// El nombre retornado comparte memoria con el parámetro.
// Debe ejecutar en O(1) peor caso 
char* nombreTPersona(TPersona persona);

// Función que retorna el apellido de la persona.
/* Requisitos específicos de la implementación solicitada: */
// El apellido retornado comparte memoria con el parámetro.
// Debe ejecutar en O(1) peor caso 
char* apellidoTPersona(TPersona persona);

// Función que devuelve la fecha de nacimiento de la persona.
/* Requisitos específicos de la implementación solicitada: */
// La fecha retornada comparte memoria con el parámetro.
// Debe ejecutar en O(1) peor caso 
TFecha fechaNacimientoTPersona(TPersona persona);

// Función que agrega el perro 'perro' en la colección de perros de la persona.
// En caso de que ya hayan MAX_PERROS_PERSONA en la colección, la funcion no tiene efecto.
/* Requisitos específicos de la implementación solicitada: */
// El perro de la persona *no* debe compartir memoria con el 'perro' parametro.
// Debe ejecutar en O(1) peor caso
void agregarPerroTPersona(TPersona &persona, TPerro perro);

// Función que indica si el perro de id 'idPerro' pertenece a la colección
// de perros de la persona.
/* Requisitos específicos de la implementación solicitada: */
// Debe ejecutar en O(1) peor caso
bool pertenecePerroTPersona(TPersona persona, int idPerro);

// Función que devuelve la cantidad de perros en la colección
// de perros de la persona.
/* Requisitos específicos de la implementación solicitada: */
// Debe ejecutar en O(1) peor caso
int cantidadPerrosTPersona(TPersona persona);

// Función que copia un persona.
/* Requisitos específicos de la implementación solicitada: */
// La copia *no* comparte memoria con la persona pasada por parámetro.
// Debe ejecutar en O(1) peor caso
TPersona copiarTPersona(TPersona persona);

#endif  // PERSONA_H