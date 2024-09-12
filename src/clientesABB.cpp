#include "../include/clientesABB.h"

struct rep_clientesABB {
    TCliente cliente;
    rep_clientesABB *izq;
    rep_clientesABB *der;
};

TClientesABB crearTClientesABBVacio() {
    return NULL;
}

void insertarTClienteTClientesABB(TClientesABB &clientesABB, TCliente cliente) {
    // Nota: El orden de la insercion se da por el numero de id del cliente.

    // Si el arbol esta vacio, se crea un nodo
    if (clientesABB == NULL) {
        TClientesABB nuevoNodo = new rep_clientesABB;
        nuevoNodo->cliente = cliente;
        nuevoNodo->izq = NULL;
        nuevoNodo->der = NULL;
        clientesABB = nuevoNodo;
    } else {
        // Si el id del cliente a insertar es menor, se inserta del lado izquierdo
        if (idTCliente(cliente) < idTCliente(clientesABB->cliente)) {
            insertarTClienteTClientesABB(clientesABB->izq, cliente);
        // Si el id del cliente a insertar es mayor, se inserta del lado derecho
        } else {
            insertarTClienteTClientesABB(clientesABB->der, cliente);
        }
    }
}

// Imprime los clientes en orde de id. [In-Orden]
void imprimirTClientesABB(TClientesABB clientesABB) {
    if (clientesABB != NULL) {
        imprimirTClientesABB(clientesABB->izq);
        imprimirTCliente(clientesABB->cliente);
        imprimirTClientesABB(clientesABB->der);
    }
}

// Liberar la memoria de todo un grupo. [Post-Orden]
void liberarTClientesABB(TClientesABB &clientesABB) {
    if (clientesABB != NULL) {
        liberarTClientesABB(clientesABB->izq);
        liberarTClientesABB(clientesABB->der);
        liberarTCliente(clientesABB->cliente);
        delete clientesABB;
        clientesABB = NULL;
    }
}

bool existeTClienteTClientesABB(TClientesABB clientesABB, int idCliente) {
    if (clientesABB == NULL) {
        return false;
    } else {
        if (idCliente == idTCliente(clientesABB->cliente)) {
            return true;
        // Si el id del cliente a buscar es menor al id del nodo actual, buscara solamente en el subarbol izquierdo
        } else if (idCliente < idTCliente(clientesABB->cliente)) {
            return existeTClienteTClientesABB(clientesABB->izq, idCliente);
        // Si el id del cliente a buscar es mayor al id del nodo actual, buscara solamente en el subarbol derecho
        } else {
            return existeTClienteTClientesABB(clientesABB->der, idCliente);
        }
    }
}

TCliente obtenerTClienteTClientesABB(TClientesABB clientesABB, int idCliente) {
    if (clientesABB == NULL) {
        return NULL;  
    } else if (idCliente == idTCliente(clientesABB->cliente)) {
        return clientesABB->cliente;  
    } else if (idCliente < idTCliente(clientesABB->cliente)) {
        return obtenerTClienteTClientesABB(clientesABB->izq, idCliente);
    } else {
        return obtenerTClienteTClientesABB(clientesABB->der, idCliente);
    }
}

// Retorna el mas grande de ambos
nat max(nat a, nat b) {
    return (a > b) ? a : b;
}

nat alturaTClientesABB(TClientesABB clientesABB) {
    if (clientesABB == NULL) {
        return 0; 
    } else {
        return 1 + max(alturaTClientesABB(clientesABB->izq), alturaTClientesABB(clientesABB->der));
    }
}

// todo VER
// PRE: el árbol binario no es vacío
TCliente maxIdTClienteTClientesABB(TClientesABB clientesABB) {
    if (clientesABB == NULL) { 
        return NULL;
    } else if (clientesABB->der == NULL) { // Si no hay mas nodos a la derecha, entonces es el nodo con el id mas grande
        return clientesABB->cliente;
    } else { // Si hay un subarbol derecho, seguira buscando en la misma direccion
        return maxIdTClienteTClientesABB(clientesABB->der);
    }
}

// todo HACER
void removerTClienteTClientesABB(TClientesABB &clientesABB, int idCliente) {
}

int cantidadClientesTClientesABB(TClientesABB clientesABB) {
    return 0;
}

float edadPromedioTClientesABB(TClientesABB clientesABB) {
    return 0.;
}

TCliente obtenerNesimoClienteTClientesABB(TClientesABB clientesABB, int n) {
    return NULL;
}
