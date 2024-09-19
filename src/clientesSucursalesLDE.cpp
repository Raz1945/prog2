#include "../include/clientesSucursalesLDE.h"

// Estructura para sucursales
struct AuxNodoLDE; 
typedef AuxNodoLDE *nodoLDE;

struct AuxNodoLDE {
    int idSucursal;
    TClientesABB clientesABB;
    nodoLDE ant; 
    nodoLDE sig; 
};

//Esta definido en el .h -> typedef struct rep_clientesSucursalesLDE *TClientesSucursalesLDE;
struct rep_clientesSucursalesLDE {
    nodoLDE inicial;
    nodoLDE final;
};

// -----
// Estructura para conteo de clientes
struct AuxNodoConteo;
typedef AuxNodoConteo *nodoConteo;

struct AuxNodoConteo {
    int idCliente;
    int conteo;
    nodoConteo ant;
    nodoConteo sig;
};

typedef struct rep_nodoConteoLDE *TAuxNodoConteo;
struct rep_nodoConteoLDE {
    nodoConteo inicial;
    nodoConteo final;
};




// Función para crear una nueva TClientesSucursalesLDE vacía
// Devuelve una colección vacía.
TClientesSucursalesLDE crearTClientesSucursalesLDEVacia() {
    TClientesSucursalesLDE nuevaLista = new rep_clientesSucursalesLDE;
    nuevaLista->inicial = NULL;
    nuevaLista->final = NULL;
    return nuevaLista;
}

// Función para insertar ordenadamente una colección de clientesABB en la lista de sucursales según la edad promedio (menor a mayor).
// Si ya existe uno o más clientesABB con la misma edad promedio, el nuevo es agregado a continuación de estos.
void insertarClientesABBTClientesSucursalesLDE(TClientesSucursalesLDE clientesSucursalesLDE, TClientesABB clientesABB, int idSucursal) {
    if (clientesSucursalesLDE != NULL) {
        // Crear un nuevo nodo
        nodoLDE nuevoNodo = new AuxNodoLDE;
        nuevoNodo->idSucursal = idSucursal;
        nuevoNodo->clientesABB = clientesABB;
        nuevoNodo->ant = NULL;
        nuevoNodo->sig = NULL;

        // Si la lista está vacía
        if (clientesSucursalesLDE->inicial == NULL) {
            clientesSucursalesLDE->inicial = nuevoNodo;
            clientesSucursalesLDE->final = nuevoNodo;
        }
        // La lista no está vacía, hay tres casos:
        else {
            // Caso 1: Insertar al inicio de la lista
            if (edadPromedioTClientesABB(clientesABB) < edadPromedioTClientesABB(clientesSucursalesLDE->inicial->clientesABB)) {
                nuevoNodo->sig = clientesSucursalesLDE->inicial;
                clientesSucursalesLDE->inicial->ant = nuevoNodo;
                clientesSucursalesLDE->inicial = nuevoNodo;
            }
            // Caso 2: Insertar al final de la lista
            else if (edadPromedioTClientesABB(clientesABB) > edadPromedioTClientesABB(clientesSucursalesLDE->final->clientesABB)) {
                nuevoNodo->sig = NULL;
                nuevoNodo->ant = clientesSucursalesLDE->final;
                clientesSucursalesLDE->final->sig = nuevoNodo;
                clientesSucursalesLDE->final = nuevoNodo;
            }
            // Caso 3: Insertar en "el medio" de la lista
            else {
                nodoLDE actual = clientesSucursalesLDE->inicial;

                // Recorre los punteros hasta encontrar el último nodo con la misma edad promedio
                while (actual != NULL && edadPromedioTClientesABB(clientesABB) > edadPromedioTClientesABB(actual->clientesABB)) {
                    actual = actual->sig;
                }
                // Si encuentra nodos con la misma edad, avanza hasta el último de ellos
                while (actual != NULL && edadPromedioTClientesABB(clientesABB) == edadPromedioTClientesABB(actual->clientesABB)) {
                    actual = actual->sig;
                }

                // Insertar el nuevo nodo antes de 'actual' (que tiene mayor edad promedio)
                if (actual != NULL) {
                    nuevoNodo->sig = actual;
                    nuevoNodo->ant = actual->ant;

                    if (actual->ant != NULL) {
                        actual->ant->sig = nuevoNodo;
                    } else {
                        clientesSucursalesLDE->inicial = nuevoNodo;
                    }

                    actual->ant = nuevoNodo;
                } else {
                    // Si no hay nodos posteriores, se inserta al final
                    nuevoNodo->ant = clientesSucursalesLDE->final;
                    clientesSucursalesLDE->final->sig = nuevoNodo;
                    clientesSucursalesLDE->final = nuevoNodo;
                }
            }
        }
    }
}

