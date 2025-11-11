#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR_LEN 50 // Tamanho máximo de cada string

//PARTE 1 --> LISTA ESTÁTICA (Vetor)

#define TAM_MAX 10 // Número máximo de itens da lista estática

typedef struct {
        char dados[TAM_MAX][MAX_STR_LEN]; // Matriz de 10 linhas e 50 colunas (char)
        int quantidade; //contador
} ListaEstatica;

// Funções da Lista Estática

void inicializarListaEstatica(ListaEstatica *lista);

void inserirListaEstatica(ListaEstatica *lista, const char* texto);
void removerListaEstatica(ListaEstatica *lista, const char* texto);
void listarListaEstatica(const ListaEstatica *lista);


//PARTE 2 --> LISTA ENCADEADA (STR)
typedef struct No {
    char* dado;
    struct No *proximo;
} No;

//"Atalho" para a lista
typedef No* ListaEncadeada;

//Funções da lista encadeada

void inicializarListaEncadeada(ListaEncadeada *lista);

void removerListaEncadeada(ListaEncadeada *lista, const char* texto);
void listarListaEncadeada(const ListaEncadeada lista);
void liberarListaEncadeada(ListaEncadeada *lista); // Função para Limpar memória

//MAIN E MENUS

void menuListaEstatica();
void menuListaEncadeada();

int main() {
    int opcao;
    do {
        printf("\n--- MANIPULAÇÃO DE LISTAS (TEXTO) ---\n");
        printf("1. Lista Estatica\n");
        printf("2. Lista Encadeada\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            menuListaEstatica();
            break;
        case 2:
            menuListaEncadeada();
            break;
        case 0:
            printf("Saindo ...\n");
            break;
        default:
            printf("Opção inválida! \n");
            break;
        }
    } while (opcao != 0);

    return 0;
}

// IMPLEMENTAÇÃO DAS FUNÇÕES DA LISTA ESTÁTICA

void inicializarListaEstatica(ListaEstatica *lista) {
    lista->quantidade = 0;
}

void inserirListaEstatica(ListaEstatica *lista, const char* texto) {
    //Validação se a lista já atingiu TAM_MAX
    if (lista->quantidade == TAM_MAX) {
        printf("Erro: Lista cheia! Não é possível inserir \n");
        return;
    }
    strcpy(lista->dados[lista->quantidade], texto);
    lista->quantidade++;
    printf("Texto \"%s\" inserido com sucesso.\n", texto);
}

void removerListaEstatica(ListaEstatica *lista, const char* texto) {
    int i, pos = -1;
    
    for (i = 0; i < lista->quantidade; i++) {
        if (strcmp(lista->dados[i], texto) == 0) {
            pos = i;
            break;
        }
    }

    //Tratamento de erro: Se o loop terminar e pos continuar -1, o item não foi encontrado.
    if (pos ==-1) {
        printf("Erro: Texto \"%s\" não encontrado na lista!\n", texto);
        return;
    }

    //"Fechar lacuna" da lista, deslocando os elementos posteriores para a esquerda usando strcpy
    for (i = pos; i < lista->quantidade -1; i++) {
        strcpy(lista->dados[i], lista->dados[i + 1]);
    }

    //Atualização do Contador:
    lista->quantidade--;
    printf("Texto \"%s\" removido com sucesso.\n", texto);
}

void listarListaEstatica(const ListaEstatica *lista) {
    //Validação se a lista contém itens
    if (lista->quantidade ==0) {
        printf("A lista estatica está vazia!\n");
        return;
    }
    printf("Itens da Lista Estática: [ ");
    for (int i = 0; i <lista->quantidade; i++) {
        printf("\"%s\" ", lista->dados[i]); //Usando %s para imprimir strings
    }
    printf("]\n");
}

// IMPLEMENTAÇÃO DAS FUNÇÕES DA LISTA ENCADEADA

void inicializarListaEncadeada(ListaEncadeada *lista) {
    *lista = NULL;
}

void inserirListaEncadeada(ListaEncadeada *lista, const char* texto) {
    //.1 ALocar memória para o Novo Nó
    No* novoNo = (No*) malloc(sizeof(No));

    if (novoNo == NULL) {
        printf("Erro: Falha na alocação de memória do Nó!n");
        return;
    }

    //.Alocar memória para String dentro do Nó
    novoNo->dado = (char*) malloc(strlen(texto) + 1);

    if (novoNo->dado ==NULL) {
        printf("Erro: Falha na alocação de memória para o texto.n");
        free(novoNo); //Libera o nó que já foi alocado
        return;
    }

    //3. COpiar o texto para a memória recém-alocada
    strcpy(novoNo->dado, texto);

    //4.Ligar o novo nó a lista
    //O ponteiro proximo do novo nó passa a apontar para o que era o antigo primeiro nó da lista.
    novoNo->proximo = *lista;
    //O novo nó agora é o primeiro item:
    *lista = novoNo;

    printf("Texto \"%s\" inserido com sucesso\n.", texto);
}

