#include "../include/persona.h"

struct rep_persona {
	int id;
	char nombre[MAX_NOMBRE_PERSONA];
	char apellido[MAX_APELLIDO_PERSONA];
	TFecha edad;
	
	TPerro adoptados[MAX_PERROS_PERSONA];
	int tope;
};

TPersona crearTPersona(int ci, const char nombre[MAX_NOMBRE_PERSONA], const char apellido[MAX_APELLIDO_PERSONA], nat diaNac, nat mesNac, nat anioNac){
	TPersona nuevaPersona = NULL;
	nuevaPersona = new rep_persona();

	nuevaPersona->id = ci;
	strcpy(nuevaPersona->nombre, nombre);
	strcpy(nuevaPersona->apellido, apellido);
	nuevaPersona->edad = crearTFecha(diaNac, mesNac, anioNac);
	nuevaPersona->tope = 0;

	return nuevaPersona;
}

void imprimirTPersona(TPersona persona){
	printf("Persona %s %s\n", persona->nombre, persona->apellido);
	printf("CI: %d\n", persona->id);
	printf("Fecha de Nacimiento: ");
	imprimirTFecha(persona->edad);
	printf("Perros adoptados:\n");
	
	for (int i = 0; i < persona->tope; i++) {
		imprimirTPerro(persona->adoptados[i]);
	}
}

void liberarTPersona(TPersona &persona){
	if (persona != NULL)  {
		liberarTFecha(persona->edad);

		for (int i = 0; i < persona->tope; i++) {
			if (persona->adoptados[i] != NULL) {
				liberarTPerro(persona->adoptados[i]);
			}
		}

		delete persona;
		persona = NULL;
	}
}

int ciTPersona(TPersona persona){
		return persona->id;
}

char* nombreTPersona(TPersona persona){
		return persona->nombre;
}

char* apellidoTPersona(TPersona persona){
		return persona->apellido;
}

TFecha fechaNacimientoTPersona(TPersona persona){
		return persona->edad;
}

void agregarPerroTPersona(TPersona &persona, TPerro perro){
    if (persona == NULL || perro == NULL) return;
    
		if (persona->tope < MAX_PERROS_PERSONA) {
    	TPerro copiaPerro = copiarTPerro(perro);
			persona->adoptados[persona->tope] = copiaPerro;
			persona->tope++; 
	}
}

bool pertenecePerroTPersona(TPersona persona, int idPerro) {
	int i = 0;
	while (i < persona->tope && 
	       (persona->adoptados[i] == NULL || idPerro != idTPerro(persona->adoptados[i]))) {
		i++;
	}
	return i < persona->tope;
}

int cantidadPerrosTPersona(TPersona persona){
	return persona->tope; 
}

TPersona copiarTPersona(TPersona persona){
	if (persona == NULL) return NULL;

	TPersona copia = new rep_persona;
	copia->id = ciTPersona(persona);
	strcpy(copia->nombre, nombreTPersona(persona));
	strcpy(copia->apellido, apellidoTPersona(persona));
	copia->edad = copiarTFecha(persona->edad);  

	copia->tope = 0;
	for (int i = 0; i < persona->tope; i++) {
		if (persona->adoptados[i] != NULL) {
			copia->adoptados[i] = copiarTPerro(persona->adoptados[i]);
			copia->tope++;
		} else {
			copia->adoptados[i] = NULL;
		}
	}

	return copia;
}
