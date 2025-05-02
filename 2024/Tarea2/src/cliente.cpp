#include "../include/cliente.h"

struct rep_cliente {
    int id;
    char nombre[MAX_NOMBRE];
    char apellido[MAX_APELLIDO];
    int edad;
    rep_cliente *sig;
};

// Función que crea un elemento de tipo TCliente con los valores pasados por parámetro
TCliente crearTCliente(int id, const char nombre[MAX_NOMBRE], const char apellido[MAX_APELLIDO], int edad){
    TCliente nuevoCliente = new rep_cliente;

    if(nuevoCliente !=NULL){
        nuevoCliente->id = id;
        strcpy(nuevoCliente->nombre, nombre);
        strcpy(nuevoCliente->apellido, apellido);
        nuevoCliente->edad = edad;
    }  

    return nuevoCliente;
}

// Función que imprime la información de UN cliente
void imprimirTCliente(TCliente cliente){
    if (cliente != NULL){
        printf("Cliente %s %s\n", cliente->nombre, cliente->apellido);
        printf("Id: %d\n",cliente->id);
        printf("Edad: %d\n", cliente->edad);
    }
}

// Función que libera la memoria asignada a un cliente
void liberarTCliente(TCliente &cliente){
    if (cliente != NULL) {
        delete cliente;
        cliente = NULL;    
    }    
}

// Función que retorna el nombre del cliente
void nombreTCliente(TCliente cliente, char nombre[MAX_NOMBRE]){
    strcpy(nombre, cliente->nombre);
}

// Función que retorna el apellido del cliente
void apellidoTCliente(TCliente cliente, char apellido[MAX_APELLIDO]){
    strcpy(apellido, cliente->apellido);
}

// Función que retorna el id del cliente
int idTCliente(TCliente cliente){
    return cliente->id;
}

// Función que retorna la edad del cliente
int edadTCliente(TCliente cliente){
    return cliente->edad;
}

// Función que copia un cliente. La copia no comparte memoria con el cliente pasado por parámetro.
TCliente copiarTCliente(TCliente cliente){
    if (cliente == NULL){
        return NULL;
    } else {
        TCliente copy = new rep_cliente;
        copy->id = cliente->id;
        strcpy(copy->nombre, cliente->nombre);
        strcpy(copy->apellido, cliente->apellido);
        copy->edad = cliente->edad;
        return copy;
    }
}
