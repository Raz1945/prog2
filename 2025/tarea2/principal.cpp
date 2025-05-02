/*
  Módulo principal de la Tarea 2.

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

#include "include/lseAdopciones.h"
#include "include/ldePerros.h"
#include "include/abbPersonas.h"

#define MAX_PALABRA 32
#define MAX_LINEA 256

///////////////////////////////
// Funciones main para Fecha //
///////////////////////////////

void leerFecha(TFecha &fecha); // Lee una fecha de la entrada en formato "dd/mm/aaaa" y la escribe la variable fecha
void main_crearFecha(TFecha &fecha); // Crea una fecha y la almacena en la variable fecha
void main_liberarFecha(TFecha &fecha); // Libera la memoria de la variable fecha
void main_imprimirFecha(TFecha fecha); // Imprime la fecha almacenada en la variable fecha
void main_copiarFecha(TFecha fecha);
void main_aumentarDias(TFecha &fecha); // Aumenta la fecha almacenada en la variable fecha en la cantidad de días indicada
void main_compararFechas(); // Compara dos fechas leidas de la entrada

////////////////////////////////////
// Funciones main para Personas  //
////////////////////////////////////
void main_crearPersona(TPersona &persona); // Crea una persona y la almacena en la variable 'persona'
void main_imprimirCIPersona(TPersona persona); // Imprime la CI de la persona almacenada en la variable 'persona'
void main_imprimirNombreYApellidoPersona(TPersona persona); // Imprime el nombre y apelldio de la persona almacenada en la variable 'persona'
void main_imprimirPersona(TPersona persona); // Imprime la persona almacenada en la variable 'persona'
void main_imprimirFechaNacimientoPersona(TPersona persona); // Imprime la fecha de nacimiento de la persona almacenada en la variable 'persona'
void main_copiarPersona(TPersona persona); // Prueba de la función copia
void main_liberarPersona(TPersona &persona); // Libera la memoria asociada a la persona guardada en la variable 'persona'
void main_agregarPerroPersona(TPersona persona, TPerro &perro); 
void main_pertenecePerroPersona(TPersona persona);
void main_cantidadPerrosPersona(TPersona persona);

////////////////////////////////////
//   Funciones main testear Perro //
////////////////////////////////////
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

//////////////////////////////////////////////
//   Funciones main para LSE Adopciones     //
//////////////////////////////////////////////
void main_crearLSEAdopcionesVacia(TLSEAdopciones &listaAdopciones);
void main_insertarLSEAdopciones(TLSEAdopciones &listaAdopciones, TFecha &fecha, TPersona &persona, TPerro &perro);
void main_imprimirLSEAdopciones(TLSEAdopciones listaAdopciones);
void main_liberarLSEAdopciones(TLSEAdopciones &listaAdopciones);
void main_esVaciaLSEAdopciones(TLSEAdopciones listaAdopciones);
void main_existeAdopcionLSEAdopciones(TLSEAdopciones listaAdopciones);
void main_removerAdopcionLSEAdopciones(TLSEAdopciones &listaAdopciones);

//////////////////////////////////////////
//    Funciones main para LDEPerros     //
//////////////////////////////////////////
void main_crearLDEPerrosVacia(TLDEPerros &ldePerros);
void main_insertarLDEPerros(TLDEPerros &ldePerros, TPerro &perro);
void main_imprimirLDEPerros(TLDEPerros ldePerros);
void main_imprimirInvertidoLDEPerros(TLDEPerros ldePerros);
void main_cantidadLDEPerros(TLDEPerros ldePerros);
void main_obtenerPrimeroLDEPerros(TLDEPerros ldePerros);
void main_obtenerUltimoLDEPerros(TLDEPerros ldePerros);
void main_obtenerNesimoLDEPerros(TLDEPerros ldePerros);
void main_existePerroLDEPerros(TLDEPerros ldePerros);
void main_removerPerroLDEPerros(TLDEPerros ldePerros);
void main_liberarLDEPerros(TLDEPerros &ldePerros);

//////////////////////////////////////
// Funciones main para ABB Personas //
//////////////////////////////////////

void main_crearABBPersonasVacio(TABBPersonas &abbPersonas); 
void main_insertarPersonaABBPersonas(TABBPersonas &abbPersonas, TPersona &persona);
void main_imprimirABBPersonas(TABBPersonas abbPersonas); 
void main_existePersonaABBPersonas(TABBPersonas abbPersonas);
void main_obtenerPersonaABBPersonas(TABBPersonas abbPersonas);
void main_alturaABBPersonas(TABBPersonas abbPersonas);
void main_maxCIPersonaABBPersonas(TABBPersonas abbPersonas);
void main_cantidadABBPersonas(TABBPersonas abbPersonas);
void main_obtenerNesimaPersonaABBPersonas(TABBPersonas gruabbPersonaspo);
void main_removerPersonaABBPersonas(TABBPersonas &abbPersonas);
void main_liberarABBPersonas(TABBPersonas &abbPersonas);
void main_filtradoPorFechaDeNacimientoABBPersonas(TABBPersonas abbPersonas);
void main_alturaABBPersonasTiempo();
void main_obtenerExistePersonaABBPersonasTiempo();


// programa principal que lee comandos de la entrada estándar e invoca a la función de test correspondiente
int main() {
    TFecha fecha = NULL;
    TPersona persona = NULL;
    TPerro perro = NULL;

    TABBPersonas abbPersonas = NULL;
    TLSEAdopciones listaAdopciones = NULL;
    TLDEPerros ldePerros = NULL;

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

        } else if (cmd_es("crearFecha", cmd)) {  
            main_crearFecha(fecha);
        } else if (cmd_es("imprimirFecha", cmd)) {  
            main_imprimirFecha(fecha);
        } else if (cmd_es("copiarFecha", cmd)) { // Copia e imprime la fecha almacenada en la variable fecha 
            main_copiarFecha(fecha);
        } else if (cmd_es("liberarFecha", cmd)) {  
            main_liberarFecha(fecha);
        } else if (cmd_es("aumentarDias", cmd)) {  
            main_aumentarDias(fecha);
        } else if (cmd_es("compararFechas", cmd)) {  
            main_compararFechas();

        } else if (cmd_es("crearPerro", cmd)) {  
            main_crearPerro(perro, fecha);
        } else if (cmd_es("liberarPerro", cmd)) { 
            main_liberarPerro(perro);
        } else if (cmd_es("imprimirIdPerro", cmd)) { 
            main_imprimirIdPerro(perro);
        } else if (cmd_es("imprimirNombrePerro", cmd)) {
            main_imprimirNombrePerro(perro); 
        } else if (cmd_es("imprimirEdadPerro", cmd)) { 
            main_imprimirEdadPerro(perro); 
        } else if (cmd_es("imprimirDescripcionPerro", cmd)) {
            main_imprimirDescripcionPerro(perro);
        } else if (cmd_es("imprimirFechaIngresoPerro", cmd)) {
            main_imprimirFechaIngresoPerro(perro); 
        } else if (cmd_es("imprimirVitalidadPerro", cmd)) {
            main_imprimirVitalidadPerro(perro); 
        } else if (cmd_es("imprimirPerro", cmd)) { 
            main_imprimirPerro(perro); 
        } else if (cmd_es("copiarPerro", cmd)) { // Copia e imprime el perro almacenado en la variable perro
            main_copiarPerro(perro); 
        } else if (cmd_es("actualizarEdadPerro", cmd)) { 
            main_actualizarEdadPerro(perro);
        } else if (cmd_es("actualizarVitalidadPerro", cmd)) { 
            main_actualizarVitalidadPerro(perro);

            //////////////////////////////////////
            /* Funciones para testear persona */
            //////////////////////////////////////

        } else if (cmd_es("crearPersona", cmd)) {  
            main_crearPersona(persona);
        } else if (cmd_es("imprimirCIPersona",cmd)){
            main_imprimirCIPersona(persona);
        } else if (cmd_es("imprimirNombreYApellidoPersona", cmd)){     
            main_imprimirNombreYApellidoPersona(persona);
        } else if (cmd_es("imprimirFechaNacimientoPersona", cmd)){     
            main_imprimirFechaNacimientoPersona(persona);
        } else if (cmd_es("imprimirPersona", cmd)) { 
            main_imprimirPersona(persona);
        } else if (cmd_es("copiarPersona",cmd)){
            main_copiarPersona(persona);
        } else if (cmd_es("agregarPerroPersona", cmd)){     
            main_agregarPerroPersona(persona, perro);
        } else if (cmd_es("pertenecePerroPersona", cmd)) { 
            main_pertenecePerroPersona(persona);
        } else if (cmd_es("cantidadPerrosPersona",cmd)){
            main_cantidadPerrosPersona(persona);
        } else if (cmd_es("liberarPersona", cmd)) {  
            main_liberarPersona(persona);        
          
            
            //////////////////////////////////////////////
            //   Funciones main para LSE Adopciones     //
            //////////////////////////////////////////////
        } else if (cmd_es("crearLSEAdopcionesVacia", cmd)) {  
            main_crearLSEAdopcionesVacia(listaAdopciones);
        } else if (cmd_es("insertarLSEAdopciones", cmd)) {  
            main_insertarLSEAdopciones(listaAdopciones, fecha, persona, perro);
        } else if (cmd_es("imprimirLSEAdopciones", cmd)) {  
            main_imprimirLSEAdopciones(listaAdopciones);
        } else if (cmd_es("liberarLSEAdopciones", cmd)) {  
            main_liberarLSEAdopciones(listaAdopciones);
        } else if (cmd_es("esVaciaLSEAdopciones", cmd)) {  
            main_esVaciaLSEAdopciones(listaAdopciones);
        } else if (cmd_es("existeAdopcionLSEAdopciones", cmd)){ 
            main_existeAdopcionLSEAdopciones(listaAdopciones);
        } else if (cmd_es("removerAdopcionLSEAdopciones", cmd)) {  
            main_removerAdopcionLSEAdopciones(listaAdopciones);


            /////////////////////////////////////////
            // Funciones para testear abb personas //
            /////////////////////////////////////////
        } else if (cmd_es("crearABBPersonasVacio", cmd)) {  
            main_crearABBPersonasVacio(abbPersonas);
        } else if (cmd_es("insertarPersonaABBPersonas", cmd)) {  
            main_insertarPersonaABBPersonas(abbPersonas, persona);
        } else if (cmd_es("imprimirABBPersonas", cmd)) { 
            main_imprimirABBPersonas(abbPersonas);
        } else if (cmd_es("existePersonaABBPersonas", cmd)) { 
            main_existePersonaABBPersonas(abbPersonas);
        } else if (cmd_es("obtenerPersonaABBPersonas", cmd)) { 
            main_obtenerPersonaABBPersonas(abbPersonas);
        } else if (cmd_es("alturaABBPersonas", cmd)) { 
            main_alturaABBPersonas(abbPersonas);
        } else if (cmd_es("maxCIPersonaABBPersonas", cmd)) { 
            main_maxCIPersonaABBPersonas(abbPersonas);
        } else if (cmd_es("cantidadABBPersonas", cmd)) { 
            main_cantidadABBPersonas(abbPersonas);
        } else if (cmd_es("obtenerNesimaPersonaABBPersonas", cmd)) { 
            main_obtenerNesimaPersonaABBPersonas(abbPersonas);
        } else if (cmd_es("removerPersonaABBPersonas", cmd)) { 
            main_removerPersonaABBPersonas(abbPersonas);
        } else if (cmd_es("liberarABBPersonas", cmd)) { 
            main_liberarABBPersonas(abbPersonas);
        } else if (cmd_es("filtradoPorFechaDeNacimientoABBPersonas", cmd)) { 
            main_filtradoPorFechaDeNacimientoABBPersonas(abbPersonas);
        } else if (cmd_es("alturaABBPersonasTiempo", cmd)) { 
            main_alturaABBPersonasTiempo();
        } else if (cmd_es("obtenerExistePersonaABBPersonasTiempo", cmd)) { 
            main_obtenerExistePersonaABBPersonasTiempo();



            //////////////////////////////////////////////
            // Funciones para testear LDE Perros  //
            //////////////////////////////////////////////
        } else if (cmd_es("crearLDEPerrosVacia", cmd)) { 
            main_crearLDEPerrosVacia(ldePerros);
        } else if (cmd_es("insertarLDEPerros", cmd)) { 
            main_insertarLDEPerros(ldePerros, perro);
        } else if (cmd_es("imprimirLDEPerros", cmd)) { 
            main_imprimirLDEPerros(ldePerros);
        } else if (cmd_es("imprimirInvertidoLDEPerros", cmd)) { 
            main_imprimirInvertidoLDEPerros(ldePerros);
        } else if (cmd_es("cantidadLDEPerros", cmd)) { 
            main_cantidadLDEPerros(ldePerros);
        } else if (cmd_es("obtenerPrimeroLDEPerros", cmd)) { 
            main_obtenerPrimeroLDEPerros(ldePerros);
        } else if (cmd_es("obtenerUltimoLDEPerros", cmd)) { 
            main_obtenerUltimoLDEPerros(ldePerros);
        } else if (cmd_es("obtenerNesimoLDEPerros", cmd)) { 
            main_obtenerNesimoLDEPerros(ldePerros);
        } else if (cmd_es("existePerroLDEPerros", cmd)) { 
            main_existePerroLDEPerros(ldePerros);
        } else if (cmd_es("removerPerroLDEPerros", cmd)) { 
            main_removerPerroLDEPerros(ldePerros);
        } else if (cmd_es("liberarLDEPerros", cmd)) { 
            main_liberarLDEPerros(ldePerros);
        } 

        
        
        else {
            printf("Comando no reconocido.\n");  // Comando no reconocido
        }  
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


