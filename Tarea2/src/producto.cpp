#include "../include/producto.h"

struct rep_producto {
    int id;
    char nombre[MAX_NOMBRE_PRODUCTO];
    int precio;
    TFecha fechaIngreso;
};


TProducto crearTProducto(int id, const char nombre[MAX_NOMBRE_PRODUCTO], int precio, TFecha fechaIngreso){
    TProducto nuevoProducto = new rep_producto;

    if (nuevoProducto != NULL) {
        nuevoProducto->id = id;
        strcpy(nuevoProducto->nombre, nombre);
        nuevoProducto->precio = precio;
        nuevoProducto->fechaIngreso = fechaIngreso;
    }

    return nuevoProducto;
}

int idTProducto(TProducto producto){
    return producto->id;
}

int precioTProducto(TProducto producto){
    return producto->precio;
}

void imprimirTProducto(TProducto producto){
    if (producto != NULL){
        printf("Producto: %d\n", producto->id);
        printf("%s\n", producto->nombre);
        printf("Precio: %d\n", producto->precio);
        printf("Ingresado el: ");
        imprimirTFecha(producto->fechaIngreso);
    }
}

void liberarTProducto(TProducto &producto){
    if (producto != NULL){
        if (producto->fechaIngreso != NULL){
            liberarTFecha(producto->fechaIngreso);
        }
        
        delete producto;
        producto = NULL;
    }
}
