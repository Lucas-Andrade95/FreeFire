#include <stdio.h>
#include <stdlib.h>

struct No {
    int dado;
    struct No* proximo;
};

int main() {
    void inserirNoInicio(struct **No inicio, int valor) {
        //1. Criamos nosso "novo nó" alocando memória para ele
        struct No* novo = (struct *No) malloc(sizeof(struct No));

        //VERIFICANDO SE A ALOCAÇÃO FOI BEM SUCEDIDA
        if (No == NULL) {
            printf("Erro: Falha na alocação de memória.\n");
            return;
        }

        // 2. Colocamos o valor dentro dele
        novo->dado = valor;

        // 3. o "próximo" do nosso novo nó será o antigo início da lista
        // 'inicio' é um ponteiro para um ponteiro, então '*inicio' nos dá o ponteiro para o primeiro nó atual.
        novo->proximo = *inicio;

        // 4. Agora, o início da lista passa a aser o nosso novo nó!
        //Modificamos o ponteiro original para que ele aponte para  o novo nó.
        *inicio = novo;
    }

}