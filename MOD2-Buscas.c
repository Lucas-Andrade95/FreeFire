#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Busca sequencial
int buscaSequencialIterativa(const char* lista[], int tamanho, const char* item);
int buscaSequencialRecursiva(const char* lista[], int tamanho, const char* item);
int buscaSequencialRecursiva_aux(const char* lista[], int tamanho, const char* item, int indice);

//Busca binária
int buscaBinariaIterativa(const char* lista[], int tamanho, const char* item);
int buscaBinariaRecursiva(const char* lista[], int tamanho, const char* item);
int buscaBinariaRecursiva_aux(const char* lista[], const char* item, int inicio, int fim);

//Função para imprimir resultados
void imprimirResultado(const char* nomeDaBusca, const char* item, int resultado);

//FUNÇÃO PRINCIPAL

int main() {
    //LISTA DE COMPRAS ORDENADA
    const char* listaDeCompras[] = {
        "arroz",
        "batata",
        "cebola",
        "detergente",
        "feijao",
        "leite",
        "macarrao",
        "oleo",
        "sal",
        "tomate"
    };

    int tamanhoDaLista = sizeof(listaDeCompras) / sizeof(listaDeCompras[0]);

    // Itens que vamos procurar para demonstrar os algoritmos;
    const char* itemExistente = "leite";
    const char* itemInexistente = "queijo";

    printf("--- DEMONSTRAÇÃO DE ALGORITMOS DE BUSCA EM LISTA DE TEXTO ---\n");
    printf("Lista utilizada: [arroz, batata, cebola, detergente, feijao, leite, macarrao, oleo, sal, tomate]\n");
    printf("------------------------------------------------------------------------------------------\n\n");

    // Realizando busca Sequencial
    printf("--- BUSCA SEQUENCIAL ---\n");
    // VERSÃO ITERATIVA
    //   Item existente
    int res1 = buscaSequencialIterativa(listaDeCompras, tamanhoDaLista, itemExistente);
    imprimirResultado("Sequencial Iterativa", itemExistente, res1);

    //   Item Inexistente
    int res2 = buscaSequencialIterativa(listaDeCompras, tamanhoDaLista, itemInexistente);
    imprimirResultado("Sequencial Iterativa", itemInexistente, res2);
    printf("\n");

    // VERSÃO RECURSIVA
    int res3 = buscaSequencialRecursiva(listaDeCompras, tamanhoDaLista, itemExistente);
    imprimirResultado("Sequencial Recursiva", itemExistente, res3);

    int res4 = buscaSequencialRecursiva(listaDeCompras, tamanhoDaLista, itemInexistente);
    imprimirResultado("Sequencial Recursiva", itemInexistente, res4);
    printf("--------------------------------------------------------------------\n\n");

    // ---- Realizando a Busca Binária em listas ordenadas ---
    printf("--- 2. BUSCA BINARIA --- \n");
    // Versão Iterativa
    int res5 = buscaBinariaIterativa(listaDeCompras, tamanhoDaLista, itemExistente);
    imprimirResultado("Binaria Iterativa", itemExistente, res5);

    int res6 = buscaBinariaIterativa(listaDeCompras, tamanhoDaLista, itemInexistente);
    imprimirResultado("Binaria iterativa", itemInexistente, res6);
    printf("\n");

    //Versao Recursiva
    int res7 = buscaBinariaRecursiva(listaDeCompras, tamanhoDaLista, itemExistente);
    imprimirResultado("Binaria Recursiva", itemExistente, res7);

    int res8 = buscaBinariaRecursiva(listaDeCompras, tamanhoDaLista, itemInexistente);
    imprimirResultado("Binaria Recursiva", itemInexistente, res8);
    printf("------------------------------------------------------------------\n");

    return 0;
}


// --- IMPLEMENTAÇÃO DAS FUNÇÕES ---

// BUSCA SEQUENCIAL

//

int buscaSequencialIterativa(const char* lista[], int tamanho, const char* item) {
    //Laço for percorre a lista de 0 até tamanho -1
    for (int i =0; i< tamanho; i++) {
        //comparando strings com strcmp
        if (strcmp(lista[i], item) == 0) {
            //Se as strings forem iguauis, encontramos o item!
            return i;
        }
    }
    //Se o laço terminar e não retornou nada, o item não está na lista
    return -1;
}

// BUSCA SEQUENCIAL RECURSIVA - NÃO RECOMENDADO PARA LISTAS GRANDES - RISCO DE STACK OVERFLOW
int buscaSequencialRecursiva(const char* lista[], int tamanho, const char* item) {
    //A lógica está na função auxiliar, começamos a partir do índice 0
    return buscaSequencialRecursiva_aux(lista, tamanho, item, 0);
}

int buscaSequencialRecursiva_aux(const char* lista[], int tamanho, const char* item, int indice) {
    if (indice >= tamanho) { 
        return -1; // se o índice for igual ou maior que o tamanho da lista , significa que já percorremos tudo e não encontramos.
    }

    if (strcmp(lista[indice], item) == 0) {
        return indice; // Encontrei! Retorno o índice.
    }

    //Passo Recursivo sequencial
    //Chamamos a mesma função novamente para verificar o próxinmo item da lista (índice +1)
    return buscaSequencialRecursiva_aux(lista, tamanho, item, indice +1);
}

//BUSCA BINÁRIA

int buscaBinariaIterativa(const char* lista[], int tamanho, const char* item) {
    int inicio = 0;
    int fim = tamanho -1;
    int meio;

    // O laço continua enquanto a sub-lista não tiver ultrapassado o fim
    while (inicio <= fim) {
        //Calcula o índice do meio
        //Usar inicio + (fim - inicio) para evitar overflow de int
        meio = inicio + (fim - inicio) / 2;

        //Compara a string do meio com o item procurado.
        int comparacao = strcmp(lista[meio], item);

        if (comparacao == 0) { //Encontrou!
            return meio;
        }
        else if (comparacao > 0) {
            //O item do meio vem DEPOIS do item procurado
            fim = meio - 1;
        }
        else { //comparação < 0  --> O meio vem ANTES do item procurado
            inicio = meio + 1;
        }
        return -1;
    }
}

int buscaBinariaRecursiva(const char* lista[], int tamanho, const char* item) {
    //Inicia a busca recursiva em toda a lista, do índice 0 até 'tamanho -1'
    return buscaBinariaRecursiva_aux(lista, item, 0, tamanho -1);
}

int buscaBinariaRecursiva_aux(const char* lista[], const char* item, int inicio, int fim) {
    if (inicio > fim) {
        return -1;
    }

    //PASSO RECURSIVO E CASO BASE DE SUCESSO
    int meio = inicio + (fim - inicio) / 2;
    int comparacao = strcmp(lista[meio], item);

    if (comparacao == 0) {
        //CASO BASE 2: SUCESSO
        return meio; //Encontrado!
    }
    else if (comparacao > 0) {
        //o item está na metade esquerda.
        return buscaBinariaRecursiva_aux(lista, item, inicio, meio -1);
    }
    else { //comparacao < 0
        return buscaBinariaRecursiva_aux(lista, item, meio +1, fim);
    }
}

//FUNÇÃO DE IMPRESSÃO

void imprimirResultado(const char* nomeDaBusca, const char* item, int resultado) {
    printf("[%s] Buscando por \"%s\"... \n", nomeDaBusca, item);
    if (resultado != -1) {
        printf(" -> Resultado: Item encontrado no indice %d.\n", resultado);
    } else {
        printf(" -> Resultado: Item nao encontrado na lista.\n");
    }
}
