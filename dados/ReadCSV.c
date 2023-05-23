#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1000
#define MAX_COLUMNS 10

int main() {
    FILE *file;
    char line[MAX_LINE_LENGTH];
    char *token;
    char *columns[MAX_COLUMNS];
    char **VetorNomes = NULL; // Alteração: Usar um ponteiro duplo para alocar memória dinamicamente
    int columnCount = 0;
    int total = 0;

    // Abre o arquivo CSV para leitura
    file = fopen("../AtariCSV.csv", "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    // Lê cada linha do arquivo
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
    }

    // Imprime os nomes armazenados em VetorNomes
    for (int i = 0; i < total; i++) {
        printf("%s\n", VetorNomes[i]);
    }

    // Libera a memória alocada
    for (int i = 0; i < total; i++) {
        free(VetorNomes[i]);
    }
    free(VetorNomes);

    // Fecha o arquivo
    fclose(file);

    return 0;
}
