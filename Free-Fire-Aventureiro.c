#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ITENS 10
#define MAX_NOME 30
#define MAX_TIPO 20


//Struct para os itens
typedef struct {
    char nome[MAX_NOME];
    char tipo[MAX_TIPO];
    int quantidade;
} Item;

//Struct para a Mochila
typedef struct {
    Item itens[MAX_ITENS];
    int ocupacao;
} Mochila;

// Funções
void adicionarItem(Mochila *m);
void removerItem(Mochila *m);
void listarItens(Mochila *m);
void buscarItemPorNome(Mochila *m);

int main() {
    Mochila mochila;
    mochila.ocupacao = 0; // Contador para saber a quantidade de itens
    int opcao;

    //MENU PRINCIPAL
    do {
        printf("\n---------------------------------------------------\n");
        printf("-------- MOCHILA DE SOBREVIVÊNCIA ---------\n");
        printf("---------------------------------------------------\n");
        printf("Itens na Mochila: %d/%d\n\n", mochila.ocupacao, MAX_ITENS);
        printf("1. Adicionar Item\n");
        printf("2. Remover Item\n");
        printf("3. Listar Itens\n");
        printf("4. Buscar Item por Nome\n");
        printf("0. Sair\n");
        printf("--------------------------------------------------\n");
        printf("Escolha uma opção: ");

        scanf("%d", &opcao);

        switch(opcao) {
            case 1:
                adicionarItem(&mochila);
                break;
            case 2:
                removerItem(&mochila);
                break;
            case 3:
                listarItens(&mochila);
                break;
            case 4:
                buscarItemPorNome(&mochila);
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }

    } while(opcao != 0);

    return 0;
}

void adicionarItem(Mochila *m) {
    //VALIDAÇÃO DE ESPAÇO DISPONÍVEL
    if (m->ocupacao == MAX_ITENS) {
        printf("\nSem espaço suficiente! Descarte itens para adicionar mais.\n");
        return;
    }

    Item novo;
    printf("\n--- Adicionar Novo Item ---\n");

    printf("Nome do item: ");
    scanf("%s", novo.nome);

    printf("Tipo do item: ");
    scanf("%s", novo.tipo);

    printf("Quantidade: ");
    scanf("%d", &novo.quantidade);

    m->itens[m->ocupacao] = novo;
    m->ocupacao++;

    printf("\nItem '%s' adicionado com sucesso!\n", novo.nome);
    listarItens(m);
    printf("\nPressione Enter para continuar...");
    getchar(); 
    getchar(); 

}

void removerItem(Mochila *m) {
    if (m->ocupacao == 0) {
        printf("\nA mochila está vazia!\n");
        return;
    }

    char nomeBusca[MAX_NOME];
    printf("\nNome do item a remover: ");
    scanf("%s", nomeBusca);

    for (int i = 0; i < m->ocupacao; i++) {
        if (strcmp(m->itens[i].nome, nomeBusca) == 0) {
            for (int j = i; j < m->ocupacao - 1; j++) {
                m->itens[j] = m->itens[j+1];
            }
            m->ocupacao--;

            printf("\nItem '%s' removido com sucesso!\n", nomeBusca);
            listarItens(m);
            printf("\nPressione Enter para continuar...");
            getchar(); 
            getchar(); 
            return;
        }
    }

    printf("\nItem '%s' não encontrado.\n", nomeBusca);
}

void listarItens(Mochila *m) {
    printf("\n--- ITENS NA MOCHILA (%d/%d) ---\n", m->ocupacao, MAX_ITENS);
    printf("--------------------------------------------------------------\n");
    printf("%-25s | %-15s | %-10s\n", "NOME", "TIPO", "QUANTIDADE");
    printf("--------------------------------------------------------------\n");

    if(m->ocupacao == 0) {
        printf("(A mochila está vazia)\n");
        printf("--------------------------------------------------------------\n");
        return;
    }

    for (int i = 0; i < m->ocupacao; i++) {
        printf("%-25s | %-15s | %-10d\n",
            m->itens[i].nome,
            m->itens[i].tipo,
            m->itens[i].quantidade
        );
    }

    printf("--------------------------------------------------------------\n");
}

void buscarItemPorNome(Mochila *m) {
    if (m->ocupacao == 0) {
        printf("\nA mochila está vazia!\n");
        printf("\nPressione Enter para continuar...");
        getchar(); 
        getchar(); 
        return;
    }
    else {
        char nomeBusca[MAX_NOME];
        printf("\n--- Buscar item na Mochila ---\n");
        printf("Digite o nome do item que deseja buscar: ");
        scanf("%s", nomeBusca);

        //Laço for percorre a lista de 0 até m->ocupacao para encontrar nomeBusca
        for (int i = 0; i < m->ocupacao; i++) {
            //comparando strings com strcmp
            if (strcmp(m->itens[i].nome, nomeBusca) == 0) {
            //Se as strings forem iguais, encontramos o item!
            printf("\n--- Item Encontrado! ---\n");
            printf("Nome: %s\n", m->itens[i].nome);
            printf("Tipo: %s\n", m->itens[i].tipo);
            printf("Quantidade: %d\n", m->itens[i].quantidade);
            printf("\nPressione Enter para continuar...");
            getchar(); 
            getchar(); 
            return;
            }
        }
        //Se o laço terminar e não retornou nada, o item não está na lista
        printf("Resultado: Item '%s' NÃO foi encontrado na mochila\n", nomeBusca);
        printf("\nPressione Enter para continuar...");
        getchar(); 
        getchar(); 
        return;
    }
    
}