///////////////////////////////////
//   Funciones main para Perros  //
///////////////////////////////////

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

///////////////////////////////////
/* Funciones main para Persona */
///////////////////////////////////

void main_crearPersona(TPersona &persona){
    assert(persona == NULL);
    int ci = leerInt();
    char nombre[MAX_NOMBRE_PERSONA];
    leerChars(nombre);
    char apellido[MAX_APELLIDO_PERSONA];
    leerChars(apellido);
    nat dia = leerNat();
    nat mes = leerNat();
    nat anio = leerNat();

    persona = crearTPersona(ci, nombre, apellido, dia, mes, anio);
}

void main_imprimirCIPersona(TPersona persona) {
    assert(persona != NULL);
    printf("La CI de la persona es: %d\n", ciTPersona(persona));
}

void main_imprimirNombreYApellidoPersona(TPersona persona){
    assert(persona != NULL);
    printf("El nombre de la persona es: %s\n", nombreTPersona(persona));
    printf("El apellido de la persona es: %s\n", apellidoTPersona(persona));
}

void main_imprimirFechaNacimientoPersona(TPersona persona){
    assert(persona != NULL);
    TFecha fecha = fechaNacimientoTPersona(persona);
    printf("La fecha de nacimiento de la persona es: ");
    imprimirTFecha(fecha);
}

