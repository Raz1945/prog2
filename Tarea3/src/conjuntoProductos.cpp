#include "../include/conjuntoProductos.h"

// Definición de tipo TConjuntoProductos como un puntero a rep_conjuntoproductos
//* El conjunto es acotado, y la cantidad máxima de elementos define el rango de identificadores que almacena.
// Los identificadores que almacena el conjunto cumplen 0 <= id < cantMax
struct rep_conjuntoProductos{
    int* ArrayIdProductos;   //* Array para almacenar los identificadores de productos 
    bool* productoRegistrado;   //* Array para saber la existencia de productos
    int cantidadActual;  // tope ~ cantidad actual de productos
    int maxProductos;   // cota ~ cantidad maxima de productos
};
    
// check Testear
TConjuntoProductos crearTConjuntoProductos(int cantMax){
    TConjuntoProductos nuevoConjunto = new rep_conjuntoProductos;   // Asigna memoria para el conjunto
    nuevoConjunto->ArrayIdProductos = new int[cantMax]();   //* Asigna e inicializa el array de enteros en 0
    nuevoConjunto->productoRegistrado = new bool[cantMax]();    //* Asigna e inicializa el array de booleanos en false
    nuevoConjunto->cantidadActual = 0;
    nuevoConjunto->maxProductos = cantMax;    
    return nuevoConjunto;
}

// check Testear
void insertarTConjuntoProductos(TConjuntoProductos &conjuntoProductos, int idProducto){
    // Veriicamos que este en el rango valido
    if (0 <= idProducto  && idProducto < conjuntoProductos->maxProductos) {
        // Verificamos si ya fue registrado el producto
        if (!conjuntoProductos->productoRegistrado[idProducto]){
            conjuntoProductos->ArrayIdProductos[conjuntoProductos->cantidadActual] = idProducto;
            conjuntoProductos->productoRegistrado[idProducto] = true;
            conjuntoProductos->cantidadActual++;
        }        
    }
}

// check Testear
void imprimirTConjuntoProductos(TConjuntoProductos conjuntoProductos){
    for (int i = 0; i < conjuntoProductos->maxProductos; i++) {
        // note:
        //  Se utiliza el array 'productoRegistrado' para iterar desde el menor identificador al mayor, 
        //  imprimiendo solo aquellos que esten marcados como true. 
        //  De esta manera se garantiza que el orden sera de menor a mayor.
        if (conjuntoProductos->productoRegistrado[i]) {
            printf("%d ", i);
        }
    }
    printf("\n");
}

// check Testear
void liberarTConjuntoProductos(TConjuntoProductos &conjuntoProductos){
    delete[] conjuntoProductos->ArrayIdProductos;   //* Liberamos la memoria ocupada por el array de identificadores
    delete[] conjuntoProductos->productoRegistrado; //* Liberamos la memoria ocupada por el array de registros
    delete conjuntoProductos;   // Liberamos la memoria de la estructura
    conjuntoProductos = NULL;
}

// check Testear 
bool esVacioTConjuntoProductos(TConjuntoProductos conjuntoProductos){ 
    return conjuntoProductos->cantidadActual == 0;
}

// check Testear 
int cantidadTConjuntoProductos(TConjuntoProductos conjuntoProductos){ 
    return conjuntoProductos->cantidadActual; 
}

// check Testear 
int cantMaxTConjuntoProductos(TConjuntoProductos conjuntoProductos){ 
    return conjuntoProductos->maxProductos;
}

// check Testear
bool perteneceTConjuntoProductos(TConjuntoProductos conjuntoProductos, int idProducto){ 
    // Verificamos que el conjunto no sea nulo y que el id esté dentro del rango válido
    if (conjuntoProductos == NULL || idProducto < 0 || idProducto >= conjuntoProductos->maxProductos) {
        return false;
    } 
    return conjuntoProductos->productoRegistrado[idProducto];
}

// check Testear
void borrarDeTConjuntoProductos(TConjuntoProductos &conjuntoProductos, int idProducto){
    // Verificamos que el conjunto no sea nulo y que el id esté dentro del rango válido
    if (conjuntoProductos != NULL && 0 <= idProducto && idProducto < conjuntoProductos->maxProductos) {

        // Verificamos si el producto está registrado
        if (conjuntoProductos->productoRegistrado[idProducto]) {

            // Marcamos el producto como no registrado
            conjuntoProductos->productoRegistrado[idProducto] = false;

            // Buscamos el idProducto en el array de productos
            for (int i = 0; i < conjuntoProductos->cantidadActual; i++) {
                if (conjuntoProductos->ArrayIdProductos[i] == idProducto) {
        
                    // Reemplazamos el idProducto actual con el último del array
                    int ultimaPosicion = conjuntoProductos->cantidadActual - 1;
                    conjuntoProductos->ArrayIdProductos[i] = conjuntoProductos->ArrayIdProductos[ultimaPosicion];
                    break;
                }
            }

            // Disminuimos la cantidad actual de productos
            conjuntoProductos->cantidadActual--;
        }
    } 
}