void removerListaEncadeada(ListaEncadeada *lista, const char* texto) {
    No *atual = *lista;
    No *anterior = NULL;

    while (atual != NULL && strcmp(atual->dado, texto) !=0) {
        anterior = atual;
        atual = atual->proximo;
    }

    if (atual == NULL) {
        printf("Erro: Texto \"%s\" Não encontrado na lista.\n", texto);
        return;
    }

    //Se o nó removido for o primeiro (anterior ==NULL), a cabeça da lista (*lista) passa a ser o segundo (atual->proximo)
    //Se estiver no meio ou fim, o ponteiro próximo do nó anterior pula o atual e aponta para atual->proximo
    if (anterior == NULL) {
        *lista = atual->proximo;
    } else {
        anterior->proximo = atual->proximo;
    }

    //Liberação da memória

    //Liberar string dentro do nó
    free(atual->dado);
    //Liberando memória do nó
    free(atual);
    printf("Texto \"%s\" removido com sucesso.;\n", texto);
}

void listarListaEncadeada(const ListaEncadeada lista) {
    No *temp = lista;
    if (temp ==NULL) {
        printf("A lista encadeada está vazia!\n");
        return;
    }
    printf("Itens da Lista Encadeada: [ ");
    while (temp != NULL) {
        printf("\"%s\" ", temp->dado);
        temp = temp->proximo;
    }
    printf("]\n");
}


//Liberando toda a memória da lista encadeada no final
void liberarListaEncadeada(ListaEncadeada *lista) {
    No *atual = *lista;
    No *proximo;
    while (atual != NULL) {
        proximo = atual->proximo;
        free(atual->dado); //Libera a string
        free(atual); //Libera o nó
        atual = proximo;
    }
    *lista = NULL;
}

void menuListaEstatica() {
    ListaEstatica lista;
    inicializarListaEstatica(&lista);

    int opcao;
    char texto[MAX_STR_LEN];

    do {
        printf("\n-- MENU LISTA ESTÁTICA --\n");
        printf("1. Inserir item\n");
        printf("2. Remover item\n");
        printf("3. Listar itens\n");
        printf("0. Voltar ao menu principal\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar(); // Limpa o \n deixado pelo scanf

        switch (opcao) {
        case 1:
            printf("Digite o texto a inserir: ");
            fgets(texto, MAX_STR_LEN, stdin);
            texto[strcspn(texto, "\n")] = '\0'; // Remove \n
            inserirListaEstatica(&lista, texto);
            break;

        case 2:
            printf("Digite o texto a remover: ");
            fgets(texto, MAX_STR_LEN, stdin);
            texto[strcspn(texto, "\n")] = '\0';
            removerListaEstatica(&lista, texto);
            break;

        case 3:
            listarListaEstatica(&lista);
            break;

        case 0:
            printf("Voltando ao menu principal...\n");
            break;

        default:
            printf("Opção inválida!\n");
        }
    } while (opcao != 0);
}

void menuListaEncadeada() {
    ListaEncadeada lista;
    inicializarListaEncadeada(&lista);

    int opcao;
    char texto[MAX_STR_LEN];

    do {
        printf("\n-- MENU LISTA ENCADEADA --\n");
        printf("1. Inserir item\n");
        printf("2. Remover item\n");
        printf("3. Listar itens\n");
        printf("0. Voltar ao menu principal\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar(); // limpa buffer

        switch (opcao) {
        case 1:
            printf("Digite o texto a inserir: ");
            fgets(texto, MAX_STR_LEN, stdin);
            texto[strcspn(texto, "\n")] = '\0';
            inserirListaEncadeada(&lista, texto);
            break;

        case 2:
            printf("Digite o texto a remover: ");
            fgets(texto, MAX_STR_LEN, stdin);
            texto[strcspn(texto, "\n")] = '\0';
            removerListaEncadeada(&lista, texto);
            break;

        case 3:
            listarListaEncadeada(lista);
            break;

        case 0:
            printf("Voltando ao menu principal...\n");
            break;

        default:
            printf("Opção inválida!\n");
        }
    } while (opcao != 0);

    liberarListaEncadeada(&lista);
}
