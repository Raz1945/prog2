/*
    compilar el programa
        g++ -o programa main.cpp src/PP_SETIEMBRE024.cpp -I./include

*/


#include "./include/PP_SETIEMBRE024.h"
#include <iostream>

// Función principal
int main() {
    // Ejemplo para la función comune
    Lista l1 = new nodoLista{1, new nodoLista{3, new nodoLista{4, new nodoLista{8, new nodoLista{9, NULL}}}}};
    Lista l2 = new nodoLista{2, new nodoLista{3, new nodoLista{4, new nodoLista{6, new nodoLista{9, NULL}}}}};

    std::cout << "Elementos comunes en las listas: ";
    Lista comunesResult = comune(l1, l2);
    imprimirLista(comunesResult); // Debe imprimir: 3 4 9

    // Ejemplo para la función licenciar
    ABB arbol = new nodoABB{8, 1000, new nodoABB{3, 500, new nodoABB{1, 300, NULL, NULL}, new nodoABB{6, 700, new nodoABB{4, 400, NULL, NULL}, new nodoABB{7, 600, NULL, NULL}}}, new nodoABB{10, 900, NULL, new nodoABB{14, 800, NULL, NULL}}};

    std::cout << "Salarios antes de licenciar:" << std::endl;
    imprimirABB(arbol);
    licenciar(arbol, 6);
    std::cout << "Salarios después de licenciar (código menor a 6):" << std::endl;
    imprimirABB(arbol);

    // Ejemplo para la función conAumento
    ABB arbolAumentado = conAumento(arbol, 600, 100);
    std::cout << "Salarios después de aplicar aumento (piso 600, aumento 100):" << std::endl;
    imprimirABB(arbolAumentado);

    return 0;
}