// check TESTEAR 
//<> Tiene una pregunta 
TConjuntoProductos unionTConjuntoProductos(TConjuntoProductos conjuntoProductos1, TConjuntoProductos conjuntoProductos2){

    if (conjuntoProductos1 == NULL){
        return conjuntoProductos2;
    }
    
    if (conjuntoProductos2 == NULL){
        return conjuntoProductos1;
    }

    //? PREGUNTAR
    // No me queda clar si el 'conjuntoUnion' tiene que tener la misma ó una mayor capacidad de almacenamiento (la suma de ambos)
    // En el caso de que ambos conjuntos esten completos. Como tienen la misma cantidad máxima de elementos, "n". 
    // El 'conjuntoUnion' tendria que ser la suma de las capacidades ambos.
    int maximo = conjuntoProductos1->maxProductos + conjuntoProductos2->maxProductos;

    // Si el 'conjuntoUnion' tuviera que respetar la capacidad maxima de elementos de cualquiera de los conjuntos
    // int maximo = conjuntoProductos1->maxProductos; 

    // Creamo el conjuntoUnion
    TConjuntoProductos conjuntoUnion = crearTConjuntoProductos(maximo);

    // Insertamos los elementos del conjuntoProductos1
    for (int i = 0; i < conjuntoProductos1->cantidadActual; i++){
        int idProducto = conjuntoProductos1->ArrayIdProductos[i];

        // Verificamos si el producto no esta registrado en conjuntoUnion
        if (!conjuntoUnion->productoRegistrado[idProducto]){
            conjuntoUnion->productoRegistrado[idProducto] = true;
            conjuntoUnion->ArrayIdProductos[conjuntoUnion->cantidadActual] = idProducto;
            conjuntoUnion->cantidadActual++;
        }
    }

    // Hacemos lo mismo con el conjuntoProducto2
    for (int i = 0; i < conjuntoProductos2->cantidadActual; i++){
        int idProducto = conjuntoProductos2->ArrayIdProductos[i];

        if (!conjuntoUnion->productoRegistrado[idProducto]){
            conjuntoUnion->productoRegistrado[idProducto] = true;
            conjuntoUnion->ArrayIdProductos[conjuntoUnion->cantidadActual] = idProducto;
            conjuntoUnion->cantidadActual++;
        }
    }

    return conjuntoUnion;
}

// check TESTEAR 

TConjuntoProductos interseccionTConjuntoProductos(TConjuntoProductos conjuntoProductos1, TConjuntoProductos conjuntoProductos2){ 
    // Verifico la existencia de los conjuntos
    if (conjuntoProductos1 == NULL || conjuntoProductos2 == NULL){
        return crearTConjuntoProductos(0);  // retornamos un conjunto vacío al no haber elementos en común
    }
    
    int maximo = conjuntoProductos1->maxProductos;
    TConjuntoProductos conjuntoInterseccion = crearTConjuntoProductos(maximo);

    // Insertamos en el 'conjuntoInterseccion' los elementos en común
    for (int i = 0; i < conjuntoProductos1->cantidadActual; i++){
        int idProducto = conjuntoProductos1->ArrayIdProductos[i];

        if (conjuntoProductos2->productoRegistrado[idProducto]){
            conjuntoInterseccion->productoRegistrado[idProducto] = true;
            conjuntoInterseccion->ArrayIdProductos[conjuntoInterseccion->cantidadActual] = idProducto;
            conjuntoInterseccion->cantidadActual++;
        }        
    }
    
    return conjuntoInterseccion;
}

// check TESTEAR 
//<> Tiene una pregunta 
TConjuntoProductos diferenciaTConjuntoProductos(TConjuntoProductos conjuntoProductos1, TConjuntoProductos conjuntoProductos2){ 
    // Verifico la existencia de los conjuntos
    if (conjuntoProductos1 == NULL || conjuntoProductos2 == NULL){
        return crearTConjuntoProductos(0);  // retornamos un conjunto vacío
    }

    //? PREGUNTAR
    // El 'conjuntoDiferencia' tiene que tener la misma ó una mayor capacidad de almacenamiento
    // En el caso de que ambos conjuntos esten completos y todos sus elementos sean diferentes a los del otro conjunto.
    // Como tienen la misma cantidad máxima de elementos, "n".
    // El 'conjuntoDiferencia' tendria que ser la suma de las capacidades ambos.
    int maximo = conjuntoProductos1->maxProductos + conjuntoProductos2->maxProductos;

    // Si se tuviera que respetar el cantMax 
    // int maximo = conjuntoProductos1->maxProductos;

    TConjuntoProductos conjuntoDiferencia = crearTConjuntoProductos(maximo);

    // Insertamos en el 'conjuntoDiferencia' los elementos que no tengan en común
    for (int i = 0; i < conjuntoProductos1->cantidadActual; i++){
        int idProducto = conjuntoProductos1->ArrayIdProductos[i];

        // Verificamos que el producto no esté registrado en conjuntoProductos2
        if (!conjuntoProductos2->productoRegistrado[idProducto]){
            conjuntoDiferencia->productoRegistrado[idProducto] = true;            
            conjuntoDiferencia->ArrayIdProductos[conjuntoDiferencia->cantidadActual] = idProducto;
            conjuntoDiferencia->cantidadActual++;
        }
    }
    
    return conjuntoDiferencia; 
}
