
#include "../include/abbPersonas.h"

struct rep_abbPersonas {
    TPersona persona;
    rep_abbPersonas *izq;
    rep_abbPersonas *der;
};

TABBPersonas crearTABBPersonasVacio(){
  return NULL;
}

// Función para insertar una persona en el árbol, ordenada por CI.
// PRE: La persona con id no está en el árbol.
void insertarTPersonaTABBPersonas(TABBPersonas &abbPersonas, TPersona persona){
  if (abbPersonas == NULL){
    // Si el arbo esta vacio se crea un nodo.
    TABBPersonas nuevo = new rep_abbPersonas;
    nuevo->persona = persona;
    nuevo->izq = NULL;
    nuevo->der = NULL;
    abbPersonas = nuevo;

  } else {
    // Si la Ci de la persona a insertar es menor, se insertara del lado izquierdo
    if (ciTPersona(persona) < ciTPersona(abbPersonas->persona)) {
      insertarTPersonaTABBPersonas(abbPersonas->izq, persona);
    } else {
      // Si la Ci de la persona a insertar es mayor, se insertara del lado derecho
      insertarTPersonaTABBPersonas(abbPersonas->der, persona);
    }
  }   
}

// Función para imprimir las personas del árbol en orden, según su CI. La impresión
// de las personas se realiza con la función 'imprimirTPersona'.
void imprimirTABBPersonas(TABBPersonas abbPersonas){
  if (abbPersonas != NULL)  {
    imprimirTABBPersonas(abbPersonas->izq);
    imprimirTPersona(abbPersonas->persona);
    imprimirTABBPersonas(abbPersonas->der);
  }  
}


// Funcion Auxiliar para liberar la memoria de la persona y del nodo
void liberarNodo(TABBPersonas &abbPersonas){
  if (abbPersonas != NULL ) {
    liberarTPersona(abbPersonas->persona);
    delete abbPersonas;
    abbPersonas = NULL;
  }
}

// Función para liberar la memoria asignada a un árbol de personas.
void liberarTABBPersonas(TABBPersonas &abbPersonas){
  if (abbPersonas != NULL)  {
    liberarTABBPersonas(abbPersonas->izq);
    liberarTABBPersonas(abbPersonas->der);

    liberarNodo(abbPersonas);
  }  
}


// Función que determina si una persona está en el árbol.
// Devuelve true si la persona está en el árbol, false en caso contrario.
bool existeTPersonaTABBPersonas(TABBPersonas abbPersonas, int ciPersona) {
  if (abbPersonas == NULL) {
    return false;
  } else {
    if (ciPersona == ciTPersona(abbPersonas->persona)) {
      return true;
    } else if (ciPersona < ciTPersona(abbPersonas->persona)) {
      // Buscamos en el subárbol izquierdo
      return existeTPersonaTABBPersonas(abbPersonas->izq, ciPersona);
    } else {
      // Buscamos en el subárbol derecho
      return existeTPersonaTABBPersonas(abbPersonas->der, ciPersona);
    }
  }
}


// Función para obtener una persona del árbol.
// PRE: la persona está en el árbol
TPersona obtenerTPersonaTABBPersonas(TABBPersonas abbPersonas, int ciPersona){
  if (abbPersonas != NULL)  {
    if (ciPersona == ciTPersona(abbPersonas->persona))  {
      return abbPersonas->persona;
    } else if ( ciPersona < ciTPersona(abbPersonas->persona)) {
      return obtenerTPersonaTABBPersonas(abbPersonas->izq, ciPersona);
    } else {
      return obtenerTPersonaTABBPersonas(abbPersonas->der, ciPersona);
    }
  }

  return NULL;
}

// Funcion Auxiliar para obtener el mayor entre dos numeros
nat elMayor(nat a, nat b)  {
  return (a > b) ? a : b;
}

// Funcion para obtener la altura del árbol.
nat alturaTABBPersonas(TABBPersonas abbPersonas){
  if (abbPersonas == NULL)  {
    return 0;
  } else {
    return 1 + elMayor(alturaTABBPersonas(abbPersonas->izq), alturaTABBPersonas(abbPersonas->der));
  }
}

// Función para obtener la persona con la CI más grande del árbol.
// PRE: el árbol no es vacío
TPersona maxCITPersonaTABBPersonas(TABBPersonas abbPersonas){
  if (abbPersonas->der == NULL) {
    return abbPersonas->persona;
  } else {
    return maxCITPersonaTABBPersonas(abbPersonas->der);
  }
}

