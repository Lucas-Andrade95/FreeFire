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
    int prioridade;
} Item;

//Struct para a Mochila
typedef struct {
    Item itens[MAX_ITENS];
    int ocupacao;
} Mochila;

// Funções de gerenciamento
void adicionarItem(Mochila *m);
void removerItem(Mochila *m);
void listarItens(Mochila *m);

// Busca binária por nome (requere ordenação por nome)
void buscarBinariaPorNome(Mochila *m);

// Funções de ordenação
void ordenarItens(Mochila *m);
void ordenarPorNome(Mochila *m);
void ordenarPorTipo(Mochila *m);
void ordenarPorPrioridade(Mochila *m);

// Flag que indica se a mochila está ordenada por nome (necessário para busca binária)
int flagBuscaBinaria = 0;

int main() {
    Mochila mochila;
    mochila.ocupacao = 0; // Contador para saber a quantidade de itens
    int opcao;

    //MENU PRINCIPAL
    do {
        printf("\n--------------------------------------------------------------\n");
        printf("-------- PLANO DE FUGA - CÓDIGO DA ILHA (NÍVEL MESTRE) ---------\n");
        printf("----------------------------------------------------------------\n");
        printf("Itens na Mochila: %d/%d\n\n", mochila.ocupacao, MAX_ITENS);
        printf("1. Adicionar Componente\n");
        printf("2. Descartar Componente\n");
        printf("3. Listar Componentes (Inventário)\n");
        printf("4. Organizar Mochila (Ordenar Componente)\n");
        printf("5. Busca Binaria por Componente-Chave (por nome)\n");
        printf("0. ATIVAR TORRE DE FUGA (Sair)\n");
        printf("---------------------------------------------------------------\n");
        printf("Escolha uma opção: ");

        if (scanf("%d", &opcao) != 1) {
            // limpar entrada caso inválida
            int c;
            while ((c = getchar()) != '\n' && c != EOF) {}
            opcao = -1;
        }

        switch(opcao) {
            case 1:
                adicionarItem(&mochila);
                break;
            case 2:
                removerItem(&mochila);
                break;
            case 3:
                listarItens(&mochila);
                printf("\nPressione Enter para continuar...");
                getchar(); // pega o '\n' remanescente
                getchar();
                break;
            case 4:
                ordenarItens(&mochila);
                break;
            case 5:
                buscarBinariaPorNome(&mochila);
                break;
            case 0:
                printf("TORRE MONTADA COM SUCESSO! Saindo...\n");
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
    printf("\n--- Coletando Novo Componente ---\n");

    printf("Nome: ");
    scanf("%s", novo.nome);

    printf("Tipo (Estrutural, Eletrônico, Energia): ");
    scanf("%s", novo.tipo);

    printf("Quantidade: ");
    scanf("%d", &novo.quantidade);

    printf("Prioridade de Montagem (1-5): ");
    scanf("%d", &novo.prioridade);

    m->itens[m->ocupacao] = novo;
    m->ocupacao++;

    // Após alteração na lista, a ordenação por nome pode estar inválida
    flagBuscaBinaria = 0;

    printf("\nComponente '%s' coletado com sucesso!\n", novo.nome);
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
    printf("\nNome do Componente a Descartar: ");
    scanf("%s", nomeBusca);

    for (int i = 0; i < m->ocupacao; i++) {
        if (strcmp(m->itens[i].nome, nomeBusca) == 0) {
            for (int j = i; j < m->ocupacao - 1; j++) {
                m->itens[j] = m->itens[j+1];
            }
            m->ocupacao--;

            // Após alteração na lista, a ordenação por nome pode estar inválida
            flagBuscaBinaria = 0;

            printf("\nComponente '%s' descartado com sucesso!\n", nomeBusca);
            listarItens(m);
            printf("\nPressione Enter para continuar...");
            getchar(); 
            getchar(); 
            return;
        }
    }

    printf("\nItem '%s' não encontrado.\n", nomeBusca);
}

// Lista os itens atuais
void listarItens(Mochila *m) {
    printf("\n--- ITENS NA MOCHILA (%d/%d) ---\n", m->ocupacao, MAX_ITENS);
    printf("--------------------------------------------------------------------------\n");
    printf("%-25s | %-15s | %-10s | %-10s\n", "NOME", "TIPO", "QUANTIDADE", "PRIORIDADE");
    printf("--------------------------------------------------------------------------\n");

    if(m->ocupacao == 0) {
        printf("(A mochila está vazia)\n");
        printf("----------------------------------------------------------------------\n");
        return;
    }

    for (int i = 0; i < m->ocupacao; i++) {
        printf("%-25s | %-15s | %-10d | %-10d\n",
            m->itens[i].nome,
            m->itens[i].tipo,
            m->itens[i].quantidade,
            m->itens[i].prioridade
        );
    }

    printf("------------------------------------------------------------------------\n");
}

// Busca binária por nome: só funcionar se flagBuscaBinaria == 1
void buscarBinariaPorNome(Mochila *m) {
    if (m->ocupacao == 0) {
        printf("\nA mochila está vazia!\n");
        printf("\nPressione Enter para continuar...");
        getchar(); 
        getchar(); 
        return;
    }
    if (flagBuscaBinaria == 0) {
        printf("\nALERTA: A busca binaria requer que a mochila esteja ordenada por NOME\nUse a opcao 4 para organizar a mochila primeiro.\n");
        printf("\nPressione Enter para continuar...");
        getchar(); 
        getchar(); 
        return;
    }

    char nomeBusca[MAX_NOME];
    printf("\n--- Busca Binária por Componente Chave ---\n");
    printf("Digite o nome do componente que deseja buscar: ");
    scanf("%s", nomeBusca);

    int inicio = 0;
    int fim = m->ocupacao - 1;
    int meio;
    int encontrada = 0;

    while (inicio <= fim) {
        meio = inicio + (fim - inicio) / 2;
        int comparacao = strcmp(m->itens[meio].nome, nomeBusca);

        if (comparacao == 0) { // Encontrou
            printf("\n--- Componente-Chave Encontrado! ---\n");
            printf("Nome: %s\n", m->itens[meio].nome);
            printf("Tipo: %s\n", m->itens[meio].tipo);
            printf("Quantidade: %d\n", m->itens[meio].quantidade);
            printf("Prioridade: %d\n", m->itens[meio].prioridade);
            encontrada = 1;
            break;
        } else if (comparacao < 0) {
            // meio < nomeBusca -> procurar na metade direita
            inicio = meio + 1;
        } else {
            // meio > nomeBusca -> procurar na metade esquerda
            fim = meio - 1;
        }
    }

    if (!encontrada) {
        printf("Resultado: Item '%s' NÃO foi encontrado na mochila\n", nomeBusca);
    }

    printf("\nPressione Enter para continuar...");
    getchar(); // limpar '\n' remanescente
    getchar();
}

// Menu de ordenação: escolhe critério e chama a função apropriada
void ordenarItens(Mochila *m) {
    if (m->ocupacao == 0) {
        printf("\nA mochila está vazia!\n");
        printf("Pressione Enter para continuar...");
        getchar();
        getchar();
        return;
    }
    
    int escolha = 0;
    printf("\n--- Estratégia de Organização ---\n");
    printf("Como deseja ordenar os componentes?\n");
    printf("1. Por Nome (Ordem Alfabética)\n");
    printf("2. Por Tipo\n");
    printf("3. Por Prioridade de Montagem\n");
    printf("0. Cancelar\n");
    printf("Escolha o critério: ");
    if (scanf("%d", &escolha) != 1) {
        int c;
        while ((c = getchar()) != '\n' && c != EOF) {}
        printf("Entrada inválida. Voltando ao menu principal.\n");
        return;
    }

    switch (escolha)
    {
        case 1:
            ordenarPorNome(m);
            flagBuscaBinaria = 1; // agora está ordenada por nome
            listarItens(m);
            printf("\nPressione Enter para voltar ao Menu Principal...");
            getchar(); // limpar '\n' remanescente
            getchar();
            break;
        case 2:
            ordenarPorTipo(m);
            flagBuscaBinaria = 0; // ordenada por tipo, busca binária por nome inválida
            listarItens(m);
            printf("\nPressione Enter para voltar ao Menu Principal...");
            getchar(); // limpar '\n' remanescente
            getchar();
            break;
        case 3:
            ordenarPorPrioridade(m);
            flagBuscaBinaria = 0; // ordenada por prioridade, busca binária por nome inválida
            listarItens(m);
            printf("\nPressione Enter para voltar ao Menu Principal...");
            getchar(); // limpar '\n' remanescente
            getchar();
            break;
        case 0:
            printf("Cancelado. Voltando ao menu principal.\n");
            break;
        default:
            printf("Opcao Inválida! Tente novamente.\n");
            break;
    }
}

// Ordena por nome em ordem alfabética (ascendente) usando bubble sort em structs
void ordenarPorNome(Mochila *m) {
    if (m->ocupacao < 2) return;

    for (int i = 0; i < m->ocupacao - 1; i++) {
        for (int j = 0; j < m->ocupacao - i - 1; j++) {
            if (strcmp(m->itens[j].nome, m->itens[j+1].nome) > 0) {
                Item aux = m->itens[j];
                m->itens[j] = m->itens[j+1];
                m->itens[j+1] = aux;
            }
        }
    }
}

// Ordena por tipo (alfabética) — se tipos iguais, mantém ordem relativa (estável o suficiente aqui)
void ordenarPorTipo(Mochila *m) {
    if (m->ocupacao < 2) return;

    for (int i = 0; i < m->ocupacao - 1; i++) {
        for (int j = 0; j < m->ocupacao - i - 1; j++) {
            if (strcmp(m->itens[j].tipo, m->itens[j+1].tipo) > 0) {
                Item aux = m->itens[j];
                m->itens[j] = m->itens[j+1];
                m->itens[j+1] = aux;
            }
        }
    }
}

// Ordena por prioridade (maior prioridade primeiro). Se prioridades iguais, mantém ordem relativa.
void ordenarPorPrioridade(Mochila *m) {
    if (m->ocupacao < 2) return;

    for (int i = 0; i < m->ocupacao - 1; i++) {
        for (int j = 0; j < m->ocupacao - i - 1; j++) {
            if (m->itens[j].prioridade < m->itens[j+1].prioridade) {
                Item aux = m->itens[j];
                m->itens[j] = m->itens[j+1];
                m->itens[j+1] = aux;
            }
        }
    }
}
