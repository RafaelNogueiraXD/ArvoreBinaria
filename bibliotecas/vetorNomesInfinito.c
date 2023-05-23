#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NOMES 100
#define MAX_TAM_NOME 50

void lerNomes(char nomes[][MAX_TAM_NOME], int* quantidade) {
    int i = 0;

    printf("Digite os nomes (Digite 'sair' para parar):\n");

    while (i < MAX_NOMES) {
        char nome[MAX_TAM_NOME];
        fgets(nome, sizeof(nome), stdin);

        // Remove o caractere de nova linha (\n) do final do nome lido
        nome[strcspn(nome, "\n")] = '\0';

        // Verifica se o usuário digitou "sair" para parar a leitura
        if (strcmp(nome, "sair") == 0) {
            break;
        }

        strcpy(nomes[i], nome);
        i++;
    }

    *quantidade = i;
}

int main() {
    char nomes[MAX_NOMES][MAX_TAM_NOME];
    int quantidade;

    lerNomes(nomes, &quantidade);

    printf("\nNomes lidos:\n");
    for (int i = 0; i < quantidade; i++) {
        printf("%s\n", nomes[i]);
    }

    return 0;
}
