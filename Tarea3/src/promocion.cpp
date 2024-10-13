#include "../include/promocion.h"
#include "../include/conjuntoProductos.h" 

//  La estructura almacena un id de tipo entero, dos fechas para representar el inicio y el fin 
// de la promocion, así como la información de qué productos forman parte de la promocion.
struct rep_promocion {
  int idProm;
  TFecha fechaInicial;
  TFecha fechaFininal;
  TConjuntoProductos conjuntoProductos;
};

// check Testear 
TPromocion crearTPromocion(int idProm, TFecha ini, TFecha fin, int cantMax){ 
  TPromocion nuevaPromo = new rep_promocion;
  nuevaPromo->idProm = idProm;
  nuevaPromo->fechaInicial = ini;
  nuevaPromo->fechaFininal = fin;
  nuevaPromo->conjuntoProductos = crearTConjuntoProductos(cantMax) ;

  return nuevaPromo;
}

// check Testear 
void agregarATPromocion(TPromocion &prom, TProducto p){
  // Verificamos que 'prom'y que el producto existan
  if (prom != NULL && p!= NULL){
      insertarTConjuntoProductos(prom->conjuntoProductos, idTProducto(p));
  }
}

// check Testear 
void imprimirTPromocion(TPromocion prom){
  printf("Promocion #%d del ",prom->idProm);
  imprimirTFecha(prom->fechaInicial);
  printf(" al ");
  imprimirTFecha(prom->fechaFininal);
  printf("\n");

  printf("Productos: ");
  imprimirTConjuntoProductos(prom->conjuntoProductos);
}

// check Testear 
void liberarTPromocion(TPromocion &prom){
  liberarTFecha(prom->fechaInicial);
  liberarTFecha(prom->fechaFininal);
  liberarTConjuntoProductos(prom->conjuntoProductos);
  delete prom;
  prom = NULL;
}

// check Testear 
bool perteneceATPromocion(TPromocion prom, TProducto p){
  if (prom == NULL || p == NULL) return false;
  return perteneceTConjuntoProductos(prom->conjuntoProductos, idTProducto(p));  
}

// check Testear 
int idTPromocion(TPromocion prom){ 
  if (prom == NULL) return 0; 
  return prom->idProm;
}

// check Testear 
TFecha fechaInicioTPromocion(TPromocion prom){ 
  if (prom == NULL) return NULL; 
  return prom->fechaInicial;
}

// check Testear 
TFecha fechaFinTPromocion(TPromocion prom){
  if (prom == NULL) return NULL; 
  return prom->fechaFininal;
}

// check Testear

bool sonPromocionesCompatibles(TPromocion prom1, TPromocion prom2) { 
    
    if (prom1 == NULL || prom2 == NULL) return false;

    // Verificamos si las fechas se superponen
    if (compararTFechas(fechaInicioTPromocion(prom1), fechaFinTPromocion(prom2)) <= 0 &&
        compararTFechas(fechaFinTPromocion(prom1), fechaInicioTPromocion(prom2)) >= 0) {
        // Si hay superposición de fechas, verificamos productos
        TConjuntoProductos resesultado = interseccionTConjuntoProductos(prom1->conjuntoProductos, prom2->conjuntoProductos);
        
        // Si hay productos en la intersección, las promociones no son compatibles
        bool sonCompatibles = esVacioTConjuntoProductos(resesultado);
        
        liberarTConjuntoProductos(resesultado); // Liberamos la memoria
        
        return sonCompatibles;
    }
    return true;
}
