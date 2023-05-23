#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TAM_NOME 1000
#define MAX_NOMES 1000
#define MAX_LINE_SIZE 1024

// Função de comparação para a ordenação
int compararNomes(const void *a, const void *b) {
    const char *nomeA = (const char *)a;
    const char *nomeB = (const char *)b;
    return strcmp(nomeA, nomeB);
}

void adicionarNome(char nomes[MAX_NOMES][MAX_TAM_NOME], int *quantidade, char *nome) {
    if (*quantidade < MAX_NOMES) {
        strcpy(nomes[*quantidade], nome);
        (*quantidade)++;
    }
}

int main() {
    FILE *arquivo;
    char linha[MAX_LINE_SIZE];
    char nomes[MAX_NOMES][MAX_TAM_NOME];
    int quantidade = 0;

    // Abre o arquivo CSV para leitura
    arquivo = fopen("../dados.csv", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    // Lê e armazena cada linha do arquivo
    while (fgets(linha, MAX_LINE_SIZE, arquivo) != NULL) {
        // Remove o caractere de nova linha (\n) do final da linha lida
        linha[strcspn(linha, "\n")] = '\0';
        if(strcmp(linha,"nome") != 0)
            adicionarNome(nomes, &quantidade, linha);
    }
    
    // Ordena os nomes em ordem alfabética
    qsort(nomes, quantidade, sizeof(nomes[0]), compararNomes);

    // Imprime os nomes ordenados
    for (int i = 0; i < quantidade; i++) {
        printf("%s\n", nomes[i]);
    }

    // Fecha o arquivo
    fclose(arquivo);

    return 0;
}
