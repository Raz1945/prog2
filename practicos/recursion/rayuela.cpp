#include <stdio.h>

int caminos(int n) {
    // Caso base
    if ((n == 0) || (n == 1))
     return 1;
    else // Llamada recursiva
        return caminos(n-1) + caminos(n-2);
}

int main() {
    int n;
    printf("Ingresa el número de adoquín objetivo: ");
    scanf("%d", &n);

    int resultado = caminos(n);
    printf("El número de caminos posibles para llegar al adoquín %d es: %d\n", n, resultado);

    return 0;
}
