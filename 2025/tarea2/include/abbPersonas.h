/*
  Módulo de definición de 'TABBPersonas'.

  Un elemento de tipo TABBPersonas es un árbol binario de búsqueda que almacena una coleccion de elementos de tipo TPersona ordenada por CI. 

  Laboratorio de Programación 2.
  InCo-FIng-UDELAR
 */
#ifndef ABBPERSONAS_H
#define ABBPERSONAS_H

#include "persona.h"

// Define el tipo TABBPersonas como un puntero a rep_abbPersonas.
typedef struct rep_abbPersonas *TABBPersonas;

// Función para crear un nuevo abb de personas vacío.
// Devuelve un nuevo árbol binario de búsqueda vacío.
/* Requisitos específicos de la implementación solicitada: */
// La funcion es Theta(1) peor caso.
TABBPersonas crearTABBPersonasVacio();

// Función para insertar una persona en el árbol, ordenada por CI.
// PRE: La persona con id no está en el árbol.
/* Requisitos específicos de la implementación solicitada: */
// La funcion es Theta(n) peor caso, siendo n la cantidad de personas en el árbol.
void insertarTPersonaTABBPersonas(TABBPersonas &abbPersonas, TPersona persona);

// Función para imprimir las personas del árbol en orden, según su CI. La impresión
// de las personas se realiza con la función 'imprimirTPersona'.
/* Requisitos específicos de la implementación solicitada: */
// La función es Theta(n) peor caso, donde n es la cantidad de personas en el árbol.
void imprimirTABBPersonas(TABBPersonas abbPersonas);

// Función para liberar la memoria asignada a un árbol de personas.
/* Requisitos específicos de la implementación solicitada: */
// La función es Theta(n) peor caso, donde n es la cantidad de personas en el árbol.
void liberarTABBPersonas(TABBPersonas &abbPersonas);

// Función que determina si una persona está en el árbol.
// Devuelve true si la persona está en el árbol, false en caso contrario.
/* Requisitos específicos de la implementación solicitada: */
// La funcion es O(log(n)) caso promedio, siendo n la cantidad de personas en el árbol.
bool existeTPersonaTABBPersonas(TABBPersonas abbPersonas, int ciPersona);

// Función para obtener una persona del árbol.
// PRE: la persona está en el árbol
/* Requisitos específicos de la implementación solicitada: */
// La funcion es O(log(n)) caso promedio, siendo n la cantidad de personas en el árbol.
TPersona obtenerTPersonaTABBPersonas(TABBPersonas abbPersonas, int ciPersona);

// Funcion para obtener la altura del árbol.
/* Requisitos específicos de la implementación solicitada: */
// La funcion es Theta(n) peor caso, siendo n la cantidad de personas en el árbol.
nat alturaTABBPersonas(TABBPersonas abbPersonas);

// Función para obtener la persona con la CI más grande del árbol.
// PRE: el árbol no es vacío
/* Requisitos específicos de la implementación solicitada: */
// La funcion es Theta(n) peor caso, siendo n la cantidad de personas en el árbol.
TPersona maxCITPersonaTABBPersonas(TABBPersonas abbPersonas);

// Función para eliminar una persona del árbol.
// En caso de que el nodo a remover tenga ambos subárboles no vacíos, se
// reemplaza por la persona con la CI más grande del subárbol izquierdo. 
// PRE: La persona está en el árbol
/* Requisitos específicos de la implementación solicitada: */
// La función es Theta(n) peor caso, donde n es la cantidad de personas en el árbol.
void removerTPersonaTABBPersonas(TABBPersonas &abbPersonas, int ciPersona);

// Función para obtener la cantidad de personas en el árbol.
/* Requisitos específicos de la implementación solicitada: */
// La funcion es Theta(n) peor caso, siendo n la cantidad de personas en el árbol.
int cantidadTABBPersonas(TABBPersonas abbPersonas);

// Función para obtener la Nésima persona del árbol. 
// El órden de las personas se considera por orden de 'CI', iniciando en 1.
// Ejemplos:  
//  obtenerNesimaPersonaTABBPersonas(abbPersonas, 1) devuelve la persona con menor CI
//  obtenerNesimaPersonaTABBPersonas(abbPersonas, 2) devuelve la segunda persoan con menor CI
//  obtenerNesimaPersonaTABBPersonas(abbPersonas, cantidadTABBPersonas(abbPersonas)) devuelve la 
//  persona con mayor CI.
// PRE: cantidadTABBPersonas(abbPersonas) >= n
// PRE: n > 0 
/* Requisitos específicos de la implementación solicitada: */
// La funcion es Theta(m) peor caso, siendo m la cantidad de personas en el árbol.
TPersona obtenerNesimaPersonaTABBPersonas(TABBPersonas abbPersonas, int n);

// Función que retorna un nuevo árbol únicamente con las personas que cumplen el 'criterio' pasado 
// por parámetro con respecto a la fecha. 
// El árbol filtrado no comparte memoria con el árbol original.
// Las personas retornadas en el nuevo árbol son copias limpias de las que pertenecen al árbol parámetro.
// 
// Si criterio < 0, el árbol retorno contiene a las personas con fecha de nacimiento MENOR a la fecha parámetro.
// Si criterio == 0, el árbol retorno contiene a las personas con fecha de nacimiento IGUAL a la fecha parámetro.
// Si criterio > 0, el árbol retorno contiene a las personas con fecha de nacimiento MAYOR a la fecha parámetro.
// 
/* Requisitos específicos de la implementación solicitada: */
// La funcion es O(n) peor caso, siendo n la cantidad de personas en el árbol.
TABBPersonas filtradoPorFechaDeNacimientoTABBPersonas(TABBPersonas abbPersonas, TFecha fecha, int criterio);

#endif // ABBPERSONAS_H  

