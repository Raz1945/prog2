#include "../include/refugio.h"

struct rep_refugio {
  /************ Parte 5.1 ************/
  /*Escriba el código a continuación */
  TPerro APerros[MAX_PERROS];
  int tope;
  /****** Fin de parte Parte 5.1 *****/
};

TRefugio crearTRefugio() {
  TRefugio refugio = NULL;
  refugio = new rep_refugio;
  refugio->tope = 0;
  return refugio; 
}

void liberarTRefugio(TRefugio& refugio) {
  if (refugio != NULL) {
    for (int i = 0; i < refugio->tope; i++) {
      liberarTPerro(refugio->APerros[i]);     
    };
    
    delete refugio;
    refugio = NULL;
  }
}

 void agregarEnTRefugio(TRefugio& refugio, TPerro perro) {
    // Verifica si el refugio no esta lleno
  if (refugio->tope < MAX_PERROS) {
    int i = refugio->tope; 

    // Buscamos la posicion adecuada para insertar el perro
    while (i > 0 && compararTFechas(fechaIngresoTPerro(perro), fechaIngresoTPerro(refugio->APerros[i - 1])) < 0) {
      refugio->APerros[i] = refugio->APerros[i - 1];  //! Desplazo a la derecha los perros cuya fecha es mayor que la del nuevo perro
      i--;
    }

    // Insertamos el perro en la posicion adecuada
    refugio->APerros[i] = perro;
    refugio->tope++;
  }
}

void imprimirTRefugio(TRefugio refugio) {
  if (refugio->tope > 0)  {    
    for (int i = 0; i < refugio->tope; i++) {
      imprimirTPerro(refugio->APerros[i]);   
    }
  }
}

bool estaEnTRefugio(TRefugio refugio, int id) {
  int i = 0;
  while (i < refugio->tope && idTPerro(refugio->APerros[i]) != id) {
    i++;
  }
  return (i < refugio->tope);
}

// PRE: El perro debe estar en el refugio
TPerro obtenerDeTRefugio(TRefugio refugio, int id) {
  int i = 1;

  // Buscamos la posicion
  while (i < refugio->tope && (idTPerro(refugio->APerros[i]) != id)){
    i++;
  }
  return refugio->APerros[i];
}

bool ingresaronPerrosFechaTRefugio(TRefugio refugio, TFecha fecha) {
  bool ingresaron = false;
  int ini = 0;
  int fin = refugio->tope - 1;
  
  while (ini <= fin && !ingresaron) {
    int med = ini + (fin - ini) / 2;
    int comparacionFechas = compararTFechas(fechaIngresoTPerro(refugio->APerros[med]), fecha);
    
    if (comparacionFechas == 0) {
      ingresaron = true;
    } else if (comparacionFechas == 1) {
      fin = med - 1;  // Busco a la izquierda.
    } else { 
      ini = med + 1;  // Busco a la derecha.
    }
  }
  
  return ingresaron;
}

void imprimirPerrosFechaTRefugio(TRefugio refugio, TFecha fecha) {
  int i = 0;

  while (i < refugio->tope && compararTFechas(fechaIngresoTPerro(refugio->APerros[i]), fecha) != 0) {
    i++;
  }

  while (i < refugio->tope && compararTFechas(fechaIngresoTPerro(refugio->APerros[i]), fecha) == 0) {
    imprimirTPerro(refugio->APerros[i]);
    i++;
  }
}

// PRE: El perro debe estar en el refugio
void removerDeTRefugio(TRefugio& refugio, int id) {
  int i = 0;

  while (i < refugio->tope && idTPerro(refugio->APerros[i]) != id) {
    i++;
  }

  if (i < refugio->tope) {
    liberarTPerro(refugio->APerros[i]);

    // Reacomodar los elementos del arreglo
    for (int j = i; j < refugio->tope - 1; j++) {
      refugio->APerros[j] = refugio->APerros[j + 1];
    }

    refugio->tope--;
  }
}

