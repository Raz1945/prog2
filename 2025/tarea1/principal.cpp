/*
  Módulo principal de la Tarea 1.

Intérprete de comandos para probar los módulos implementados.

Cada comando tiene un nombre y una secuencia (posiblemente vacía) de parámetros.
Se asume que los comandos están bien formados. Esto implica que:
- el nombre es uno de los descritos más abajo;
- la cantidad y tipo de los parámetros cumplen con lo requerido.

El comando 'Fin' termina el programa

El comando '# comentario' imprime comentario.

  Laboratorio de Programación 2.
  InCo-FIng-UDELAR
*/

#define cmd_es(nom_comando, cmd) (0 == strcmp(nom_comando, cmd))

#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "include/refugio.h"

#define MAX_PALABRA 32
#define MAX_LINEA 256

// Lee una fecha de la entrada en formato "dd/mm/aaaa" y la escribe la variable fecha
void leerFecha(TFecha &fecha);

/* La implementación de las funciones de testeo se realiza al final del archivo*/
// Funciones para testear fecha
void main_crearFecha(TFecha &fecha); 
void main_liberarFecha(TFecha &fecha);
void main_imprimirFecha(TFecha fecha);
void main_copiarFecha(TFecha fecha);
void main_aumentarDias(TFecha &fecha);
void main_compararFechas(); 
// Funciones para testear perro
void main_crearPerro(TPerro &perro, TFecha &fecha);
void main_liberarPerro(TPerro &perro); 
void main_imprimirIdPerro(TPerro perro);
void main_imprimirNombrePerro(TPerro perro); 
void main_imprimirEdadPerro(TPerro perro); 
void main_imprimirDescripcionPerro(TPerro perro); 
void main_imprimirFechaIngresoPerro(TPerro perro); 
void main_imprimirVitalidadPerro(TPerro perro); 
void main_imprimirPerro(TPerro perro); 
void main_copiarPerro(TPerro perro);
void main_actualizarEdadPerro(TPerro &perro); 
void main_actualizarVitalidadPerro(TPerro &perro); 
// Funciones para testear refugio
void main_crearRefugio(TRefugio &refugio); 
void main_liberarRefugio(TRefugio refugio);
void main_agregarEnRefugio(TRefugio &refugio, TPerro &perro); 
void main_imprimirRefugio(TRefugio refugio); 
void main_estaEnRefugio(TRefugio refugio);
void main_obtenerDeRefugio(TRefugio refugio);
void main_ingresaronPerrosFechaRefugio(TRefugio refugio);
void main_imprimirPerrosFechaRefugio(TRefugio refugio); 
void main_removerDeRefugio(TRefugio &refugio);

