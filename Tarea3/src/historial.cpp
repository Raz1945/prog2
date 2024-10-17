#include "../include/historial.h"

// El historial está compuesto por tres listas de promociones: pasadas, activas y futuras. 
// Además, almacena la fecha actual (representada con una variable de tipo TFecha), 
// para poder determinar cuáles promociones están activas; cuáles, pasadas y cuáles, futuras.
struct rep_historial {
  TListaPromociones PromFinalizadas;  
  TListaPromociones PromActivas;    
  TListaPromociones PromFuturas;  
  TFecha fechaActual;
};

// check Testear 
THistorial crearTHistorial(TFecha fecha) {
  THistorial historial = new rep_historial;
  historial->fechaActual = fecha;
  historial->PromFinalizadas = NULL;
  historial->PromActivas = NULL;
  historial->PromFuturas = NULL;

  return historial;
}

// check Testear 
//* PRE: esCompatiblePromocionHistorial
void agregarPromocionTHistorial(THistorial historial, TPromocion promocion) {
  if (historial != NULL) {

    // Verifico si la fecha de culminacion de la nueva promocion esta vencida, es vigente o no ha comenzado
    if (compararTFechas(historial->fechaActual, fechaFinTPromocion(promocion)) > 0) {
      // Caso 1: Promocion ya finalizada (fechaActual > fechaFinPromocion)
      agregarPromocionTListaPromociones(historial->PromFinalizadas, promocion);

    } else if (compararTFechas(fechaInicioTPromocion(promocion), historial->fechaActual) <= 0 &&
               compararTFechas(historial->fechaActual, fechaFinTPromocion(promocion)) <= 0) {
      // Caso 2: Promocion activa (fechaInicio <= fechaActual <= fechaFin)
      agregarPromocionTListaPromociones(historial->PromActivas, promocion);

    } else if (compararTFechas(fechaInicioTPromocion(promocion), historial->fechaActual) > 0) {
      // Caso 3: Promocion futura (fechaInicio > fechaActual)
      agregarPromocionTListaPromociones(historial->PromFuturas, promocion);  
    }
  }
}

// check Testear 
//* PRE: No existe el producto (con 'idProducto') en la promoción del historial
//* PRE: existe una promoción en el historial con id 'idPromo'
void agregarProductoAPromocionTHistorial(THistorial historial, TProducto producto, int idPromo) {
  if (historial != NULL) {
    TPromocion promocion = NULL;

    // Verificamos si la promocion pertenece a las 'finalizadas'
    if (pertenecePromocionTListaPromociones(historial->PromFinalizadas, idPromo)) {
      promocion = obtenerPromocionTListaPromociones(historial->PromFinalizadas, idPromo);
    }
    // Verificamos si la promocion pertenece a las 'activas'
    else if (pertenecePromocionTListaPromociones(historial->PromActivas, idPromo)) {
      promocion = obtenerPromocionTListaPromociones(historial->PromActivas, idPromo);
    }
    // Verificamos si la promocion pertenece a las 'futuras'
    else if (pertenecePromocionTListaPromociones(historial->PromFuturas, idPromo)) {
      promocion = obtenerPromocionTListaPromociones(historial->PromFuturas, idPromo);
    }

    // Si se encontro la promocion, se agrega el producto
    if (promocion != NULL) {
      agregarATPromocion(promocion, producto);
    }
  }
}

void avanzarAFechaTHistorial(THistorial historial, TFecha fecha) {
  
}

void imprimirPromocionesFinalizadosTHistorial(THistorial historial) {}

void imprimirPromocionesActivasTHistorial(THistorial historial) {}

void imprimirPromocionesFuturasTHistorial(THistorial historial) {}

bool esCompatiblePromocionTHistorial(THistorial historial, TPromocion promocion) { return false; }

// check Testear 
void liberarTHistorial(THistorial &historial) {
  if (historial != NULL){
    liberarTListaPromociones(historial->PromFinalizadas,true);
    liberarTListaPromociones(historial->PromActivas,true);
    liberarTListaPromociones(historial->PromFuturas,true);
    liberarTFecha(historial->fechaActual); 
    delete historial;
    historial = NULL;
  }
}
