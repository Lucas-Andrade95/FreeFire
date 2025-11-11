#include <stdio.h>
#include <stdlib.h>

int main() {

//ALOCANDO A MEMÓRIA DINÂMICA
int* numeros = (int*) malloc(3 * sizeof(int));
if (numeros == NULL) {
    printf("Falha na alocação de memória\n");
    return 1;
}

numeros[0] = 10;
numeros[1] = 21;
numeros[2] = 29;

printf("%d", numeros[2]);

numeros = (int*) realloc(numeros, 5 * sizeof(int));
numeros[4] = 17;
printf("%d", numeros[4]);

free(numeros);
return 0;

}

