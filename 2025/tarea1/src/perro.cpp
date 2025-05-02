#include "../include/perro.h"

struct rep_perro {
  /************ Parte 4.1 ************/
  /*Escriba el código a continuación */
  int id;
  char nombre[MAX_NOMBRE];
  nat edad;
  nat vitalidad;
  char descripcion[MAX_DESCRIPCION];
  TFecha fechaIngreso;
  /****** Fin de parte Parte 4.1 *****/
};

TPerro crearTPerro(int id, const char nombre[MAX_NOMBRE], nat edad, nat vitalidad, const char descripcion[MAX_DESCRIPCION], TFecha fechaIngreso) {
  TPerro nuevoPerro = NULL;
  nuevoPerro = new rep_perro;
  nuevoPerro->id = id;
  strcpy(nuevoPerro->nombre, nombre);
  nuevoPerro->edad = edad;
  nuevoPerro->vitalidad = vitalidad;
  strcpy(nuevoPerro->descripcion, descripcion);
  nuevoPerro->fechaIngreso = fechaIngreso;
  return nuevoPerro;
}

void liberarTPerro(TPerro &perro) {
  if (perro != NULL) {
    if (perro->fechaIngreso != NULL) {
      liberarTFecha(perro->fechaIngreso);
    };

    delete perro;
    perro = NULL;
  }
}

int idTPerro(TPerro perro) {
  return perro->id;
}

char* nombreTPerro(TPerro perro) {
  return perro->nombre;
}

nat edadTPerro(TPerro perro) {
  return perro->edad;
}

nat vitalidadTPerro(TPerro perro) {
  return perro->vitalidad;
}

char* descripcionTPerro(TPerro perro) {
  return perro->descripcion;
}

TFecha fechaIngresoTPerro(TPerro perro) {
  return perro->fechaIngreso;
}

void imprimirTPerro(TPerro perro) {
  printf("Perro %d\n", idTPerro(perro));
  printf("Nombre: %s\n", nombreTPerro(perro));
  printf("Edad: %d\n", edadTPerro(perro));
  printf("Descripcion: %s\n", descripcionTPerro(perro));
  printf("Fecha de ingreso: ");
  imprimirTFecha(fechaIngresoTPerro(perro));
  printf("Vitalidad: %d\n",vitalidadTPerro(perro));
}

TPerro copiarTPerro(TPerro perro) {
  TPerro copia = new rep_perro;
  copia->id = idTPerro(perro);
  strcpy(copia->nombre, nombreTPerro(perro));
  copia->edad = edadTPerro(perro);
  copia->vitalidad = vitalidadTPerro(perro);
  strcpy(copia->descripcion, descripcionTPerro(perro));
  copia->fechaIngreso = copiarTFecha(fechaIngresoTPerro(perro));
  return copia;
}

void actualizarEdadTPerro(TPerro &perro, nat nuevaEdad) {
  perro->edad = nuevaEdad;
}

void actualizarVitalidadTPerro(TPerro &perro, nat nuevaVitalidad) {
  perro->vitalidad = nuevaVitalidad;
}