void main_imprimirPersona(TPersona persona) {
    assert(persona != NULL);
    imprimirTPersona(persona);
}

void main_copiarPersona(TPersona persona){
    TPersona personaCopia = copiarTPersona(persona);
    printf("Persona copiada. Datos de la copia:\n");
    imprimirTPersona(personaCopia);

    liberarTPersona(personaCopia);
    personaCopia = NULL;
}

void main_agregarPerroPersona(TPersona persona, TPerro &perro){
    assert(persona != NULL);
    assert(perro != NULL);
    agregarPerroTPersona(persona, perro);
}

void main_pertenecePerroPersona(TPersona persona){
    assert(persona != NULL);
    int id = leerInt();
    bool existe = pertenecePerroTPersona(persona, id);
    if (existe){
        printf("El perro con id %d pertenece a la persona.\n", id);
    } else {
        printf("El perro con id %d NO pertenece a la persona.\n", id);
    }
}
            
void main_cantidadPerrosPersona(TPersona persona){
    assert(persona != NULL);
    int cant = cantidadPerrosTPersona(persona);
    printf("La persona tiene %d perro/s.\n", cant);    
}

void main_liberarPersona(TPersona &persona) {
    assert(persona != NULL);
    liberarTPersona(persona);
}


//////////////////////////////////////////////
//    Funciones main para LSE Adopciones    //
//////////////////////////////////////////////

