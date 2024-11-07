#include "../include/envio.h"

struct rep_envio {
  TCarritoProductos carrito;
  TFecha fecha;
  rep_envio* sig;

};

TEnvio crearTEnvio(TCarritoProductos carrito, TFecha fecha) {
  TEnvio nuevo = new rep_envio;
  nuevo->carrito = carrito;
  nuevo->fecha = fecha;
  nuevo->sig = NULL;

  return nuevo;
}

void liberarTEnvio(TEnvio &envio) {
  TEnvio aBorrar;
  while (envio != NULL) {
    aBorrar = envio;
    envio = envio->sig;
    liberarCarritoProductos(aBorrar->carrito);
    liberarTFecha(aBorrar->fecha);
    delete aBorrar;
  }

  envio = NULL;
}

TCarritoProductos obtenerCarritoProductosTEnvio(TEnvio envio) {
  return envio->carrito;
}

TFecha obtenerFechaTEnvio(TEnvio envio) {
   return envio->fecha;
}

void imprimirTEnvio(TEnvio envio) {
    imprimirCarritoProductos(envio->carrito);
    printf("\n");
    printf("Fecha del envio: ");
    imprimirTFecha(envio->fecha);
    printf("\n");
}