// Función que libera la memoria de un nodo
void liberarNodo(nodoLDE nodo) {
    if (nodo != NULL) {
        // Liberar la memoria de todo un grupo.
        liberarTClientesABB(nodo->clientesABB); 
        delete nodo;
    }
}

// Función que elimina la lista con todos sus ClientesABBs. 
// También libera la memoria de los clientes.
void liberarTClientesSucursalesLDE(TClientesSucursalesLDE &clientesSucursalesLDE) {
    if (clientesSucursalesLDE != NULL) {
        nodoLDE actual = clientesSucursalesLDE->inicial;
        nodoLDE temp;

        while (actual != NULL) {
            temp = actual->sig; 
            liberarNodo(actual);
            actual = temp;
        }

        delete clientesSucursalesLDE;
        clientesSucursalesLDE = NULL;
    }
}

// Función para imprimir secuencialmente los clientesABB de menor a mayor, según la edad promedio.
void imprimirTClientesSucursalesLDE(TClientesSucursalesLDE clientesSucursalesLDE){
    if (clientesSucursalesLDE != NULL) {
        nodoLDE actual = clientesSucursalesLDE->inicial;
        printf("clientesSucursalesLDE de grupos:\n");

        while (actual != NULL) {
            printf("Grupo con edad promedio %.2f:\n", edadPromedioTClientesABB(actual->clientesABB));

            if (actual->clientesABB != NULL) {
                imprimirTClientesABB(actual->clientesABB);
            }
            
            actual = actual->sig;
        }
    }
}

// Función para imprimir secuencialmente los clientesABB de mayor a menor, según la edad promedio.
void imprimirInvertidoTClientesSucursalesLDE(TClientesSucursalesLDE clientesSucursalesLDE){
    if (clientesSucursalesLDE != NULL) {
        nodoLDE actual = clientesSucursalesLDE->final;
        
        printf("clientesSucursalesLDE de grupos:\n");

        while (actual != NULL) {
            printf("Grupo con edad promedio %.2f:\n", edadPromedioTClientesABB(actual->clientesABB));

            if (actual->clientesABB != NULL) {
                imprimirTClientesABB(actual->clientesABB);
            }

            actual = actual->ant;
        }
    }
}

// Función quer retorna la cantidad de grupos clientesABB en la colección.
nat cantidadTClientesABBClientesSucursalesLDE(TClientesSucursalesLDE clientesSucursalesLDE){
    if (clientesSucursalesLDE == NULL) {
        return 0;
    } else {
        nodoLDE grupo = clientesSucursalesLDE->inicial;
        nat contador = 0;
        while (grupo != NULL) {
            contador++;
            grupo = grupo->sig;
        }

        return contador;
    }
}

// Función para obtener el primer grupo de clientesABB en la lista de sucursales
// PRE: la lista no es vacía
TClientesABB obtenerPrimeroClientesSucursalesLDE(TClientesSucursalesLDE clientesSucursalesLDE){
    if (clientesSucursalesLDE != NULL && clientesSucursalesLDE->inicial != NULL) {
        return clientesSucursalesLDE->inicial->clientesABB;
    }    
	return NULL;
}

// Función auxiliar que recorre en orden la lista
TClientesABB obtenerClienteEnPosicion(TClientesSucursalesLDE listaSucursales, int &index, int n) {
    if (listaSucursales != NULL) {
        nodoLDE actual = listaSucursales->inicial;

        while (actual != NULL && index < n) {
            index++;
            if (index == n) {
                return actual->clientesABB;
            }
            actual = actual->sig;
        }
    }
    return NULL;
}

// Función para obtener un grupo clientesABB en la lista de grupos (sucursales). 
// 'n' indica el índice desde el inicio (base 1, invocar con n = 1 devuelve el primer elemento).
// En caso de que n sea mayor que la cantidad de sucursales en la lista retorna NULL
// PRE: n > 0
TClientesABB obtenerNesimoClientesSucursalesLDE(TClientesSucursalesLDE clientesSucursalesLDE, int n){
    if (n > 0) {
        int cantidadGrupos = cantidadTClientesABBClientesSucursalesLDE(clientesSucursalesLDE);
        if ( n <= cantidadGrupos ) {
            int index = 0; 
            return obtenerClienteEnPosicion(clientesSucursalesLDE, index, n);
        }
    }
    return NULL;
}