void main_crearLSEAdopcionesVacia(TLSEAdopciones &listaAdopciones){
    assert(listaAdopciones == NULL);
    listaAdopciones = crearTLSEAdopcionesVacia();
}

void main_insertarLSEAdopciones(TLSEAdopciones &listaAdopciones, TFecha &fecha, TPersona &persona, TPerro &perro){
    insertarTLSEAdopciones(listaAdopciones, fecha, persona, perro);
    printf("Adopcion de persona de CI %d y perro de id %d agregada de forma exitosa.\n", ciTPersona(persona), idTPerro(perro));
    fecha = NULL;
    persona = NULL;
    perro = NULL;
}

void main_imprimirLSEAdopciones(TLSEAdopciones listaAdopciones){
    printf("Lista de adopciones:\n");
    imprimirTLSEAdopciones(listaAdopciones);
    printf("Fin lista de adopciones.\n");
}

void main_liberarLSEAdopciones(TLSEAdopciones &listaAdopciones){
    liberarTLSEAdopciones(listaAdopciones);
}

void main_esVaciaLSEAdopciones(TLSEAdopciones listaAdopciones){
    bool esVacia = esVaciaTLSEAdopciones(listaAdopciones);
    if (esVacia){
        printf("La lista de adopciones es vacia.\n");
    } else {
        printf("La lista de adopciones NO es vacia.\n");
    }
}

