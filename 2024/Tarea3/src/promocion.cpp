#include "../include/promocion.h"
#include "../include/conjuntoProductos.h" 

//  La estructura almacena un id de tipo entero, dos fechas para representar el inicio y el fin 
// de la promocion, así como la información de qué productos forman parte de la promocion.
struct rep_promocion {
  int idProm;
  TFecha fechaInicial;
  TFecha fechaFinal;
  TConjuntoProductos conjuntoProductos;
};

TPromocion crearTPromocion(int idProm, TFecha ini, TFecha fin, int cantMax){ 
  TPromocion nuevaPromo = new rep_promocion;
  nuevaPromo->idProm = idProm;
  nuevaPromo->fechaInicial = ini;
  nuevaPromo->fechaFinal = fin;
  nuevaPromo->conjuntoProductos = crearTConjuntoProductos(cantMax) ;

  return nuevaPromo;
}

void agregarATPromocion(TPromocion &prom, TProducto p){
  // Verificamos que exitan tanto la promocion como el producto
  if (prom != NULL && p!= NULL){
      insertarTConjuntoProductos(prom->conjuntoProductos, idTProducto(p));
  }
}

void imprimirTPromocion(TPromocion prom){
  printf("Promocion #%d del ",prom->idProm);
  imprimirTFecha(prom->fechaInicial);
  printf(" al ");
  imprimirTFecha(prom->fechaFinal);
  printf("\n");

  printf("Productos: ");
  imprimirTConjuntoProductos(prom->conjuntoProductos);
}

void liberarTPromocion(TPromocion &prom){
  liberarTFecha(prom->fechaInicial);
  liberarTFecha(prom->fechaFinal);
  liberarTConjuntoProductos(prom->conjuntoProductos);

  delete prom;
  prom = NULL;
}

bool perteneceATPromocion(TPromocion prom, TProducto p){
  if (prom == NULL || p == NULL) return false;
  return perteneceTConjuntoProductos(prom->conjuntoProductos, idTProducto(p));  
}

int idTPromocion(TPromocion prom){ 
  if (prom == NULL) return 0; 
  return prom->idProm;
}

TFecha fechaInicioTPromocion(TPromocion prom){ 
  if (prom == NULL) return NULL; 
  return prom->fechaInicial;
}

TFecha fechaFinTPromocion(TPromocion prom){
  if (prom == NULL) return NULL; 
  return prom->fechaFinal;
}

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