// Función para eliminar el último grupo (clientesABB) en la lista de sucursales.
// Retorna el grupo (clientesABB) removido.
// PRE: la lista no es vacía
TClientesABB removerUltimoClientesSucursalesLDE(TClientesSucursalesLDE clientesSucursalesLDE) {
    if (clientesSucursalesLDE != NULL ) {
        nodoLDE nodoUltimo = clientesSucursalesLDE->final;
        TClientesABB clientesRemovidos = nodoUltimo->clientesABB;

        // Caso 1 - Un solo nodo en la lista
        if (clientesSucursalesLDE->inicial == clientesSucursalesLDE->final) {
            clientesSucursalesLDE->inicial = NULL;
            clientesSucursalesLDE->final = NULL;
        }
        // Caso 2 - Mas de un nodo en la lista
        else {
            clientesSucursalesLDE->final = nodoUltimo->ant;
            clientesSucursalesLDE->final->sig = NULL;
        }

        delete nodoUltimo; // Liberamos la memoria

        return clientesRemovidos;
    }
    return NULL;
}

// Función para eliminar el n-esimo grupo de la lista de sucursales 
// 'n' indica el índice desde el inicio (base 1, invocar con n = 1 devuelve el primer elemento).
// Retorna el grupo removido.
// PRE: Hay al menos n elementos en la lista
// PRE: n > 0
TClientesABB removerNesimoClientesSucursalesLDE(TClientesSucursalesLDE clientesSucursalesLDE, int n){
    if (clientesSucursalesLDE != NULL && n > 0) {
        int totalSucursales = cantidadTClientesABBClientesSucursalesLDE(clientesSucursalesLDE);

        if (n <= totalSucursales) {
            int contador = 1;
            nodoLDE nodoActual = clientesSucursalesLDE->inicial;

            while (contador < n && nodoActual != NULL) {
                nodoActual = nodoActual->sig;
                contador++;
            }
            
            if (nodoActual != NULL) {
                TClientesABB clientesRemovidos = nodoActual->clientesABB; // grupo de clientes a remover

                // Caso 1 - No es el primer nodo
                if (nodoActual->ant != NULL) {
                    nodoActual->ant->sig = nodoActual->sig; // Apuntamos el nodo anterior al 'actual' hacia el nodo siguiente al 'actual'
                } 
                // Caso 2 - Es el primer nodo
                else {
                    clientesSucursalesLDE->inicial = nodoActual->sig; // Actualizamos el comienzo de la lista
                }
                
                // Caso 3 - No es el ultimo nodo
                if (nodoActual->sig != NULL) {
                    nodoActual->sig->ant = nodoActual->ant; // Apuntamos el nodo siguiente al 'actual' hacia el nodo anterior al 'actual'
                }
                // Caso 4 - Es el ultimo nodo
                else {
                    clientesSucursalesLDE->final = nodoActual->ant;
                }

                delete nodoActual; // Liberamos la memoria

                return clientesRemovidos;
            }
        }
    }
    
	return NULL;
}

//  ------------------------------------------------------------------------------------------------- //
// Crear una lista de conteo vacia
TAuxNodoConteo crearListaConteoVacia() {
    TAuxNodoConteo lista = new rep_nodoConteoLDE;
    lista->inicial = NULL;
    lista->final = NULL;
    return lista;
}

/// Insertar un nodo en la lista de conteo de manera ordenada por idCliente
void insertarNodoConteo(TAuxNodoConteo lista, int idCliente, int conteo) {
    nodoConteo nuevoNodo = new AuxNodoConteo; 
    nuevoNodo->idCliente = idCliente;
    nuevoNodo->conteo = conteo;
    nuevoNodo->ant = NULL;
    nuevoNodo->sig = NULL;

    if (lista->inicial == NULL) {
        // Si la lista esta vacia, el nuevo nodo se convierte en el inicio y el final de la lista
        lista->inicial = nuevoNodo;
        lista->final = nuevoNodo;
    } else {
        nodoConteo actual = lista->inicial;

        // Buscar la posicion adecuada para insertar el nuevo nodo manteniendo el orden
        while (actual != NULL && actual->idCliente < idCliente) {
            actual = actual->sig;
        }

        // Insertar al final de la lista
        if (actual == NULL) {
            lista->final->sig = nuevoNodo;
            nuevoNodo->ant = lista->final;
            lista->final = nuevoNodo;
        } 
        // Insertar al inicio de la lista
        else if (actual == lista->inicial) {
            nuevoNodo->sig = lista->inicial;
            lista->inicial->ant = nuevoNodo;
            lista->inicial = nuevoNodo;
        }
        // Insertar en medio de la lista
         else {
            nuevoNodo->sig = actual;
            nuevoNodo->ant = actual->ant;
            actual->ant->sig = nuevoNodo;
            actual->ant = nuevoNodo;
        }
    }
}

