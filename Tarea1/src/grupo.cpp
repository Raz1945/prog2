#include "../include/grupo.h"
#include "../include/persona.h"

struct rep_grupo {
    /************ Parte 5.1 ************/
    /*Escriba el código a continuación */
    TPersona grupo[MAX_PERSONAS];
    int tope;
    /****** Fin de parte Parte 5.1 *****/
};


TGrupo crearTGrupo(){
    TGrupo grupo = NULL;
    /************ Parte 5.2 ************/
    /*Escriba el código a continuación */
    grupo = new rep_grupo; 
    grupo->tope = 0; 
    /****** Fin de parte Parte 5.2 *****/
    return grupo;
}

// Función para agregar una persona a un grupo
// Recibe un elemento de tipo TGrupo y un elemento de tipo TPersona y lo agrega al grupo en orden por fecha de nacimiento (de menor a mayor)
// Si dos personas tienen la misma fecha de nacimiento, deben ordenarse por orden de ingreso al grupo, de más nuevo a más antiguo
// Si la cantidad de personas en el grupo es igual a MAX_PERSONAS, la función no tiene efecto
void agregarAGrupo(TGrupo& grupo, TPersona persona){
    /************ Parte 5.2 ************/
    /*Escriba el código a continuación */
    if (grupo->tope < MAX_PERSONAS) {
        int i = grupo->tope - 1; // Comienza desde el ultimo elemento
        
        while (i >= 0 && (!esMasJoven(persona, grupo->grupo[i]) || compararTFechas(fechaNacimientoTPersona(persona), fechaNacimientoTPersona(grupo->grupo[i])) == 0)) {
            grupo->grupo[i + 1] = grupo->grupo[i]; 
            i--;
        };

    // Inserta la nueva persona en la posicion correspondiente
    grupo->grupo[i + 1] = persona;
    grupo->tope++;
    }
    /****** Fin de parte Parte 5.2 *****/
}

// Función para imprimir todas las personas de un grupo
// Recibe un elemento de tipo TGrupo e imprime sus personas en orden cronológico
// El formato en el que se debe imprimir el grupo es utilizando de forma secuencial la función imprimirTPersona
// Si el grupo está vacío no imprime nada
void imprimirTGrupo(TGrupo grupo){
    /************ Parte 5.2 ************/
    /*Escriba el código a continuación */
    if (grupo->tope > 0) { 
        for (int i = 0; i < grupo->tope; i++) { 
            imprimirTPersona(grupo->grupo[i]); 
        }
    }
    /****** Fin de parte Parte 5.2 *****/
}

// Función para liberar un grupo
// Recibe una referencia a un elemento de tipo TGrupo y libera su memoria
// Libera además la memoria de cada una de las personas en el grupo
void liberarTGrupo(TGrupo& grupo){
   /************ Parte 5.2 ************/
    /*Escriba el código a continuación */
    if (grupo != NULL) {
        for (int i = 0; i < grupo->tope; i++) {
            liberarTPersona(grupo->grupo[i]); 
        };

        delete grupo;
        grupo = NULL;
    }
    /****** Fin de parte Parte 5.2 *****/
}

// Función para verificar si un elemento de tipo TPersona existe en un grupo
// Recibe un grupo y la cédula de la persona y regresa un booleano indicando su existencia
bool estaEnGrupo(TGrupo grupo, int cedula){
    bool esta = false;
	/************ Parte 5.3 ************/
    /*Escriba el código a continuación */
    int i = 0; 
    while (i < grupo->tope && !esta){
        if (cedulaTPersona(grupo->grupo[i]) == cedula){ 
            esta = true;
        };
        i++;        
    }
    /****** Fin de parte Parte 5.3 *****/
	return esta;
}

// Esta función remueve la persona con ci "cedula" del grupo "grupo"
void removerDeGrupo(TGrupo &grupo, int cedula){
    /************ Parte 5.4 ************/
    /*Escriba el código a continuación */
    int i = 0;
    while (i < grupo->tope && !(cedulaTPersona(grupo->grupo[i]) == cedula)){
        i++;
    }

    // Cuando sale del bucle, i correpondera a la posicion de la persona cuya cedula coincide con la buscada
    if (i < grupo->tope){
        // Removemos la persona del grupo
        liberarTPersona(grupo->grupo[i]); 

        // Reacomodamos el grupo para llenar el espacio dejado por la persona eliminada
        for (int j = i; j < grupo->tope - 1; j++){
            grupo->grupo[j] = grupo->grupo[j + 1];
        }

        grupo->tope--;
    }
    /****** Fin de parte Parte 5.4 *****/   
}

// Función para verificar si hay, al menos, una persona en el grupo que tenga la fecha de nacimiento "fecha"
// Debe implementarse utilizando búsqueda binaria
bool hayPersonasFecha(TGrupo grupo, TFecha fecha){
    bool hay = false;
    /************ Parte 5.5 ************/
    /*Escriba el código a continuación */
    int min = 0;
    int max = grupo->tope - 1;

    while (min <= max && !hay) {
        int pm = min + (max - min) / 2; // Punto Medio

        int comparacion = compararTFechas(fechaNacimientoTPersona(grupo->grupo[pm]), fecha);

        if (comparacion == 0) {
            hay = true; 
        } else if (comparacion == 1) {
            max = pm - 1; // Busca en la mitad inferior
        } else {
            min = pm + 1; // Busca en la mitad superior
        }
    }
    /****** Fin de parte Parte 5.5 *****/ 
    return hay;
}

// Imprime en pantalla las personas del grupo que tengan la fecha de nacimiento "fecha" 
void imprimirPersonasFecha(TGrupo grupo, TFecha fecha){
    /************ Parte 5.5 ************/
    /*Escriba el código a continuación */
    for (int i = 0; i < grupo->tope; i++){
        if (compararTFechas(fechaNacimientoTPersona(grupo->grupo[i]), fecha) == 0){
            imprimirTPersona(grupo->grupo[i]);
        };
    }
    /****** Fin de parte Parte 5.5 *****/ 
}