// programa principal que lee comandos de la entrada estándar e invoca a la función de test correspondiente
int main() {
    TFecha fecha = NULL;
    TPerro perro = NULL;
    TRefugio refugio = NULL;

    char restoLinea[MAX_LINEA + 1];
    char cmd[MAX_PALABRA];

    int cont_comandos = 0;
    bool seguir = true;
    while (seguir) {
        // mostrar el prompt
        cont_comandos++;
        printf("%u>", cont_comandos);

        // leer el comando en la variable cmd
        leerChars(cmd);

        // procesar el comando
        if (cmd_es("Fin", cmd)) {  // Termina el programa
            seguir = false;
            printf("Fin.\n");

        } else if (cmd_es("#", cmd)) {  // Imprime el comentario luego del #
            leerRestoLinea(restoLinea);
            printf("# %s.\n", restoLinea);

            ///////////////////////////////////
            /* Funciones para testear fecha */
            ///////////////////////////////////

        } else if (cmd_es("crearFecha", cmd)) {  // Crea una fecha y la almacena en la variable fecha
            main_crearFecha(fecha);

        } else if (cmd_es("imprimirFecha", cmd)) {  // Imprime la fecha almacenada en la variable fecha
            main_imprimirFecha(fecha);

        } else if (cmd_es("copiarFecha", cmd)) { // Copia e imprime la fecha almacenada en la variable fecha 
            main_copiarFecha(fecha);

        } else if (cmd_es("liberarFecha", cmd)) {  // Libera la memoria de la variable fecha
            main_liberarFecha(fecha);

        } else if (cmd_es("aumentarDias", cmd)) {  // Aumenta la fecha almacenada en la variable fecha en la cantidad de días indicada
            main_aumentarDias(fecha);

        } else if (cmd_es("compararFechas", cmd)) {  // Compara dos fechas leidas de la entrada
            main_compararFechas();

            ///////////////////////////////////
            /* Funciones para testear perro */
            ///////////////////////////////////

        } else if (cmd_es("crearPerro", cmd)) {  // Crea un perro con los valores indicados y lo almacena en la variable perro
            main_crearPerro(perro, fecha);
        
        } else if (cmd_es("liberarPerro", cmd)) { // Libera la memoria de la variable perro
            main_liberarPerro(perro);

        } else if (cmd_es("imprimirIdPerro", cmd)) {  // Imprime el id del perro almacenado en la variable perro
            main_imprimirIdPerro(perro);

        } else if (cmd_es("imprimirNombrePerro", cmd)) { // Imprime el nombre del perro almacenado en la variable perro
            main_imprimirNombrePerro(perro); 

        } else if (cmd_es("imprimirEdadPerro", cmd)) { // Imprime la edad del perro almacenada en la variable perro
            main_imprimirEdadPerro(perro); 

        } else if (cmd_es("imprimirDescripcionPerro", cmd)) { // Imprime la descrpción del perro almacenada en la variable perro
            main_imprimirDescripcionPerro(perro);

        } else if (cmd_es("imprimirFechaIngresoPerro", cmd)) { // Imprime la fecha de ingreso al refugio del perro almacenada en la variable perro
            main_imprimirFechaIngresoPerro(perro); 

        } else if (cmd_es("imprimirVitalidadPerro", cmd)) { // Imprime el nivel de vitalidad del perro almacenado en la variable perro
            main_imprimirVitalidadPerro(perro); 

        } else if (cmd_es("imprimirPerro", cmd)) { // Imprime los datos del perro almacenados en la variable perro
            main_imprimirPerro(perro); 

        } else if (cmd_es("copiarPerro", cmd)) { // Copia e imprime el perro almacenado en la variable perro
            main_copiarPerro(perro); 
            
        } else if (cmd_es("actualizarEdadPerro", cmd)) { // Actualiza la edad del perro almacenada en la variable perro por la edad indicada
            main_actualizarEdadPerro(perro);
 
        } else if (cmd_es("actualizarVitalidadPerro", cmd)) { // Actualiza la vitalidad del perro almacenada en la variable perro por la vitalidad indicada
            main_actualizarVitalidadPerro(perro);

        //     ///////////////////////////////////
        //     /* Funciones para testear refugio */
        //     ///////////////////////////////////

        } else if (cmd_es("crearRefugio", cmd)) {  // Crea una refugio y lo almacena en la variable refugio
            main_crearRefugio(refugio);

        } else if (cmd_es("liberarRefugio", cmd)) { // Libera la memoria de la variable refugio
            main_liberarRefugio(refugio); 

        } else if (cmd_es("agregarEnRefugio", cmd)) { // Agrega al perro almacenado en la variable perro al refugio almacenado en la variable refugio
            main_agregarEnRefugio(refugio, perro);

        } else if (cmd_es("imprimirRefugio", cmd)) { // Imprime los datos de los perros del refugio almacenados en la variable refugio
            main_imprimirRefugio(refugio); 

        } else if (cmd_es("estaEnRefugio", cmd)) { // Indica si el perro con el id indicado está en el refugio almacenado en la variable refugio
            main_estaEnRefugio(refugio); 

        } else if (cmd_es("obtenerDeRefugio", cmd)) {
            main_obtenerDeRefugio(refugio); 
            
        } else if (cmd_es("ingresaronPerrosFechaRefugio", cmd)) {// Indica si ingresaron perros al refugio en una fecha indicada
            main_ingresaronPerrosFechaRefugio(refugio); 

        } else if (cmd_es("imprimirPerrosFechaRefugio", cmd)) { // Imprime todos los perros del refugio que ingresaron en la fecha indicada
            main_imprimirPerrosFechaRefugio(refugio); 

        } else if (cmd_es("removerDeRefugio", cmd)) { // Remueve el perro con el id indicado del refugio almacenado en la variable refugio 
            main_removerDeRefugio(refugio); 

        } else {
            printf("Comando no reconocido.\n");  // Comando no reconocido

        }  // if
        fgets(restoLinea, MAX_LINEA + 1, stdin);
    }  // while

    return 0;
}  // main

