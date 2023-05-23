#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bibliotecas/funcoes.h"
// Estrutura de um nó da árvoreh
#define MAX_LINE_LENGTH 1000
#define MAX_COLUMNS 10

int main() {
    No* raiz = NULL;
    FILE *file;
    char line[MAX_LINE_LENGTH];
    char *token;
    char *columns[MAX_COLUMNS];
    char **VetorNomes = NULL; // Alteração: Usar um ponteiro duplo para alocar memória dinamicamente
    int columnCount = 0, troca = 0;
    int total = 0;
    file = fopen("../dados/AtariCSV.csv", "r");
    if (file == NULL){
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }else printf("\n Achamos o arquivo!\n");
     while (fgets(line, sizeof(line), file) != NULL) {
        // Divide a linha em colunas usando a vírgula como delimitador
        token = strtok(line, ",");
        columnCount = 0;

        while (token != NULL && columnCount < MAX_COLUMNS) {
            columns[columnCount] = token;
            columnCount++;
            token = strtok(NULL, ",");
        }

        // Aloca memória para VetorNomes e copia os nomes
        VetorNomes = realloc(VetorNomes, (total + 1) * sizeof(char*));
        VetorNomes[total] = malloc(strlen(columns[0]) + 1); // +1 para o caractere nulo
        strcpy(VetorNomes[total], columns[0]);
        total++;

        if(strcmp(columns[0],"Acid Drop") == 0)troca = 1;
        
        if(troca == 0)
            raiz = inserirNo(raiz, columns[0], columns[1], columns[2], columns[3], columns[4], columns[5], columns[6]);
        else    
            raiz = inserirNo(raiz, columns[0], "Vazio", "Vazio", columns[1], columns[3], columns[4], columns[5]);
            // raiz = inserirNo(raiz, columns[0], columns[3], columns[1], columns[4], columns[4], columns[5], columns[6]);
    }
    // Percorrer e imprimir as strings em ordem alfabética
    percorrerEmOrdem(raiz);
    // Liberar a memória ocupada pela árvore    
    liberarArvore(raiz);
    for (int i = 0; i < total; i++) {
        free(VetorNomes[i]);
    }
    free(VetorNomes);

    // Fecha o arquivo
    fclose(file);

    return 0;
}
