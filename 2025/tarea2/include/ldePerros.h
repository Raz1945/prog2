/*
  Módulo de definición de 'TLDEPerros'.

  Un elemento de tipo TLDEPerros es una lista doblemente encadenada que guarda elementos de tipo
  TPerro, con un cabezal con puntero al inicio y al final de la lista.

  Laboratorio de Programación 2. InCo-FIng-UDELAR
 */
#ifndef TLDEPERROS_H
#define TLDEPERROS_H

#include "perro.h"

// Define el tipo TLDEPerros como un puntero a rep_tldeperros
typedef struct rep_tldeperros *TLDEPerros;

// Función para crear una nueva TLDEPerros vacía
// Devuelve una instancia de TLDEPerros vacía.
/* Requisitos específicos de la implementación solicitada: */
// La función es Theta(1) peor caso.
TLDEPerros crearTLDEPerrosVacia();

// Función para insertar ordenadamente de menor a mayor un perro en la lista de perros, según 
// su edad. Si ya existe uno o más perros con la misma edad,
// el nuevo perro es agregado al inicio de los demás perros con misma edad.
/* Requisitos específicos de la implementación solicitada: */
// La función es O(n) peor caso, siendo n la cantidad de perros en la lista
void insertarTLDEPerros(TLDEPerros &ldePerros, TPerro perro);

// Función que elimina la ldePerros. También libera
// la memoria asociada a todos los perros.
/* Requisitos específicos de la implementación solicitada: */
// La función es O(n) peor caso, donde n es la cantidad de perros en la lista.
void liberarTLDEPerros(TLDEPerros &ldePerros);

// Función para imprimir secuencialmente los perros de menor a mayor, según su edad.
// El formato de impresión es:
// LDE Perros:
//     <y luego para cada perro se repite>
//     <imprimir con función imprimirTPerro>
/* Requisitos específicos de la implementación solicitada: */
// La función es O(n) peor caso, donde n es la cantdiad de perros en la lista.
void imprimirTLDEPerros(TLDEPerros ldePerros);

// Función para imprimir secuencialmente los perros de mayor a menor, según su edad.
// El formato de impresión es:
// LDE Perros:
//     <y luego para cada perro se repite>
//     <imprimir con función imprimirTPerro>
/* Requisitos específicos de la implementación solicitada: */
// La función es O(n) peor caso, donde n es la cantdiad de perros en la lista.
void imprimirInvertidoTLDEPerros(TLDEPerros ldePerros);

// Función quer retorna la cantidad de perros en la lista.
/* Requisitos específicos de la implementación solicitada: */
// La función es O(1) peor caso, donde n es la cantidad de perros en la lista
nat cantidadTLDEPerros(TLDEPerros ldePerros);

// Función para eliminar el perro con id 'id' de la lista.
// Retorna el elemento TPerro removido.
// PRE: existe el perro de id 'id' en la lista
/* Requisitos específicos de la implementación solicitada: */
// La función es O(n) en el peor caso, siendo n la cantidad de perros en la lista.
TPerro removerPerroTLDEPerros(TLDEPerros &ldePerros, int id);

// Función para obtener el primer perro en la lista de perros (el perro con menor edad). 
// PRE: la lista no es vacía
/* Requisitos específicos de la implementación solicitada: */
// La función es O(1) peor caso.
TPerro obtenerPrimeroTLDEPerros(TLDEPerros ldePerros);

// Función para obtener el último perro en la lista de perros (el perro con mayor edad). 
// PRE: la lista no es vacía
/* Requisitos específicos de la implementación solicitada: */
// La función es O(1) peor caso.
TPerro obtenerUltimoTLDEPerros(TLDEPerros ldePerros);

// Función para obtener un perro en la lista de perros. 'n' indica el índice desde el 
// inicio (invocar con n = 1 devuelve el primer elemento). 
// PRE: n > 0, n es menor a la cantidad de perros en 'ldePerros'
/* Requisitos específicos de la implementación solicitada: */
// La función es O(n) peor caso, siendo n la cantidad de perros en la lista.
TPerro obtenerNesimoTLDEPerros(TLDEPerros ldePerros, int n);

// Función que indica si existe el perro de id 'id' en la lista.
// La función retorna true si y solo si existe un perro con id 'id' en la lista 'ldePerros'.
/* Requisitos específicos de la implementación solicitada: */
// La función es O(n) en el peor caso, siendo n la cantidad de perros en la lista.
bool existePerroTLDEPerros(TLDEPerros ldePerros, int id);



#endif // TLDEPERROS_H  