///////////////////////////////
/* Funciones main para Fecha */
///////////////////////////////

void leerFecha(TFecha &fecha) {
    nat *componentes = new nat[3];
    scanf("%u/%u/%u", &componentes[0], &componentes[1], &componentes[2]);
    fecha = crearTFecha(componentes[0], componentes[1], componentes[2]);
    delete[] componentes;
}

void main_crearFecha(TFecha &fecha) {
    assert(fecha == NULL);
    leerFecha(fecha);
} 

void main_liberarFecha(TFecha &fecha) {
    assert(fecha != NULL);
    liberarTFecha(fecha);
}

void main_imprimirFecha(TFecha fecha) {
    assert(fecha != NULL);
    imprimirTFecha(fecha);
}

void main_copiarFecha(TFecha fecha) {
    assert(fecha != NULL); 
    TFecha copia = copiarTFecha(fecha); 
    imprimirTFecha(copia); 
    liberarTFecha(copia);
}

void main_aumentarDias(TFecha &fecha) {
    assert(fecha != NULL);
    nat cantDias = leerNat();
    aumentarTFecha(fecha, cantDias);
    printf("La nueva fecha aplazada %d dias es: ", cantDias);
    imprimirTFecha(fecha);
}

void main_compararFechas() {
    TFecha fecha1 = NULL, fecha2 = NULL;
    leerFecha(fecha1);
    leerFecha(fecha2);
    int comp = compararTFechas(fecha1, fecha2);
    if (comp == 0) {
        printf("Las fechas son iguales. \n");
    } else if (comp == 1) {
        printf("La primera fecha es posterior a la segunda. \n");
    } else
        printf("La primera fecha es anterior a la segunda. \n");
    liberarTFecha(fecha1);
    liberarTFecha(fecha2);
}

/////////////////////////////////
/* Funciones main para Perros */
/////////////////////////////////

void main_crearPerro(TPerro &perro, TFecha &fecha) {
    assert((perro == NULL) && (fecha != NULL));
    int id = leerNat(); 
    char nombre[100]; 
    leerChars(nombre); 
    nat edad = leerNat(); 
    nat vitalidad = leerNat(); 
    char desc[100]; 
    leerRestoLinea(desc);
    perro = crearTPerro(id, nombre, edad, vitalidad, desc, fecha);
    fecha = NULL;
}

void main_liberarPerro(TPerro &perro) {
    assert(perro!=NULL); 
    liberarTPerro(perro); 
}

void main_imprimirIdPerro(TPerro perro) {
    assert(perro != NULL);
    printf("El id del perro es: %d\n", idTPerro(perro));
}

void main_imprimirNombrePerro(TPerro perro) {
    assert(perro != NULL);
    printf("El nombre del perro es: %s\n", nombreTPerro(perro));
}

