#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAMANHO 10

//======DECLARAÇÃO DAS FUNÇÕES=========

//FUNÇÃO PARA GERAR LISTAS

void gerarListaOrdenada(int lista[], int n);
void gerarListaInversa(int lista[], int n);
void gerarListaAleatoria(int lista[], int n);

//FUNÇÕES DE ORDENAÇÃO

void bubbleSort(int lista[], int n);
void insertionSort(int lista[], int n);
void selectionSort(int lista[], int n);

//FUNÇÕES AUXILIARES
void imprimirLista(const char* titulo, const int lista[], int n);
void copiarLista(int destino[], const int origem[], int n);

//======FUNÇÃO PRINCIPAL (MAIN) =========

int main() {
    srand(time(NULL)); // Gera números aleatórios de acordo com o horário atual

    //Decalaração das listas
    int listaOrdenada[TAMANHO];
    int listaInversa[TAMANHO];
    int listaAleatoria[TAMANHO];

    //Preenche as listas com os padrões desejados
    printf("--- GERANDO LISTAS DE ENTRADA ---\n");
    gerarListaOrdenada(listaOrdenada, TAMANHO);
    gerarListaInversa(listaInversa, TAMANHO);
    gerarListaAleatoria(listaAleatoria, TAMANHO);
    printf("----------------------------------\n\n");

    //Declara uma lista temporária que será usada para receber uma cópia
    int listaTemp[TAMANHO];

    // ========BUBBLE SORT============
    printf("========== 1.BUBBLE SORT ===========\n");

    //LISTA JÁ ORDENADA
    copiarLista(listaTemp, listaOrdenada, TAMANHO);
    bubbleSort(listaTemp, TAMANHO);
    imprimirLista("Bubble Sort | Melhor caso (ja ordenada)", listaTemp, TAMANHO);

    //LISTA INVERSA
    copiarLista(listaTemp, listaInversa, TAMANHO);
    bubbleSort(listaTemp, TAMANHO);
    imprimirLista("Bubble Sort | Pior Caso (ordem inversa)", listaTemp, TAMANHO);

    //LISTA ALEATÓRIA
    copiarLista(listaTemp, listaAleatoria, TAMANHO);
    bubbleSort(listaTemp, TAMANHO);
    imprimirLista("Bubble Sort | Caso Medio (aleatoria)", listaTemp, TAMANHO);
    printf("\n");

    // =========INSERTION SORT ==========
    printf("========== 2. INSERTION SORT ==========\n");
    
    //LISTA ORDENADA
    copiarLista(listaTemp, listaOrdenada, TAMANHO);
    insertionSort(listaTemp, TAMANHO);
    imprimirLista("Insertion Sort | Melhor caso (ja ordenada)", listaTemp, TAMANHO);

    //LISTA INVERSA
    copiarLista(listaTemp, listaInversa, TAMANHO);
    insertionSort(listaTemp, TAMANHO);
    imprimirLista("Insertion Sort | Pior caso (ordem inversa)", listaTemp, TAMANHO);

    //LISTA ALEATÓRIA
    copiarLista(listaTemp, listaAleatoria, TAMANHO);
    insertionSort(listaTemp, TAMANHO);
    imprimirLista("Insertion Sort | Caso Medio (aleatoria)", listaTemp, TAMANHO);
    printf("\n");

    // ======== SELECTION SORT ===============
    printf("========== 3. SELECTION SORT ==========\n");

    //LISTA ORDENADA
    copiarLista(listaTemp, listaOrdenada, TAMANHO);
    selectionSort(listaTemp, TAMANHO);
    imprimirLista("Selection Sort | Melhor Caso (ja ordenada)", listaTemp, TAMANHO);

    //LISTA INVERSA
    copiarLista(listaTemp, listaInversa, TAMANHO);
    selectionSort(listaTemp, TAMANHO);
    imprimirLista("Selection Sort | Pior Caso (ordem inversa)", listaTemp, TAMANHO);

    //LISTA ALEATÓRIA
    copiarLista(listaTemp, listaAleatoria, TAMANHO);
    selectionSort(listaTemp, TAMANHO);
    imprimirLista("Selection Sort | Caso Medio (aleatoria)", listaTemp, TAMANHO);
    printf("\n");

    return 0;
}

