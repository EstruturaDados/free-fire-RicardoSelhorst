#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ITENS 10

// ---------------- Structs ---------------- //
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

typedef struct No {
    Item dados;
    struct No* proximo;
} No;

// ---------------- Variáveis Globais ---------------- //
int comparacoesSequencial = 0;
int comparacoesBinaria = 0;

// ================== FUNÇÕES PARA VETOR ================== //

// Inserir item no vetor
void inserirItemVetor(Item vetor[], int *qtdAtual) {
    if(*qtdAtual >= MAX_ITENS) {
        printf("Vetor cheio!\n");
        return;
    }
    printf("Nome: "); scanf(" %[^\n]s", vetor[*qtdAtual].nome);
    printf("Tipo: "); scanf("%s", vetor[*qtdAtual].tipo);
    printf("Quantidade: "); scanf("%d", &vetor[*qtdAtual].quantidade);
    (*qtdAtual)++;
    printf("Item inserido no vetor.\n");
}

// Remover item do vetor pelo nome
void removerItemVetor(Item vetor[], int *qtdAtual) {
    if(*qtdAtual == 0) {
        printf("Vetor vazio!\n");
        return;
    }
    char nome[30];
    printf("Nome do item a remover: "); scanf(" %[^\n]s", nome);

    int encontrado = 0;
    for(int i = 0; i < *qtdAtual; i++) {
        if(strcmp(vetor[i].nome, nome) == 0) {
            for(int j = i; j < *qtdAtual - 1; j++) vetor[j] = vetor[j+1];
            (*qtdAtual)--;
            encontrado = 1;
            printf("Item removido do vetor.\n");
            break;
        }
    }
    if(!encontrado) printf("Item nao encontrado.\n");
}

// Listar itens do vetor
void listarVetor(Item vetor[], int qtdAtual) {
    if(qtdAtual == 0) {
        printf("Vetor vazio!\n");
        return;
    }
    for(int i = 0; i < qtdAtual; i++)
        printf("%d - %s | %s | %d\n", i+1, vetor[i].nome, vetor[i].tipo, vetor[i].quantidade);
}

// Ordenar vetor por nome (Bubble Sort)
void ordenarVetor(Item vetor[], int qtdAtual) {
    for(int i = 0; i < qtdAtual-1; i++) {
        for(int j = 0; j < qtdAtual-i-1; j++) {
            if(strcmp(vetor[j].nome, vetor[j+1].nome) > 0) {
                Item temp = vetor[j];
                vetor[j] = vetor[j+1];
                vetor[j+1] = temp;
            }
        }
    }
}

// Busca sequencial no vetor
int buscarSequencialVetor(Item vetor[], int qtdAtual, char *nome) {
    comparacoesSequencial = 0;
    for(int i = 0; i < qtdAtual; i++) {
        comparacoesSequencial++;
        if(strcmp(vetor[i].nome, nome) == 0) return i;
    }
    return -1;
}

// Busca binária no vetor (após ordenar)
int buscarBinariaVetor(Item vetor[], int qtdAtual, char *nome) {
    comparacoesBinaria = 0;
    int esquerda = 0, direita = qtdAtual-1;
    while(esquerda <= direita) {
        int meio = (esquerda + direita)/2;
        comparacoesBinaria++;
        int cmp = strcmp(vetor[meio].nome, nome);
        if(cmp == 0) return meio;
        else if(cmp < 0) esquerda = meio + 1;
        else direita = meio - 1;
    }
    return -1;
}

// ================== FUNÇÕES PARA LISTA ENCADEADA ================== //

// Inserir item no início da lista
void inserirItemLista(No **inicio) {
    No *novo = (No*)malloc(sizeof(No));
    printf("Nome: "); scanf(" %[^\n]s", novo->dados.nome);
    printf("Tipo: "); scanf("%s", novo->dados.tipo);
    printf("Quantidade: "); scanf("%d", &novo->dados.quantidade);

    novo->proximo = *inicio;
    *inicio = novo;
    printf("Item inserido na lista encadeada.\n");
}