void main_existeAdopcionLSEAdopciones(TLSEAdopciones listaAdopciones){
    int ciPersona = leerInt();
    int idPerro = leerInt();
    bool existe = existeAdopcionTLSEAdopciones(listaAdopciones, ciPersona, idPerro);
    if (existe){
        printf("Existe una adopcion de la persona de CI %d al perro %d en la lista.\n", ciPersona, idPerro);
    } else {
        printf("NO Existe una adopcion de la persona de CI %d al perro %d en la lista.\n", ciPersona, idPerro);
    }
}

void main_removerAdopcionLSEAdopciones(TLSEAdopciones &listaAdopciones){
    int ciPersona = leerInt();
    int idPerro = leerInt();
    assert(existeAdopcionTLSEAdopciones(listaAdopciones, ciPersona, idPerro));
    removerAdopcionTLSEAdopciones(listaAdopciones, ciPersona, idPerro);
    printf("Adopcion de la persona de CI %d al perro %d removida de la lista.\n", ciPersona, idPerro);
}

/////////////////////////////////////
// Funciones main para ABB Persona //
/////////////////////////////////////

void main_crearABBPersonasVacio(TABBPersonas &abbPersonas){
    assert(abbPersonas == NULL);
    abbPersonas = crearTABBPersonasVacio();
}

void main_insertarPersonaABBPersonas(TABBPersonas &abbPersonas, TPersona &persona){
    assert(persona != NULL);
    insertarTPersonaTABBPersonas(abbPersonas, persona);
    persona = NULL;
}

void main_imprimirABBPersonas(TABBPersonas abbPersonas){
    imprimirTABBPersonas(abbPersonas);
}

void main_existePersonaABBPersonas(TABBPersonas abbPersonas){
    int id = leerInt();
    if (existeTPersonaTABBPersonas(abbPersonas, id)){
        printf("La persona con ci %d pertenece al arbol.\n", id);
    }else{
        printf("La persona con ci %d NO pertenece al arbol.\n", id);
    }
}

void main_obtenerPersonaABBPersonas(TABBPersonas abbPersonas){
    int id = leerInt();
    TPersona persona = obtenerTPersonaTABBPersonas(abbPersonas, id);
    if (persona == NULL){
        printf("La persona con CI %d no se puede imprimir pues NO pertenece al arbol.\n", id);
    }else{  
        imprimirTPersona(persona);
    }
}

void main_alturaABBPersonas(TABBPersonas abbPersonas){
    nat altura = alturaTABBPersonas(abbPersonas);
    printf("La altura del arbol es %d.\n", altura);
}

void main_maxCIPersonaABBPersonas(TABBPersonas abbPersonas){
    TPersona personaMaxCI = maxCITPersonaTABBPersonas(abbPersonas);
    printf("La mayor cedula en el arbol es %d.\n", ciTPersona(personaMaxCI));
}

void main_cantidadABBPersonas(TABBPersonas abbPersonas){
    int cantidad = cantidadTABBPersonas(abbPersonas);
    printf("La cantidad de personas en el arbol es %d.\n", cantidad);
}

