#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ITENS 10

// ---------------- Struct Item ---------------- //
// Representa cada objeto coletado pelo jogador
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

// ---------------- Funções ---------------- //

// Inserir um item na mochila
void inserirItem(Item mochila[], int *qtdAtual) {
    if(*qtdAtual >= MAX_ITENS) {
        printf("Mochila cheia! Nao e possivel adicionar mais itens.\n");
        return;
    }

    printf("\nCadastro do Item %d:\n", *qtdAtual + 1);
    printf("Nome: ");
    scanf(" %[^\n]s", mochila[*qtdAtual].nome);
    printf("Tipo (arma, municao, cura, ferramenta): ");
    scanf("%s", mochila[*qtdAtual].tipo);
    printf("Quantidade: ");
    scanf("%d", &mochila[*qtdAtual].quantidade);

    (*qtdAtual)++;
    printf("Item cadastrado com sucesso!\n");
}

// Remover um item da mochila pelo nome
void removerItem(Item mochila[], int *qtdAtual) {
    if(*qtdAtual == 0) {
        printf("Mochila vazia! Nao ha itens para remover.\n");
        return;
    }

    char nomeBusca[30];
    printf("Digite o nome do item a ser removido: ");
    scanf(" %[^\n]s", nomeBusca);

    int encontrado = 0;
    for(int i = 0; i < *qtdAtual; i++) {
        if(strcmp(mochila[i].nome, nomeBusca) == 0) {
            // Desloca os itens restantes para preencher o espaço
            for(int j = i; j < *qtdAtual - 1; j++) {
                mochila[j] = mochila[j+1];
            }
            (*qtdAtual)--;
            encontrado = 1;
            printf("Item removido com sucesso!\n");
            break;
        }
    }

    if(!encontrado) {
        printf("Item nao encontrado na mochila.\n");
    }
}

// Listar todos os itens da mochila
void listarItens(Item mochila[], int qtdAtual) {
    if(qtdAtual == 0) {
        printf("Mochila vazia!\n");
        return;
    }

    printf("\n=== Itens na Mochila ===\n");
    for(int i = 0; i < qtdAtual; i++) {
        printf("%d - Nome: %s | Tipo: %s | Quantidade: %d\n",
               i+1, mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
    }
}

// Busca sequencial de um item pelo nome
void buscarItem(Item mochila[], int qtdAtual) {
    if(qtdAtual == 0) {
        printf("Mochila vazia!\n");
        return;
    }

    char nomeBusca[30];
    printf("Digite o nome do item a buscar: ");
    scanf(" %[^\n]s", nomeBusca);

    for(int i = 0; i < qtdAtual; i++) {
        if(strcmp(mochila[i].nome, nomeBusca) == 0) {
            printf("Item encontrado!\nNome: %s | Tipo: %s | Quantidade: %d\n",
                   mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
            return;
        }
    }

    printf("Item nao encontrado na mochila.\n");
}

// ---------------- Main ---------------- //
int main() {
    Item mochila[MAX_ITENS];
    int qtdAtual = 0;
    int opcao;

    do {
        printf("\n=== Sistema de Inventario ===\n");
        printf("1 - Inserir item\n");
        printf("2 - Remover item\n");
        printf("3 - Listar itens\n");
        printf("4 - Buscar item\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1: inserirItem(mochila, &qtdAtual); break;
            case 2: removerItem(mochila, &qtdAtual); break;
            case 3: listarItens(mochila, qtdAtual); break;
            case 4: buscarItem(mochila, qtdAtual); break;
            case 0: printf("Saindo do sistema...\n"); break;
            default: printf("Opcao invalida! Tente novamente.\n");
        }
    } while(opcao != 0);

    return 0;
}