// FUNÇÕES DE ORDENAÇÃO

void bubbleSort(int lista[], int n) {
    int i, j, temp;
    int trocou; 

    //Após cada passagem 'i', o i-ésimo elemento estará no lugar certo.
    for (i = 0; i < n - 1; i++) {
        trocou = 0; // Flag para saber se todos os elementos já estão ordenados (Não houve trocas)

        //Laço interno percorre a lista, comparando elementos vizinhos
        for (j = 0; j < n - i - 1; j++) {
            //Se o elemento atual for maior que o próximo...
            if (lista[j] > lista[j + 1]) { //trocamos eles de lugar.
                temp = lista[j];
                lista[j] = lista[j + 1];
                lista[j + 1] = temp;
                trocou = 1; //Marca que uma troca aconteceu
            }
        }

        if (trocou == 0) { //Se não houve trocas a lista está ordenada e... 
            break; //...podemos encerrar o loop para que não faça iterações desnecessariamente
        }
    }
}

void insertionSort(int lista[], int n) {
    int i, chave, j;

    //Iniciamos pelo segundo elemento, comparando com os outros à esquerda
    for (i = 1; i < n; i++) {
        chave = lista[i]; // 'chave' é o elemento atual que estamos comparando e queremos inserir na parte ordenada
        j = i - 1; //j aponta para o último elemento da "parte ordenada", ou seja à esquerda de i

        //Movemos os elementos maiores que 'chave' para a direita, se houver
        while (j >= 0 && lista[j] > chave) {
            lista[j + 1] = lista[j];
            j = j - 1;
        }

        //inserimos chave na posição correta
        lista[j + 1] = chave;
    }
}

void selectionSort(int lista[], int n) {
    int i, j, indice_min, temp;

    //Laço externo percorre a lista para definir a fronteira entre a parte ordenada e não ordenada
    for (i = 0; i < n - 1; i ++) {
        //Assume que o primeiro elemento da parte não ordenada é o menor.
        indice_min = i;

        //Laço interno percorre a parte não ordenada para encontrar o menor elemento de fato.
        for (j = i + 1; j < n; j++) {
            //Se encontrar um elemento menor que o mín atual...
            if (lista[j] < lista[indice_min]) {
                //...atualiza o índice mínimo
                indice_min = j;
            }
        }

        //Se o menor elemento não for o primeiro da parte não ordenada,
        //troca de lugar com ele
        if (indice_min != i) {
            temp = lista[i];
            lista[i] = lista[indice_min];
            lista[indice_min] = temp;
        }
    }
}


// ---- FUNÇÕES AUXILIARES ---
//Gera uma lista de n elementos em ordem crescente.
void gerarListaOrdenada(int lista[], int n) {
    for (int i = 0; i < n; i++) {
        lista[i] = i + 1;
    }
    imprimirLista("Original - Ordenada", lista, n);
}

//Gera uma lista de n elementos em ordem Decrescente

void gerarListaInversa(int lista[], int n) {
    for (int i = 0; i < n; i++) {
        lista[i] = n - i;
    }
    imprimirLista("Original - Inversa", lista, n);
}

void imprimirLista(const char* titulo, const int lista[], int n) {
    printf("%s: ", titulo);
    printf(" [ ");
    for (int i = 0; i < n; i++) {
        printf(" %d ", lista[i]);
    }
    printf(" ]\n");
}

void gerarListaAleatoria(int lista[], int n) {
    for (int i = 0; i < n; i++) {
        lista[i] = rand() % 100; // números entre 0 e 99
    }
    imprimirLista("Original - Aleatoria", lista, n);
}

void copiarLista(int destino[], const int origem[], int n) {
    for (int i = 0; i < n; i++) {
        destino[i] = origem[i];
    }
}
