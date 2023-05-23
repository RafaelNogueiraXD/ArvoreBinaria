#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bibliotecas/funcoes.h"
#include "bibliotecas/funcoesAtv.h"
#define MAX_LINE_LENGTH 1000
#define MAX_COLUMNS 10

No* lerArquivo(char* nomeArquivo, char*** VetorNomes, int* total) {
    FILE* file = fopen(nomeArquivo, "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return NULL;
    }
    printf("\n Achamos o arquivo!\n");

    No* raiz = NULL;
    char line[MAX_LINE_LENGTH];
    char *token;
    char *columns[MAX_COLUMNS];
    int columnCount = 0;
    int troca = 0;

    while (fgets(line, sizeof(line), file) != NULL) {
        token = strtok(line, ",");
        columnCount = 0;

        while (token != NULL && columnCount < MAX_COLUMNS) {
            columns[columnCount] = token;
            columnCount++;
            token = strtok(NULL, ",");
        }

        *VetorNomes = realloc(*VetorNomes, (*total + 1) * sizeof(char*));
        (*VetorNomes)[*total] = malloc(strlen(columns[0]) + 1);
        strcpy((*VetorNomes)[*total], columns[0]);
        (*total)++;

        if (strcmp(columns[0], "Acid Drop") == 0)
            troca = 1;

        if (troca == 0)
            raiz = inserirNo(raiz, columns[0], columns[1], columns[2], columns[3], columns[4], columns[5], columns[6]);
        else
            raiz = inserirNo(raiz, columns[0], "Vazio", "Vazio", columns[1], columns[3], columns[4], columns[5]);
    }

    fclose(file);
    return raiz;
}

void liberarMemoria(char** VetorNomes, int total) {
    for (int i = 0; i < total; i++) {
        free(VetorNomes[i]);
    }
    free(VetorNomes);
}

int main() {
    No* raiz = NULL;
    char** VetorNomes = NULL;
    int total = 0;

    raiz = lerArquivo("../dados/AtariCSV.csv", &VetorNomes, &total);
    if (raiz == NULL) {
        liberarMemoria(VetorNomes, total);
        return 1;
    }
    inserirNo2(raiz, "teste", NULL, NULL, NULL, NULL, NULL, NULL);
    if(buscarNo(raiz,"teste") != NULL)
        mostraBusca(buscarNo(raiz,"teste"));
    removerNo(raiz,"teste");  
    if(buscarNo(raiz,"teste") != NULL)
        mostraBusca(buscarNo(raiz,"teste"));
    else printf("\nNenhum dado foi encontrado!");

    liberarArvore(raiz);
    liberarMemoria(VetorNomes, total);

    return 0;
}
