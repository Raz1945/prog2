#include "../include/practico5_ej1.h"
#include <iostream>

AB consArbol(AB izq, AB der, int elem){
    AB nuevo = new nodoAB;
    nuevo->elem = elem;
    nuevo->izq = izq;
    nuevo->der = der;

    return nuevo;
}

int contarElems(AB arbol) {
    if (arbol == NULL) return 0;
    else {
        return 1 + contarElems(arbol->izq) + contarElems(arbol->der);
    }
}

int contarHojas(AB arbol) {
    if (arbol == NULL) return 0; // Caso base: Si el árbol es vacío, no hay hojas
    if (arbol->izq == NULL && arbol->der == NULL) return 1; // Caso base: Nodo hoja
    // Contar hojas en los subárboles izquierdo y derecho
    return contarHojas(arbol->izq) + contarHojas(arbol->der);
}

int altura(AB arbol) {
    if (arbol == NULL) return 0;
    else {
        int alturaIzq = altura(arbol->izq);
        int alturaDer = altura(arbol->der);
        return 1 + (alturaIzq > alturaDer ? alturaIzq : alturaDer);
    }
}

AB copiar(AB arbol){
    if (arbol == NULL) return NULL;
    else {
     AB copia = new nodoAB;
     copia->elem = arbol->elem;
     copia->izq = copiar(arbol->izq);   
     copia->der = copiar(arbol->der);   
     return copia;
    }
}

void liberarArbol(AB arbol){
    if (arbol != NULL) {
        liberarArbol(arbol->izq);
        liberarArbol(arbol->der);
        delete arbol;
        arbol = NULL;
    }
}

Lista concatenar(Lista l1, Lista l2){
    if (l1 == NULL) return l2; // Si l1 es NULL, devolvemos l2

    Lista temp = l1;
    while (temp->sig != NULL) {
       temp = temp->sig;
    }
    temp->sig = l2; // Si l2 es NULL, no afecta la concatenacion
    
    return l1;
}

Lista enOrden(AB arbol){
    if (arbol == NULL) return NULL;

    Lista listaIzq = enOrden(arbol->izq);

    Lista nodoActual = new nodoLista;
    nodoActual->elem = arbol->elem;
    nodoActual->sig = NULL;

    Lista listaDer = enOrden(arbol->der);

    Lista listaCompleta = concatenar(listaIzq, nodoActual);
    return concatenar(listaCompleta, listaDer);
}

Lista preOrden(AB arbol){
    if (arbol == NULL) return NULL;

    Lista nodoActual = new nodoLista;
    nodoActual->elem = arbol->elem;
    nodoActual->sig = NULL;

    Lista l = concatenar(nodoActual, preOrden(arbol->izq));
    l = concatenar(l, preOrden(arbol->der));

    return l;
}

Lista postOrden(AB arbol){
    if (arbol == NULL) return NULL;

    Lista res = concatenar(postOrden(arbol->izq), postOrden(arbol->der));

    // Crea el nodo actual con el valor de la raiz
    Lista nodoActual = new nodoLista;
    nodoActual->elem = arbol->elem;
    nodoActual->sig = NULL;

    return res = concatenar(res, nodoActual);
}

bool esCamino(AB arbol, Lista l){
    if (l == NULL) return arbol == NULL;

    if (arbol == NULL) return false;

    // Verificar si el nodo actual coincide con el primer elemento de la lista
    if(arbol->elem != l->elem){
        return false;
    }

    // Si ambos subárboles son NULL y la lista termina aquí, es un camino válido
    if (arbol->izq == NULL && arbol->der == NULL && l->sig == NULL) {
        return true;
    }
     // Si el nodo tiene dos hijos, continuar con ambos subárboles
    if (arbol->izq != NULL && arbol->der != NULL) {
        return esCamino(arbol->izq, l->sig) || esCamino(arbol->der, l->sig);
    }

    // Si el nodo tiene un hijo izquierdo, continuar solo con el subárbol izquierdo
    else if (arbol->der == NULL && arbol->izq != NULL) {
        return esCamino(arbol->izq, l->sig);
    }

    // Si el nodo tiene un hijo derecho, continuar solo con el subárbol derecho
    else if (arbol->izq == NULL && arbol->der != NULL) {
        return esCamino(arbol->der, l->sig);
    }

    // Si no tiene hijos, es una hoja, y ya hemos verificado que la lista terminó
    else {
        return false;
    }
}


// Función auxiliar para encontrar el camino más largo en el árbol
void encontrarCaminoMasLargo(AB arbol, Lista &camino, int &maxLongitud, Lista caminoActual) {
    // Caso base: Si el árbol es NULL, terminamos
    if (arbol == NULL) {
        return;
    }

    // Crear un nuevo nodo para el camino actual y añadirlo al frente de la lista
    Lista nuevoNodo = new nodoLista;
    nuevoNodo->elem = arbol->elem;
    nuevoNodo->sig = caminoActual;
    caminoActual = nuevoNodo;

    // Si el nodo actual es una hoja (sin hijos), comprobar si el camino actual es el más largo
    if (arbol->izq == NULL && arbol->der == NULL) {
        // Calcular la longitud del camino actual
        int longitudActual = 0;
        Lista temp = caminoActual;
        while (temp != NULL) {
            longitudActual++;
            temp = temp->sig;
        }

        // Si el camino actual es más largo que el camino más largo encontrado, actualizar
        if (longitudActual > maxLongitud) {
            maxLongitud = longitudActual;
            // Crear una copia del camino más largo
            Lista copia = NULL;
            temp = caminoActual;
            while (temp != NULL) {
                Lista nuevo = new nodoLista;
                nuevo->elem = temp->elem;
                nuevo->sig = copia;
                copia = nuevo;
                temp = temp->sig;
            }
            camino = copia;
        }
    } else {
        // Si no es una hoja, continuar la búsqueda en los subárboles izquierdo y derecho
        encontrarCaminoMasLargo(arbol->izq, camino, maxLongitud, caminoActual);
        encontrarCaminoMasLargo(arbol->der, camino, maxLongitud, caminoActual);
    }

    // Eliminar el nodo actual de la lista al retroceder en la recursión
    Lista temp = caminoActual;
    caminoActual = caminoActual->sig;
    delete temp;
}

// Función principal para encontrar el camino más largo desde la raíz a una hoja
Lista caminoMasLargo(AB arbol) {
    // Inicializar variables para almacenar el camino más largo y su longitud
    Lista camino = NULL;
    int maxLongitud = 0;
    
    // Llamar a la función auxiliar para iniciar el proceso
    encontrarCaminoMasLargo(arbol, camino, maxLongitud, NULL);
    
    // Retornar el camino más largo encontrado
    return camino;
}