// Remover item pelo nome da lista encadeada
void removerItemLista(No **inicio) {
    if(*inicio == NULL) { printf("Lista vazia!\n"); return; }
    char nome[30]; printf("Nome do item a remover: "); scanf(" %[^\n]s", nome);
    No *atual = *inicio, *ant = NULL;

    while(atual != NULL) {
        if(strcmp(atual->dados.nome, nome) == 0) {
            if(ant == NULL) *inicio = atual->proximo;
            else ant->proximo = atual->proximo;
            free(atual);
            printf("Item removido da lista.\n");
            return;
        }
        ant = atual; atual = atual->proximo;
    }
    printf("Item nao encontrado.\n");
}

// Listar itens da lista encadeada
void listarLista(No *inicio) {
    if(inicio == NULL) { printf("Lista vazia!\n"); return; }
    No *atual = inicio;
    while(atual != NULL) {
        printf("%s | %s | %d\n", atual->dados.nome, atual->dados.tipo, atual->dados.quantidade);
        atual = atual->proximo;
    }
}

// Busca sequencial na lista encadeada
No* buscarSequencialLista(No *inicio, char *nome) {
    comparacoesSequencial = 0;
    No *atual = inicio;
    while(atual != NULL) {
        comparacoesSequencial++;
        if(strcmp(atual->dados.nome, nome) == 0) return atual;
        atual = atual->proximo;
    }
    return NULL;
}

// Liberar memória da lista
void liberarLista(No *inicio) {
    No *atual;
    while(inicio != NULL) {
        atual = inicio;
        inicio = inicio->proximo;
        free(atual);
    }
}

// ================== MAIN ================== //

int main() {
    Item vetor[MAX_ITENS];
    int qtdVetor = 0;
    No *lista = NULL;

    int opcao, estrutura;

    do {
        printf("\nEscolha a estrutura:\n1 - Vetor\n2 - Lista Encadeada\n0 - Sair\nOpcao: ");
        scanf("%d", &estrutura);

        if(estrutura == 0) break;

        do {
            printf("\nOperacoes:\n1-Inserir\n2-Remover\n3-Listar\n4-Busca Sequencial\n5-Busca Binaria (vetor)\n0-Voltar\nOpcao: ");
            scanf("%d", &opcao);

            if(estrutura == 1) { // Vetor
                switch(opcao) {
                    case 1: inserirItemVetor(vetor, &qtdVetor); break;
                    case 2: removerItemVetor(vetor, &qtdVetor); break;
                    case 3: listarVetor(vetor, qtdVetor); break;
                    case 4: {
                        char nome[30]; printf("Nome para buscar: "); scanf(" %[^\n]s", nome);
                        int idx = buscarSequencialVetor(vetor, qtdVetor, nome);
                        if(idx != -1) printf("Encontrado: %s | Comparacoes: %d\n", vetor[idx].nome, comparacoesSequencial);
                        else printf("Nao encontrado | Comparacoes: %d\n", comparacoesSequencial);
                        break;
                    }
                    case 5: {
                        ordenarVetor(vetor, qtdVetor);
                        char nome[30]; printf("Nome para busca binaria: "); scanf(" %[^\n]s", nome);
                        int idx = buscarBinariaVetor(vetor, qtdVetor, nome);
                        if(idx != -1) printf("Encontrado: %s | Comparacoes: %d\n", vetor[idx].nome, comparacoesBinaria);
                        else printf("Nao encontrado | Comparacoes: %d\n", comparacoesBinaria);
                        break;
                    }
                }
            } else if(estrutura == 2) { // Lista Encadeada
                switch(opcao) {
                    case 1: inserirItemLista(&lista); break;
                    case 2: removerItemLista(&lista); break;
                    case 3: listarLista(lista); break;
                    case 4: {
                        char nome[30]; printf("Nome para buscar: "); scanf(" %[^\n]s", nome);
                        No *res = buscarSequencialLista(lista, nome);
                        if(res != NULL) printf("Encontrado: %s | Comparacoes: %d\n", res->dados.nome, comparacoesSequencial);
                        else printf("Nao encontrado | Comparacoes: %d\n", comparacoesSequencial);
                        break;
                    }
                    case 5: printf("Busca binaria nao aplicavel na lista encadeada!\n"); break;
                }
            }
        } while(opcao != 0);

    } while(estrutura != 0);

    liberarLista(lista);
    return 0;
}
