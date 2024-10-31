#include "../include/queja.h"

struct rep_queja {
  TFecha fecha;
  TProducto producto;
  TCliente cliente;
  char comentario[MAX_COMENTARIO];

  rep_queja* sig;
};
// En el queja.h se definio: typedef struct rep_queja *TQueja;

TQueja crearTQueja(TFecha fecha, TProducto producto, TCliente cliente,  const char comentario[MAX_COMENTARIO]) {
  TQueja nueva = new rep_queja;
  nueva->fecha = fecha;
  nueva->producto = producto;
  nueva->cliente = cliente;
  strcpy(nueva->comentario, comentario);
  return nueva;
}

void imprimirTQueja(TQueja queja) {
  printf("Fecha: ");
  imprimirTFecha(queja->fecha);
  printf("\n");
  printf("Cliente: ");
  imprimirTCliente(queja->cliente);
  imprimirTProducto(queja->producto);
  printf("\n");
  printf("Comentario: %s\n", queja->comentario);
}

void liberarTQueja(TQueja &queja) { 
  if (queja != NULL) {
    liberarTFecha(queja->fecha);
    liberarTCliente(queja->cliente);
    liberarTProducto(queja->producto);
    delete queja;
    queja = NULL;
  }
}

// TODO TESTEAR 
TFecha fechaTQueja(TQueja queja) { 
  return queja->fecha; 
}
