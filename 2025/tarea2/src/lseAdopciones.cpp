#include "../include/lseAdopciones.h"

struct rep_lseadopciones {
	TPersona persona;
	TPerro perro;
	TFecha fechaAdopcion;
	rep_lseadopciones *sig;
};

TLSEAdopciones crearTLSEAdopcionesVacia(){
	return NULL;
}

bool esVaciaTLSEAdopciones(TLSEAdopciones lseAdopciones){
	return lseAdopciones == NULL ;
}

void imprimirTLSEAdopciones(TLSEAdopciones lseAdopciones) {
	rep_lseadopciones *actual = lseAdopciones;

	while (actual != NULL) {
			printf("---------------------------\n");
			printf("Adopcion en fecha ");
			imprimirTFecha(actual->fechaAdopcion); 

			printf("Adoptante:\n");
			printf("Persona %s %s\n", nombreTPersona(actual->persona), apellidoTPersona(actual->persona)); // CORREGIDO
			printf("CI: %d\n", ciTPersona(actual->persona));

			printf("Adoptado:\n");
			printf("Perro %d\n", idTPerro(actual->perro));
			printf("Nombre: %s\n", nombreTPerro(actual->perro));
			printf("Fecha de ingreso: ");
			imprimirTFecha(fechaIngresoTPerro(actual->perro));
			printf("---------------------------\n");

			actual = actual->sig;
	}
}

void liberarTLSEAdopciones(TLSEAdopciones &lseAdopciones){
	rep_lseadopciones *nodoActual = lseAdopciones;

	while (nodoActual != NULL)	{
		rep_lseadopciones *temp = nodoActual;
		liberarTPersona(nodoActual->persona);
		liberarTPerro(nodoActual->perro);
		liberarTFecha(nodoActual->fechaAdopcion);
		nodoActual = nodoActual->sig;
		delete temp;
	}
	
}

void insertarTLSEAdopciones(TLSEAdopciones &lseAdopciones, TFecha fecha, TPersona persona, TPerro perro) {
	rep_lseadopciones *nuevo = new rep_lseadopciones;
	nuevo->fechaAdopcion = fecha;   
	nuevo->persona = persona;       
	nuevo->perro = perro;

	// Si la lista es vacia o si se debe insertar al comienzo
	if (lseAdopciones == NULL || compararTFechas(fecha, lseAdopciones->fechaAdopcion) < 0) {
		nuevo->sig = lseAdopciones;
		lseAdopciones = nuevo;
	} else {
		//Recorremos hasta encontrar la posicion adecuada
		rep_lseadopciones *actual = lseAdopciones;
		while (actual->sig != NULL && compararTFechas(actual->sig->fechaAdopcion, fecha) <= 0) {
			actual = actual->sig;
		}
		nuevo->sig = actual->sig;
		actual->sig = nuevo;
	}
}

bool existeAdopcionTLSEAdopciones(TLSEAdopciones lseAdopciones, int ciPersona, int idPerro) {
	rep_lseadopciones *actual = lseAdopciones;

	while (actual != NULL) {
		if (ciTPersona(actual->persona) == ciPersona && idTPerro(actual->perro) == idPerro) {
			return true;
		}
		actual = actual->sig;
	}

	return false;
}

void removerAdopcionTLSEAdopciones(TLSEAdopciones &lseAdopciones, int ciPersona, int idPerro) {
	rep_lseadopciones *actual = lseAdopciones;
	rep_lseadopciones *anterior = NULL;

	while (actual != NULL) {
			if (ciTPersona(actual->persona) == ciPersona && idTPerro(actual->perro) == idPerro) {
					if (anterior == NULL) {
							// Es el primer nodo
							lseAdopciones = actual->sig;
					} else {
							anterior->sig = actual->sig;
					}

					liberarTPerro(actual->perro);
					liberarTPersona(actual->persona);
					liberarTFecha(actual->fechaAdopcion);
					delete actual;
					return;
			}

			anterior = actual;
			actual = actual->sig;
	}
}
