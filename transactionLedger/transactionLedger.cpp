#include <stdio.h>
#include <stdbool.h>
#include <string.h>

int calculateMinProcessingSteps(char* transactionLedger) {
    int steps = 0;  // Contador de pasos
    int len = strlen(transactionLedger);  // Longitud de la cadena
    bool canBeReduced;  // Bandera para saber si la cadena se puede reducir

    do {
        canBeReduced = false;  // Inicialmente, asumimos que no se puede reducir

        // Recorremos la cadena de izquierda a derecha
        for (int i = 0; i < len; i++) {
            char currentChar = transactionLedger[i];  // Carácter actual
            int left = -1, right = -1;  // Posiciones de las coincidencias

            // Buscar la primera ocurrencia a la izquierda
            for (int j = i - 1; j >= 0; j--) {
                if (transactionLedger[j] == currentChar) {
                    left = j;
                    break;
                }
            }

            // Buscar la primera ocurrencia a la derecha
            for (int j = i + 1; j < len; j++) {
                if (transactionLedger[j] == currentChar) {
                    right = j;
                    break;
                }
            }

            // Si se encontraron coincidencias a la izquierda y a la derecha, eliminarlas
            if (left != -1 && right != -1) {
                // Eliminar la ocurrencia a la izquierda
                for (int k = left; k < len - 1; k++) {
                    transactionLedger[k] = transactionLedger[k + 1];
                }
                len--;

                // Ajustar el índice 'right' porque la cadena se ha desplazado
                right--;

                // Eliminar la ocurrencia a la derecha
                for (int k = right; k < len - 1; k++) {
                    transactionLedger[k] = transactionLedger[k + 1];
                }
                len--;

                steps++;  // Incrementar el contador de pasos
                canBeReduced = true;  // La cadena se ha reducido
                i = -1;  // Reiniciar la búsqueda desde el principio
                break;
            }
        }
    } while (canBeReduced);  // Repetir mientras la cadena se pueda reducir

    return steps;  // Devolver el número de pasos
}

int main() {
    char ledger[] = "baabacaa";
    int steps = calculateMinProcessingSteps(ledger);
    printf("Minimum processing steps: %d\n", steps);
    return 0;
}