// Contar la cantidad de veces que cada cliente aparece en un árbol binario de búsqueda
void contarClientesEnArbol(TClientesABB clientesABB, TAuxNodoConteo listaConteo, int idCliente) {
    if (clientesABB != NULL) {
        int totalClientesABB = cantidadClientesTClientesABB(clientesABB);

        for (int i = 1; i <= totalClientesABB; i++) {
            TCliente clienteActual = obtenerNesimoClienteTClientesABB(clientesABB, i);
            int idClienteActual = idTCliente(clienteActual);

            nodoConteo resultado = listaConteo->inicial;
            // Buscar si el cliente ya esta en la lista de conteo
            while (resultado != NULL) {

                // Si el cliente ya esta en la lista, incrementar su conteo
                if (resultado->idCliente == idClienteActual) {
                    resultado->conteo++;
                    return;
                }

                resultado = resultado->sig;
            }

            // Si el cliente no está en la lista de conteo, agregarlo con un conteo inicial de 1
            insertarNodoConteo(listaConteo, idClienteActual, 1);
        }
    }
}

// Obtener un cliente dado su id en la colección de sucursales
TCliente obtenerClientePorId(TClientesSucursalesLDE clientesSucursalesLDE, int idCliente) {
    nodoLDE sucursal = clientesSucursalesLDE->inicial;

    while (sucursal != NULL) {
        TClientesABB clientesABB = sucursal->clientesABB;
        int totalClientesABB = cantidadClientesTClientesABB(clientesABB);

        for (int i = 1; i <= totalClientesABB; i++) {
            TCliente clienteActual = obtenerNesimoClienteTClientesABB(clientesABB, i);

            if (idTCliente(clienteActual) == idCliente) {
                return clienteActual; // Retornar el cliente encontrado
            }
        }

        sucursal = sucursal->sig;
    }
    return NULL; // Si no se encuentra el cliente, retornar NULL
}

// Encontrar el cliente con el mayor conteo de apariciones
TCliente obtenerClienteConMayorConteo(TClientesSucursalesLDE clientesSucursalesLDE, TAuxNodoConteo listaConteo) {
    if (listaConteo->inicial == NULL) {
        return NULL; 
    }

    nodoConteo mejorNodo = listaConteo->inicial;
    int conteoMaximo = mejorNodo->conteo;

    // Iterar a traves de la lista de conteo desde el inicio hasta el final
    nodoConteo clienteActual = mejorNodo->sig;
    while (clienteActual != NULL) {

        if (clienteActual->conteo > conteoMaximo) {
            mejorNodo = clienteActual;
            conteoMaximo = clienteActual->conteo;
        } 
        // Si el conteo es igual, seleccionar el cliente con el id menor
        else if (clienteActual->conteo == conteoMaximo) {
            if (clienteActual->idCliente < mejorNodo->idCliente) {
                mejorNodo = clienteActual;
            }
        }
        clienteActual = clienteActual->sig;
    }

    // Obtener el cliente con el id más repetido
    TCliente clienteRepetido = obtenerClientePorId(clientesSucursalesLDE, mejorNodo->idCliente);

    // Liberar memoria de la lista de conteo
    while (listaConteo->inicial != NULL) {
        nodoConteo temp = listaConteo->inicial;
        listaConteo->inicial = listaConteo->inicial->sig;
        delete temp; 
    }
    delete listaConteo;

    return clienteRepetido;
}

// Dada una coleccion de clientesABB, regresa el cliente que se encuentre en la mayor cantidad de clientesABB (sucursales).
// Un cliente se considera repetido si su id es el mismo. 
// Si todos los clientesABB de la colección están vacíos o si la colección de clientesABB es vacía, retorna NULL.
// Si hay varios clientes empatados en apariciones, se retorna aquel con menor id.
TCliente clienteMasRepetido(TClientesSucursalesLDE clientesSucursalesLDE) {
    if (clientesSucursalesLDE == NULL || clientesSucursalesLDE->inicial == NULL) {
        return NULL;    // Si la colección de sucursales está vacía o todas las sucursales están vacías, retornar NULL
    }

    TAuxNodoConteo listaConteo = crearListaConteoVacia(); 

    nodoLDE sucursal = clientesSucursalesLDE->inicial;
    // Recorrer cada sucursal y contar los clientes en sus árboles binarios
    while (sucursal != NULL) {
        TClientesABB clientesABB = sucursal->clientesABB;
        int totalClientesABB = cantidadClientesTClientesABB(clientesABB);

        for (int i = 1; i <= totalClientesABB; i++) {
            TCliente clienteActual = obtenerNesimoClienteTClientesABB(clientesABB, i);
            int idCliente = idTCliente(clienteActual);
            contarClientesEnArbol(clientesABB, listaConteo, idCliente); // Contar el cliente en el ABB
        }
        sucursal = sucursal->sig;
    }

    if (listaConteo->inicial == NULL) {
        // Si no hay clientes en la lista de conteo, liberar la lista y retornar NULL
        delete listaConteo;
        return NULL;
    }

    TCliente clienteRepetido = obtenerClienteConMayorConteo(clientesSucursalesLDE, listaConteo);

    return clienteRepetido;
}
