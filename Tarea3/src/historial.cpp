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

THistorial crearTHistorial(TFecha fecha) {
  THistorial historial = new rep_historial;
  historial->fechaActual = fecha;
  historial->PromFinalizadas = NULL;
  historial->PromActivas = NULL;
  historial->PromFuturas = NULL;

  return historial;
}

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

// todo Revisar 
//* PRE: fecha es posterior a la fechaActual de historial
void avanzarAFechaTHistorial(THistorial historial, TFecha fecha) {

  // Actualizamos la fecha del historial
  liberarTFecha(historial->fechaActual);
  historial->fechaActual = fecha;


  // Procesamos las listas usando las funciones del módulo
  TListaPromociones promocionesFinalizadas = obtenerPromocionesFinalizadas(historial->PromActivas, fecha);
  TListaPromociones promocionesActivas = obtenerPromocionesActivas(historial->PromFuturas, fecha);

  // Actualizamos las listas en el historial
  TListaPromociones oldPromoFinalizadas = historial->PromFinalizadas;
  TListaPromociones oldPromoActivas = historial->PromActivas;
  historial->PromFinalizadas = unirListaPromociones(historial->PromFinalizadas, promocionesFinalizadas);
  historial->PromActivas = unirListaPromociones(historial->PromActivas, promocionesActivas);

  // Liberar memoria de las listas intermedias si no se usan más.
  if (promocionesFinalizadas != NULL) {
    liberarTListaPromociones(promocionesFinalizadas, false);
  }
  if (promocionesActivas != NULL) {
    liberarTListaPromociones(promocionesActivas, false);
  }
  liberarTListaPromociones(oldPromoActivas, false);
  liberarTListaPromociones(oldPromoFinalizadas, false);
}

void imprimirPromocionesFinalizadosTHistorial(THistorial historial) {
    imprimirTListaPromociones(historial->PromFinalizadas);
}

void imprimirPromocionesActivasTHistorial(THistorial historial) {
    imprimirTListaPromociones(historial->PromActivas);
}

void imprimirPromocionesFuturasTHistorial(THistorial historial) {
  imprimirTListaPromociones(historial->PromFuturas);
}

bool esCompatiblePromocionTHistorial(THistorial historial, TPromocion promocion) { 
    return esCompatibleTListaPromociones(historial->PromFinalizadas, promocion) &&
           esCompatibleTListaPromociones(historial->PromActivas, promocion) &&
           esCompatibleTListaPromociones(historial->PromFuturas, promocion);
}

void liberarTHistorial(THistorial &historial) {
  liberarTListaPromociones(historial->PromFinalizadas,true);
  liberarTListaPromociones(historial->PromActivas,true);
  liberarTListaPromociones(historial->PromFuturas,true);
  liberarTFecha(historial->fechaActual); 
  delete historial;
  historial = NULL;
}