void main_imprimirEdadPerro(TPerro perro) {
    assert(perro != NULL);
    printf("La edad del perro es: %d\n", edadTPerro(perro));
}
void main_imprimirDescripcionPerro(TPerro perro) {
    assert(perro != NULL);
    printf("La descripcion del perro es: %s\n", descripcionTPerro(perro));
}

void main_imprimirFechaIngresoPerro(TPerro perro) {
    assert(perro != NULL); 
    TFecha fechaIngreso = fechaIngresoTPerro(perro); 
    assert(fechaIngreso != NULL); 
    printf("La fecha de ingreso del perro es: ");
    imprimirTFecha(fechaIngreso);
}

void main_imprimirVitalidadPerro(TPerro perro) {
    assert(perro != NULL);
    printf("La vitalidad del perro es: %d\n", vitalidadTPerro(perro));   
}

void main_imprimirPerro(TPerro perro) {
    assert(perro != NULL); 
    imprimirTPerro(perro); 
} 

void main_copiarPerro(TPerro perro) {
    assert(perro != NULL); 
    TPerro copia = copiarTPerro(perro); 
    imprimirTPerro(copia); 
    liberarTPerro(copia);
}

void main_actualizarEdadPerro(TPerro &perro) {
    assert(perro!=NULL); 
    nat nuevaEdad = leerNat(); 
    actualizarEdadTPerro(perro, nuevaEdad); 
}

void main_actualizarVitalidadPerro(TPerro &perro) {
    assert(perro!=NULL); 
    nat nuevaVit = leerNat(); 
    actualizarVitalidadTPerro(perro, nuevaVit); 
}

////////////////////////////////
/* Funciones main para Refugio */
////////////////////////////////

void main_crearRefugio(TRefugio &refugio) {
    assert(refugio==NULL);
    refugio = crearTRefugio(); 
}

void main_liberarRefugio(TRefugio refugio) {
    assert(refugio != NULL); 
    liberarTRefugio(refugio); 
}

void main_agregarEnRefugio(TRefugio &refugio, TPerro &perro) {
    assert(refugio != NULL && perro != NULL); 
    agregarEnTRefugio(refugio, perro);
    perro = NULL; 
}

void main_imprimirRefugio(TRefugio refugio) {
    assert(refugio!=NULL); 
    imprimirTRefugio(refugio); 
}

void main_estaEnRefugio(TRefugio refugio) {
    assert(refugio!=NULL); 
    int id = leerNat(); 
    if(estaEnTRefugio(refugio, id)) 
        printf("El perro con id %d esta en el refugio.\n", id); 
    else 
        printf("El perro con id %d NO esta en el refugio.\n", id); 
}

void main_obtenerDeRefugio(TRefugio refugio) {
    assert(refugio!=NULL); 
    int id = leerNat(); 
    assert(estaEnTRefugio(refugio, id)); 
    imprimirTPerro(obtenerDeTRefugio(refugio, id));
}

void main_ingresaronPerrosFechaRefugio(TRefugio refugio) {
    assert(refugio != NULL);
    TFecha fecha = NULL;
    leerFecha(fecha);

    if (ingresaronPerrosFechaTRefugio(refugio, fecha))
        imprimirPerrosFechaTRefugio(refugio, fecha);
    else
        printf("No se encontraron perros ingresados en la fecha determinada.\n");

    liberarTFecha(fecha);
}

void main_imprimirPerrosFechaRefugio(TRefugio refugio) {
    assert(refugio != NULL);
    TFecha fecha = NULL;
    leerFecha(fecha);
    imprimirPerrosFechaTRefugio(refugio, fecha);
    liberarTFecha(fecha);
}

void main_removerDeRefugio(TRefugio &refugio) {
    assert(refugio!=NULL); 
    int id = leerNat(); 
    if(estaEnTRefugio(refugio, id)) {
        removerDeTRefugio(refugio, id); 
        printf("El perro con id %d se removió del refugio.\n", id);
    } else printf("El perro con id %d NO está en el refugio.\n", id);
}