void main_obtenerNesimaPersonaABBPersonas(TABBPersonas abbPersonas){
    int n = leerInt();
    int cantEnArbol = cantidadTABBPersonas(abbPersonas); 
    if (cantEnArbol >= n) {
        TPersona persona = obtenerNesimaPersonaTABBPersonas(abbPersonas, n);
        printf("Persona nro %d del abb personas:\n", n);
        imprimirTPersona(persona);
    } else {
        printf("No se puede imprimir la persona nro %d del arbol porque solo hay %d.\n", n, cantEnArbol);
    }
}

void main_removerPersonaABBPersonas(TABBPersonas &abbPersonas){
    int ci = leerInt();
    if (existeTPersonaTABBPersonas(abbPersonas, ci)) {
        removerTPersonaTABBPersonas(abbPersonas, ci);
        printf("La persona con id %d se removio del arbol.\n", ci);
    } else {
        printf("La persona con CI %d no se puede remover porque NO pertenece al arbol.\n", ci);
    }
}

void main_liberarABBPersonas(TABBPersonas &abbPersonas){
    liberarTABBPersonas(abbPersonas);
}

void main_filtradoPorFechaDeNacimientoABBPersonas(TABBPersonas abbPersonas){
    TFecha fechaFiltrado = NULL;
    leerFecha(fechaFiltrado);
    int criterio = leerInt();
    TABBPersonas filtrado = filtradoPorFechaDeNacimientoTABBPersonas(abbPersonas, fechaFiltrado, criterio);
    imprimirTABBPersonas(filtrado);
    liberarTABBPersonas(filtrado);
    liberarTFecha(fechaFiltrado);
}

void insertarEnArbolDesdeArreglo(TABBPersonas &abbPersonas, TPersona *arreglo, int inicio, int final){
    if (inicio <= final){
        int mid = (inicio + final) / 2;
        insertarTPersonaTABBPersonas(abbPersonas, arreglo[mid]);
        insertarEnArbolDesdeArreglo(abbPersonas, arreglo, inicio, mid - 1);
        insertarEnArbolDesdeArreglo(abbPersonas, arreglo, mid + 1, final);
    }
}

void main_alturaABBPersonasTiempo(){
    TABBPersonas abbPersonas = crearTABBPersonasVacio();

    nat tamanio = leerNat();
    nat timeout = leerNat();

    TPersona *arreglo = new TPersona[tamanio];
    for (nat i = 0; i < tamanio; i++) {
        arreglo[i] = crearTPersona(i, "Carlos", "Luna", 2, 5, 1960);
    }

    nat inicio = 0;
    nat final = tamanio - 1;
    insertarEnArbolDesdeArreglo(abbPersonas, arreglo, inicio, final);
    clock_t tm = clock();
    nat altura = alturaTABBPersonas(abbPersonas);
    tm = clock() - tm;

    float tiempo = ((float)tm) / CLOCKS_PER_SEC;
    if (tiempo > timeout){
        printf("ERROR, tiempo excedido; %.1f > %d \n", tiempo, timeout);
    }else{
        printf("La altura del arbol es %d. Calculado correctamente en menos de %ds.\n", altura, timeout);    
    }
    
    liberarTABBPersonas(abbPersonas);
    delete[] arreglo;
}

