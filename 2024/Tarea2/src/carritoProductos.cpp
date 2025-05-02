#include "../include/carritoProductos.h"

struct rep_carritoProductos{
    TProducto producto;
    rep_carritoProductos * sig;
};

// Función para crear un elemento de tipo TCarritoProductos.
// Devuelve un carrito de productos vacío.
TCarritoProductos crearCarritoProductosVacio(){
    TCarritoProductos nuevoCarrito = NULL;
    return nuevoCarrito;
}

// Función para agregar un producto a un carrito de productos.
// Inserta el producto en el carrito, ordenado de menor a mayor por ID producto.
// La función es Theta(n) peor caso, siendo n la cantidad de productos en el carrito
// PRE: no existe producto con el mismo id en la carrito
void insertarProductoCarritoProductos(TCarritoProductos &carritoProductos, TProducto producto){
    rep_carritoProductos *nuevo = new rep_carritoProductos;
    nuevo->producto = producto;

    // Caso 1 - Se insertar al principio si el carrito esta vacio o si el nuevo producto añadido debe de ir primero
    if (carritoProductos == NULL || (idTProducto(carritoProductos->producto) >= idTProducto(producto))){
        nuevo->sig = carritoProductos;
        carritoProductos = nuevo;
    } else {
        // Caso 2 - Busco la posicion correcta de la lista para insertar
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

// Función para imprimir todos los productos de un carrito.
// El formato en el que se debe imprimir el carrito es utilizando de forma secuencial la función imprimirTProducto.
// Si la colección está vacía no imprime nada.
void imprimirCarritoProductos(TCarritoProductos carritoProductos){
    rep_carritoProductos *actual = carritoProductos;

    while (actual != NULL){
        imprimirTProducto(actual->producto);
        actual = actual->sig;
    }
}

// Función para liberar un carrito de productos
// Recibe una referencia a un elemento de tipo TCarritoProductos y libera su memoria
// Libera además la memoria de cada uno de los productos en el carrito.
void liberarCarritoProductos(TCarritoProductos &carritoProductos){
    rep_carritoProductos *nodoActual = carritoProductos;

    while (nodoActual != NULL){
        rep_carritoProductos *temp = nodoActual;
        liberarTProducto(nodoActual->producto);
        nodoActual = nodoActual->sig;
        delete temp;
    }    
    carritoProductos = NULL;
}

// Funcion para verificar si una carrito de productos es vacio, retorna true si y solo si el carrito es vacío
bool esVacioCarritoProductos(TCarritoProductos carritoProductos){
    return carritoProductos != NULL ?  false :  true;
}

// Función para verificar si un producto existe en un carrito de productos.
// Recibe una carrito de productos y un id de producto y regresa un booleano indicando su existencia.
bool existeProductoCarritoProductos(TCarritoProductos carritoProductos, int idProducto){
    rep_carritoProductos *idActual = carritoProductos;

    // Recorre la lista hasta encontrar la coincidencia o llegar al final
    while (idActual != NULL && idTProducto(idActual->producto) != idProducto){
        idActual = idActual->sig;
    }
    return idActual != NULL;
}

// Función para obtener un producto de un carrito de productos.
// Recibe un carrito y un id de producto y regresa el producto con ese id.
// PRE: El producto debe estar en el carrito
TProducto obtenerProductoCarritoProductos(TCarritoProductos carritoProductos, int idProducto) {
    rep_carritoProductos *idActual = carritoProductos;

    while (idActual != NULL && idTProducto(idActual->producto) != idProducto){
        idActual = idActual->sig;
    }

    return idActual->producto;
}

// Función para remover un producto de un carrito.
// Recibe un carrito de productos y un id de producto y elimina el producto con ese id.
// También elimina la memoria asociada a dicho producto.
// PRE: El producto debe estar en el carrito
void removerProductoCarritoProductos(TCarritoProductos &carritoProductos, int idProducto){

    // Verificamos si el producto se encuentra en el primer nodo
    if (idTProducto(carritoProductos->producto) == idProducto){
        rep_carritoProductos *temp = carritoProductos;
        carritoProductos = carritoProductos->sig;

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
