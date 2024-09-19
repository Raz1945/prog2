#include "../include/clientesABB.h"

struct rep_clientesABB {
    TCliente cliente;
    rep_clientesABB *izq;
    rep_clientesABB *der;
};

// Función para crear un nuevo grupo vacío.
// Devuelve un nuevo árbol binario vacío.
TClientesABB crearTClientesABBVacio() {
    return NULL;
}

// Función para insertar un Cliente en el árbol binario, por id.
// Nota: El orden de la insercion se da por el numero de id del cliente.
// PRE: El Cliente no está en el grupo.
void insertarTClienteTClientesABB(TClientesABB &clientesABB, TCliente cliente) {
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

// Liberar la memoria del cliente y del nodo
// Función para liberar la memoria asignada a un grupo.
void liberarNodo(TClientesABB &clientesABB) {
    if (clientesABB != NULL) {
        liberarTCliente(clientesABB->cliente);
        delete clientesABB;
        clientesABB = NULL; 
    }
}
// Función para liberar la memoria asignada a un grupo. [Post-Orden]
void liberarTClientesABB(TClientesABB &clientesABB) {    
    if (clientesABB != NULL) {
        liberarTClientesABB(clientesABB->izq);
        liberarTClientesABB(clientesABB->der);

        liberarNodo(clientesABB);
    }
}

// Función que determina si un cliente está en el árbol binario.
// Devuelve true si el cliente está en el grupo, false en caso contrario.
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

// Función para obtener un cliente del árbol binario.
// PRE: el cliente está en el grupo
TCliente obtenerTClienteTClientesABB(TClientesABB clientesABB, int idCliente) {
    if (clientesABB != NULL) {
        if (idCliente == idTCliente(clientesABB->cliente)) {
            return clientesABB->cliente;  
        } else if (idCliente < idTCliente(clientesABB->cliente)) {
            return obtenerTClienteTClientesABB(clientesABB->izq, idCliente);
        } else {
            return obtenerTClienteTClientesABB(clientesABB->der, idCliente);
        }
    }
    return NULL;  
}

// Funcion para obtener el mayor entre dos numeros
nat max(nat a, nat b) {
    return (a > b) ? a : b;
}

// Funcion para obtener la altura del árbol binario.
nat alturaTClientesABB(TClientesABB clientesABB) {
    if (clientesABB == NULL) {
        return 0; 
    } else {
        return 1 + max(alturaTClientesABB(clientesABB->izq), alturaTClientesABB(clientesABB->der));
    }
}

// Función para obtener el cliente con el id más grande del árbol binario.
// PRE: el árbol binario no es vacío
TCliente maxIdTClienteTClientesABB(TClientesABB clientesABB) {
    if (clientesABB->der == NULL) { 
        return clientesABB->cliente;
    }
    // Si hay un subarbol derecho, seguira buscando en la misma direccion
    else {
        return maxIdTClienteTClientesABB(clientesABB->der);
    }
}

// Función para eliminar un cliente del árbol binario.
// En caso de que el nodo a remover tenga ambos subárboles no vacíos, se
// reemplaza por el cliente con el id más grande del subárbol izquierdo. 
// PRE: El cliente está en el grupo
void removerTClienteTClientesABB(TClientesABB &clientesABB, int idCliente) {
    if (clientesABB != NULL) {
        if (idCliente < idTCliente(clientesABB->cliente)) {
            removerTClienteTClientesABB(clientesABB->izq, idCliente);

        } else if (idCliente > idTCliente(clientesABB->cliente)) {
            removerTClienteTClientesABB(clientesABB->der, idCliente);
        } 
        // Nodo encontrado
        else {
            // Caso 1 - El nodo es una hoja
            if (clientesABB->izq == NULL && clientesABB->der == NULL) {
                liberarNodo(clientesABB);
            } 
            // Caso 2 - El nodo solo tiene hijo derecho
            else if (clientesABB->izq == NULL) {
                TClientesABB temp = clientesABB;
                clientesABB = clientesABB->der;  // Reemplazamos con el hijo derecho
                liberarNodo(temp);
            } 
            // Caso 2 - El nodo solo tiene hijo izquierdo
            else if (clientesABB->der == NULL) {
                TClientesABB temp = clientesABB;
                clientesABB = clientesABB->izq;  // Reemplazamos con el hijo izquierdo
                liberarNodo(temp);
            } 
            // Caso 3 - El nodo tiene ambos subárboles no vacíos
            else {
                // Encontramos el cliente con el id mas grande en el subarbol izquierdo
                TCliente maxClienteIzquierdo = maxIdTClienteTClientesABB(clientesABB->izq);
                
                // Hacemos una copia del cliente del nodo maximo
                TCliente copiaMaxClienteIzquierdo = copiarTCliente(maxClienteIzquierdo);

                // Liberamos el cliente del nodo actual y reemplazamos con la copia
                liberarTCliente(clientesABB->cliente);
                clientesABB->cliente = copiaMaxClienteIzquierdo;

                // Eliminamos el nodo duplicado en el subarbol izquierdo
                removerTClienteTClientesABB(clientesABB->izq, idTCliente(maxClienteIzquierdo));
            }
        }
    }
}

// Función para obtener la cantidad de clientes en el árbol binario.
int cantidadClientesTClientesABB(TClientesABB clientesABB) {
    if (clientesABB == NULL){
        return 0;
    } else {
        return 1 + cantidadClientesTClientesABB(clientesABB->izq) + cantidadClientesTClientesABB(clientesABB->der);
    }
}

// Sumar la edad de todos los clientes en el ABB
float sumatoriaEdadTClientesABB(TClientesABB clientesABB) {
    if (clientesABB == NULL) {
        return 0.0;
    } else {
        // Suma la edad del cliente actual + las edades de los lados izquierdo y derecho
        return edadTCliente(clientesABB->cliente) + 
               sumatoriaEdadTClientesABB(clientesABB->izq) + 
               sumatoriaEdadTClientesABB(clientesABB->der);
    }
}

// Funcion para obtener la edad promedio de los clientes. Si no hay clientes en el grupo devuelve 0.
float edadPromedioTClientesABB(TClientesABB clientesABB) {
    int cantidadClientes = cantidadClientesTClientesABB(clientesABB);

    if (cantidadClientes == 0) {
        return 0.0;
    } else {
        return (sumatoriaEdadTClientesABB(clientesABB) / cantidadClientes);
    }
}

// Recorre enorden el arbol [In-Orden] 
TCliente inOrden(TClientesABB nodo, int &index, int n) {

    if (nodo != NULL) {
        // Recorre el subarbol izquierdo
        TCliente resultado = inOrden(nodo->izq, index, n);
        if (index == n) return resultado; 

        // Aumenta el contador luego de pasar por el nodo izquierdo
        index++;

        // Verifica si se encontro en el nodo actual
        if (index == n) {
            return nodo->cliente;
        }

        // En caso de no encontrarlo en el nodo actual, recorre el subarbol derecho
        resultado = inOrden(nodo->der, index, n);
        if (index == n) return resultado;
    }
    return NULL;
}

// Función para obtener el Nesimo cliente del grupo. El órden de los clientes se considera por orden de 'id', con base 1.
// PRE: cantidadClientesTClientesABB(grupo) >= n
// PRE: n > 0
TCliente obtenerNesimoClienteTClientesABB(TClientesABB clientesABB, int n) {
    int index = 0; // contador de posicion
    return inOrden(clientesABB, index, n);
}