void main_obtenerExistePersonaABBPersonasTiempo(){
    TABBPersonas abbPersonas = crearTABBPersonasVacio();

    nat tamanio = leerNat();
    double timeout = leerDouble();

    TPersona *arreglo = new TPersona[tamanio];
    for (nat i = 0; i < tamanio; i++) {
        arreglo[i] = crearTPersona(i, "Carlos", "Luna",  2, 5, 1960);
    }

    nat inicio = 0;
    nat final = tamanio - 1;
    insertarEnArbolDesdeArreglo(abbPersonas, arreglo, inicio, final);
    clock_t tm = clock();
    bool existePersona1 = existeTPersonaTABBPersonas(abbPersonas, 0);
    bool existePersona2 = existeTPersonaTABBPersonas(abbPersonas, tamanio - 1);
    bool existePersona3 = existeTPersonaTABBPersonas(abbPersonas, tamanio / 3);
    bool existePersona4 = existeTPersonaTABBPersonas(abbPersonas, (2 * tamanio) / 3);
    TPersona persona1 = obtenerTPersonaTABBPersonas(abbPersonas, 0);
    TPersona persona2 = obtenerTPersonaTABBPersonas(abbPersonas, tamanio - 1);
    TPersona persona3 = obtenerTPersonaTABBPersonas(abbPersonas, tamanio / 3);
    TPersona persona4 = obtenerTPersonaTABBPersonas(abbPersonas, (2 * tamanio) / 3);
    tm = clock() - tm;

    float tiempo = ((float)tm) / CLOCKS_PER_SEC;
    if (tiempo > timeout){
        printf("ERROR, tiempo excedido: %.3f > %.3f \n", tiempo, timeout);
    }else{
        printf("Se obtuvieron las personas %d %d %d %d con cedulas respectivas %d %d %d %d\n", existePersona1, existePersona2, existePersona3, existePersona4, ciTPersona(persona1), ciTPersona(persona2), ciTPersona(persona3), ciTPersona(persona4));
        printf("Calculado correctamente en menos de %.3fs.\n", timeout);    
    }
    
    liberarTABBPersonas(abbPersonas);
    delete[] arreglo;
}

//////////////////////////////////////////
//   Funciones main para LDE Perros     //
//////////////////////////////////////////

void main_crearLDEPerrosVacia(TLDEPerros &ldePerros){
    assert(ldePerros == NULL);
    ldePerros = crearTLDEPerrosVacia();
}

void main_insertarLDEPerros(TLDEPerros &ldePerros, TPerro &perro){
    assert(perro != NULL);
    insertarTLDEPerros(ldePerros, perro);
    perro = NULL;
}

void main_imprimirLDEPerros(TLDEPerros ldePerros){
    imprimirTLDEPerros(ldePerros);
}

void main_imprimirInvertidoLDEPerros(TLDEPerros ldePerros){
    imprimirInvertidoTLDEPerros(ldePerros);
}

void main_cantidadLDEPerros(TLDEPerros ldePerros){
    nat cant = cantidadTLDEPerros(ldePerros);
    printf("La cantidad de perros en la lista es %d\n", cant);
}

void main_obtenerPrimeroLDEPerros(TLDEPerros ldePerros){
    nat cant = cantidadTLDEPerros(ldePerros);
    if (cant > 0){
        TPerro perro = obtenerPrimeroTLDEPerros(ldePerros);
        assert(perro != NULL);
        printf("Primer perro:\n");
        imprimirTPerro(perro);
    }else{
        printf("No se puede obtener el primero de la LDE de perros porque es vacia\n");
    }
}


void main_obtenerUltimoLDEPerros(TLDEPerros ldePerros){
    nat cant = cantidadTLDEPerros(ldePerros);
    if (cant > 0){
        TPerro perro = obtenerUltimoTLDEPerros(ldePerros);
        assert(perro != NULL);
        printf("Ultimo perro:\n");
        imprimirTPerro(perro);
    }else{
        printf("No se puede obtener el ultimo de la LDE de perros porque es vacia\n");
    }
}

void main_obtenerNesimoLDEPerros(TLDEPerros ldePerros){
    nat n = leerNat();
    assert(cantidadTLDEPerros(ldePerros) >= n);

    TPerro perro = obtenerNesimoTLDEPerros(ldePerros, n);
    assert(perro != NULL);

    printf("Perro en la posicion %d:\n", n);
    imprimirTPerro(perro);
}

void main_existePerroLDEPerros(TLDEPerros ldePerros){
    int id = leerInt();
    bool existe = existePerroTLDEPerros(ldePerros, id);
    if (existe){
        printf("El perro de id %d pertenece a la lista.\n", id);
    }else{
        printf("El perro de id %d NO pertenece a la lista.\n", id);
    }
}

void main_removerPerroLDEPerros(TLDEPerros ldePerros){
    nat id = leerNat();

    TPerro perro = removerPerroTLDEPerros(ldePerros, id);
    assert(perro != NULL);

    printf("Perro removido de la lista:\n");
    imprimirTPerro(perro);
    liberarTPerro(perro);
}

void main_liberarLDEPerros(TLDEPerros &ldePerros){
    assert(ldePerros != NULL);
    liberarTLDEPerros(ldePerros);
    ldePerros = NULL;
}
