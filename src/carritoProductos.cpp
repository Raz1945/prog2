#include "../include/carritoProductos.h"

struct rep_carritoProductos{
    TProducto producto;
    rep_carritoProductos * sig;
};


TCarritoProductos crearCarritoProductosVacio(){
    TCarritoProductos nuevoCarrito = NULL;
    return nuevoCarrito;
}

// PRE: no existe producto con el mismo id en la carrito
void insertarProductoCarritoProductos(TCarritoProductos &carritoProductos, TProducto producto){
    rep_carritoProductos *nuevo = new rep_carritoProductos;
    nuevo->producto = producto;

    // Caso 1: Insertar al principio si el carrito está vacio o si el nuevo producto añadido debe ser el primero
    if (carritoProductos == NULL || (idTProducto(carritoProductos->producto) >= idTProducto(producto))){
        nuevo->sig = carritoProductos;
        carritoProductos = nuevo;
    } else {
        // Caso 2: Busco la posicion correcta de la lista para insertar
        rep_carritoProductos *actual = carritoProductos;
        rep_carritoProductos *siguiente = actual->sig;

        while (siguiente != NULL && idTProducto(siguiente->producto) < idTProducto(producto)) {
            actual = siguiente;
            siguiente = siguiente->sig;
        }

        // Insertamos el nuevo nodo entre actual y siguiente
        nuevo->sig = siguiente;
        actual->sig = nuevo;
    }
}

void imprimirCarritoProductos(TCarritoProductos carritoProductos){
    rep_carritoProductos *actual = carritoProductos;

    while (actual != NULL){
        imprimirTProducto(actual->producto);
        actual = actual->sig;
    }
}

void liberarCarritoProductos(TCarritoProductos &carritoProductos){
    rep_carritoProductos *actual = carritoProductos;

    while (actual != NULL){
        rep_carritoProductos *temp = actual; // referencia al nodo actual
        liberarTProducto(actual->producto);
        actual = actual->sig;
        delete temp;
    }    
    carritoProductos = NULL;
}

bool esVacioCarritoProductos(TCarritoProductos carritoProductos){
    return carritoProductos != NULL ?  false :  true;
}

bool existeProductoCarritoProductos(TCarritoProductos carritoProductos, int idProducto){
    rep_carritoProductos *idActual = carritoProductos;

    // Recorre la lista hasta encontrar la coincidencia o llegar al final
    while (idActual != NULL && idTProducto(idActual->producto) != idProducto){
        idActual = idActual->sig;
    }
    return idActual != NULL;
}

// PRE: El producto debe estar en el carrito
TProducto obtenerProductoCarritoProductos(TCarritoProductos carritoProductos, int idProducto) {
    // Recorremos la lista hasta encontrar el producto con dicho id 
    rep_carritoProductos *idActual = carritoProductos;

    while (idActual != NULL && idTProducto(idActual->producto) != idProducto){
        idActual = idActual->sig;
    }

    return idActual->producto;
}

// PRE: El producto debe estar en el carrito
void removerProductoCarritoProductos(TCarritoProductos &carritoProductos, int idProducto){

    // Verificamos si el producto se encuentra en el primer nodo
    if (idTProducto(carritoProductos->producto) == idProducto){
        rep_carritoProductos *temp = carritoProductos;
        carritoProductos = carritoProductos->sig; // encabezamos el siguiente nodo, como cabeza de la lista

        liberarTProducto(temp->producto);
        delete temp;
    }

    // Si no es el primer nodo
    rep_carritoProductos *idActual = carritoProductos;
    rep_carritoProductos *anterior = NULL;

    while (idActual != NULL && idTProducto(idActual->producto) != idProducto){
        anterior = idActual; // Posicion del nodo previo
        idActual = idActual->sig;
    }

    if (idActual != NULL){
        anterior->sig = idActual->sig; // Aputamos el nodo previo al siguiente a eliminar
        liberarTProducto(idActual->producto);
        delete idActual;
    }
        
}
