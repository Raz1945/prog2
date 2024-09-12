#include "../include/cliente.h"

struct rep_cliente {
    int id;
    char nombre[MAX_NOMBRE];
    char apellido[MAX_APELLIDO];
    int edad;
    rep_cliente *sig;
};


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

void imprimirTCliente(TCliente cliente){
    if (cliente != NULL){
        printf("Cliente %s %s\n", cliente->nombre, cliente->apellido);
        printf("Id: %d\n",cliente->id);
        printf("Edad: %d\n", cliente->edad);
    }
}

void liberarTCliente(TCliente &cliente){
    delete cliente;
    cliente = NULL;        
}

void nombreTCliente(TCliente cliente, char nombre[MAX_NOMBRE]){
    strcpy(nombre, cliente->nombre);
}

void apellidoTCliente(TCliente cliente, char apellido[MAX_APELLIDO]){
    strcpy(apellido, cliente->apellido);
}

int idTCliente(TCliente cliente){
    return cliente->id;
}

int edadTCliente(TCliente cliente){
    return cliente->edad;
}

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