// Función para eliminar una persona del árbol.
// En caso de que el nodo a remover tenga ambos subárboles no vacíos, se
// reemplaza por la persona con la CI más grande del subárbol izquierdo. 
// PRE: La persona está en el árbol
void removerTPersonaTABBPersonas(TABBPersonas &abbPersonas, int ciPersona){
  if (abbPersonas != NULL)  {
    if (ciPersona < ciTPersona(abbPersonas->persona)) {
      // Busco por el subarbol izq
      removerTPersonaTABBPersonas(abbPersonas->izq, ciPersona);

    } else if (ciPersona > ciTPersona(abbPersonas->persona)) {
      // Busco por el subarbol der
      removerTPersonaTABBPersonas(abbPersonas->der, ciPersona);

    } else {
      // Nodo encontrado
      // Caso 1 - Es un nodo hoja
      if (abbPersonas->izq == NULL && abbPersonas->der == NULL)  {
        liberarNodo(abbPersonas);

      } else if (abbPersonas->izq == NULL) {
        // Caso 2 - Solo tiene un hijo derecho 
        TABBPersonas temp = abbPersonas;
        abbPersonas = abbPersonas->der; // Remplazamos con el hijo derecho
        liberarNodo(temp);

      } else if (abbPersonas->der == NULL) {
        // Caso 3 - Solo tiene un hijo izquierdo 
        TABBPersonas temp = abbPersonas;
        abbPersonas = abbPersonas->izq; // Remplazamos con el hijo izquierdo
        liberarNodo(temp);

      } else {
        // Caso 4 - Tiene ambos subarboles  
        // Buscamos la persona con la mayor Ci en el subarbol izquierdo
        TPersona maxCiPersonaIzq = maxCITPersonaTABBPersonas(abbPersonas->izq); 

        // Creamos una copia de 'maxCiPersonaIzq'
        TPersona copiaMaxCiPersonaIzq = copiarTPersona(maxCiPersonaIzq);

        // Removemos el cliente del nodo actual y lo subtituimos por 'maxCiPersonaIzq'
        liberarTPersona(abbPersonas->persona);
        abbPersonas->persona = copiaMaxCiPersonaIzq;

        // Eliminamos el nodo duplicado
        removerTPersonaTABBPersonas(abbPersonas->izq, ciTPersona(maxCiPersonaIzq));
      }
    }
  }
}

// Función para obtener la cantidad de personas en el árbol.
int cantidadTABBPersonas(TABBPersonas abbPersonas){
  if (abbPersonas == NULL) {
    return 0;
  } else {
    return 1 + cantidadTABBPersonas(abbPersonas->izq) + cantidadTABBPersonas(abbPersonas->der);
  }
}


// Funcion Auxiliar para recorrer el arbol In-Orden
TPersona inOrden(TABBPersonas nodo, int &index, int n) {
  if (nodo != NULL) {
    // Recorremos el subarbol izq
    TPersona resultado = inOrden(nodo->izq, index, n);
    if (index == n) return resultado;

    // Aumentamos el contador luego de pasar por el nodo izq
    index++;

    if (index == n) {
      return nodo->persona;
    }
    
    // Sino se encontro, recorremos el subarbol der
    resultado = inOrden(nodo->der, index, n);
    if (index == n) return resultado;
  }

  return NULL;
}

// Función para obtener la Nésima persona del árbol. 
// El órden de las personas se considera por orden de 'CI', iniciando en 1.
// Ejemplos:  
//  obtenerNesimaPersonaTABBPersonas(abbPersonas, 1) devuelve la persona con menor CI
//  obtenerNesimaPersonaTABBPersonas(abbPersonas, 2) devuelve la segunda persoan con menor CI
//  obtenerNesimaPersonaTABBPersonas(abbPersonas, cantidadTABBPersonas(abbPersonas)) devuelve la 
//  persona con mayor CI.
// PRE: cantidadTABBPersonas(abbPersonas) >= n
// PRE: n > 0 
TPersona obtenerNesimaPersonaTABBPersonas(TABBPersonas abbPersonas, int n){
  int index = 0; 
  return inOrden(abbPersonas, index, n);
}

// Si criterio < 0, el árbol retorno contiene a las personas con fecha de nacimiento MENOR a la fecha parámetro.
// Si criterio == 0, el árbol retorno contiene a las personas con fecha de nacimiento IGUAL a la fecha parámetro.
// Si criterio > 0, el árbol retorno contiene a las personas con fecha de nacimiento MAYOR a la fecha parámetro.
TABBPersonas filtradoPorFechaDeNacimientoTABBPersonas(TABBPersonas abbPersonas, TFecha fecha, int criterio) {
  if (abbPersonas == NULL) {
      return NULL;
  }

  TABBPersonas filtradoIzq = filtradoPorFechaDeNacimientoTABBPersonas(abbPersonas->izq, fecha, criterio);
  TABBPersonas filtradoDer = filtradoPorFechaDeNacimientoTABBPersonas(abbPersonas->der, fecha, criterio);

  TPersona actual = abbPersonas->persona;
  TFecha fechaNac = fechaNacimientoTPersona(actual);
  
  int res = compararTFechas(fecha, fechaNac);
  bool cumple = false;

  // Verifica si la persona cumple con el criterio de fecha
  if ((criterio < 0 && res > 0) ||  
      (criterio == 0 && res == 0) ||
      (criterio > 0 && res < 0)) {  
      cumple = true;
  }

  // Si cumple con el criterio, crear un nuevo nodo
  if (cumple) {
      TABBPersonas nuevoNodo = new rep_abbPersonas;
      nuevoNodo->persona = copiarTPersona(actual);
      nuevoNodo->izq = filtradoIzq;
      nuevoNodo->der = filtradoDer;
      return nuevoNodo;
  }

  // Si no cumple con el criterio, devolver el arbol filtrado combinando los subarboles izquierdo y derecho
  if (filtradoIzq != NULL && filtradoDer != NULL) {
      filtradoIzq->der = filtradoDer;  // Conectar el subarbol derecho al izquierdo
      return filtradoIzq; 
  }

  // Devolvemos el subarbol filtrado que no es NULL
  return filtradoIzq != NULL ? filtradoIzq : filtradoDer;
}
