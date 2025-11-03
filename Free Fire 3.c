#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_COMPONENTES 20

// ---------------- Struct ---------------- //
typedef struct {
    char nome[30];
    char tipo[20];
    int prioridade;
} Componente;

// ---------------- Funções Auxiliares ---------------- //

// Mostrar todos os componentes
void mostrarComponentes(Componente comp[], int n) {
    printf("\n%-30s %-20s %-10s\n", "Nome", "Tipo", "Prioridade");
    printf("---------------------------------------------------------\n");
    for(int i = 0; i < n; i++) {
        printf("%-30s %-20s %-10d\n", comp[i].nome, comp[i].tipo, comp[i].prioridade);
    }
    printf("\n");
}

// ---------------- Algoritmos de Ordenação ---------------- //

// Bubble Sort por nome (string)
void bubbleSortNome(Componente comp[], int n, int *comparacoes) {
    *comparacoes = 0;
    for(int i = 0; i < n-1; i++) {
        for(int j = 0; j < n-i-1; j++) {
            (*comparacoes)++;
            if(strcmp(comp[j].nome, comp[j+1].nome) > 0) {
                Componente temp = comp[j];
                comp[j] = comp[j+1];
                comp[j+1] = temp;
            }
        }
    }
}

// Insertion Sort por tipo (string)
void insertionSortTipo(Componente comp[], int n, int *comparacoes) {
    *comparacoes = 0;
    for(int i = 1; i < n; i++) {
        Componente key = comp[i];
        int j = i - 1;
        while(j >= 0) {
            (*comparacoes)++;
            if(strcmp(comp[j].tipo, key.tipo) > 0) {
                comp[j+1] = comp[j];
                j--;
            } else break;
        }
        comp[j+1] = key;
    }
}

// Selection Sort por prioridade (int)
void selectionSortPrioridade(Componente comp[], int n, int *comparacoes) {
    *comparacoes = 0;
    for(int i = 0; i < n-1; i++) {
        int min_idx = i;
        for(int j = i+1; j < n; j++) {
            (*comparacoes)++;
            if(comp[j].prioridade < comp[min_idx].prioridade)
                min_idx = j;
        }
        if(min_idx != i) {
            Componente temp = comp[i];
            comp[i] = comp[min_idx];
            comp[min_idx] = temp;
        }
    }
}

// ---------------- Busca Binária ---------------- //
// Apenas aplicável após ordenar por nome
int buscaBinariaPorNome(Componente comp[], int n, char nome[], int *comparacoes) {
    int esquerda = 0, direita = n-1;
    *comparacoes = 0;

    while(esquerda <= direita) {
        int meio = (esquerda + direita)/2;
        (*comparacoes)++;
        int cmp = strcmp(comp[meio].nome, nome);
        if(cmp == 0) return meio;
        else if(cmp < 0) esquerda = meio + 1;
        else direita = meio - 1;
    }
    return -1; // Não encontrado
}

// ---------------- Medir Tempo de Execução ---------------- //
double medirTempo(void (*algoritmo)(Componente[], int, int*), Componente comp[], int n, int *comparacoes) {
    clock_t inicio = clock();
    algoritmo(comp, n, comparacoes);
    clock_t fim = clock();
    return ((double)(fim - inicio)) / CLOCKS_PER_SEC;
}

// ---------------- Main ---------------- //
int main() {
    Componente componentes[MAX_COMPONENTES];
    int n;

    printf("Digite o numero de componentes (max 20): ");
    scanf("%d", &n);
    getchar(); // Limpar buffer

    if(n < 1 || n > MAX_COMPONENTES) {
        printf("Numero invalido!\n");
        return 1;
    }

    // Entrada dos componentes
    for(int i = 0; i < n; i++) {
        printf("\nComponente %d\n", i+1);
        printf("Nome: "); fgets(componentes[i].nome, sizeof(componentes[i].nome), stdin);
        componentes[i].nome[strcspn(componentes[i].nome, "\n")] = '\0'; // remover \n

        printf("Tipo: "); fgets(componentes[i].tipo, sizeof(componentes[i].tipo), stdin);
        componentes[i].tipo[strcspn(componentes[i].tipo, "\n")] = '\0';

        printf("Prioridade (1-10): "); scanf("%d", &componentes[i].prioridade);
        getchar(); // limpar buffer
    }

    int opcao;
    int comparacoes;
    Componente copia[MAX_COMPONENTES];

    do {
        printf("\nEscolha a estrategia de ordenacao:\n");
        printf("1 - Bubble Sort por Nome\n");
        printf("2 - Insertion Sort por Tipo\n");
        printf("3 - Selection Sort por Prioridade\n");
        printf("4 - Buscar componente-chave por Nome (binaria)\n");
        printf("0 - Sair\nOpcao: ");
        scanf("%d", &opcao);
        getchar();

        switch(opcao) {
            case 1:
                memcpy(copia, componentes, sizeof(Componente)*n);
                printf("\nOrdenando por Nome (Bubble Sort)...\n");
                double t1 = medirTempo(bubbleSortNome, copia, n, &comparacoes);
                mostrarComponentes(copia, n);
                printf("Comparacoes: %d, Tempo: %.6f s\n", comparacoes, t1);
                break;

            case 2:
                memcpy(copia, componentes, sizeof(Componente)*n);
                printf("\nOrdenando por Tipo (Insertion Sort)...\n");
                double t2 = medirTempo(insertionSortTipo, copia, n, &comparacoes);
                mostrarComponentes(copia, n);
                printf("Comparacoes: %d, Tempo: %.6f s\n", comparacoes, t2);
                break;

            case 3:
                memcpy(copia, componentes, sizeof(Componente)*n);
                printf("\nOrdenando por Prioridade (Selection Sort)...\n");
                double t3 = medirTempo(selectionSortPrioridade, copia, n, &comparacoes);
                mostrarComponentes(copia, n);
                printf("Comparacoes: %d, Tempo: %.6f s\n", comparacoes, t3);
                break;

            case 4:
                // Busca binária: precisa ordenar por nome primeiro
                memcpy(copia, componentes, sizeof(Componente)*n);
                bubbleSortNome(copia, n, &comparacoes); // ordenar por nome
                {
                    char chave[30];
                    printf("Digite o nome do componente-chave: ");
                    fgets(chave, sizeof(chave), stdin);
                    chave[strcspn(chave, "\n")] = '\0';

                    int idx = buscaBinariaPorNome(copia, n, chave, &comparacoes);
                    if(idx != -1) {
                        printf("Componente encontrado:\n");
                        printf("%-30s %-20s %-10d\n", copia[idx].nome, copia[idx].tipo, copia[idx].prioridade);
                        printf("Comparacoes na busca binaria: %d\n", comparacoes);
                    } else {
                        printf("Componente nao encontrado. Comparacoes: %d\n", comparacoes);
                    }
                }
                break;

            case 0: printf("Saindo...\n"); break;
            default: printf("Opcao invalida!\n"); break;
        }

    } while(opcao != 0);

    return 0;
}
