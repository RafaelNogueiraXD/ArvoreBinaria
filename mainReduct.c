#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bibliotecas/funcoes.h"
#include "bibliotecas/funcoesAtv.h"

int main() {
    No* raiz = NULL;
    char** VetorNomes = NULL;
    int total = 0, opcao;

    raiz = lerArquivo("../dados/AtariCSV.csv", &VetorNomes, &total);
    if (raiz == NULL) {
        liberarMemoria(VetorNomes, total);
        return 1;
    }

    do {
        menu();
        scanf("%d", &opcao);
        getchar(); // Limpar o caractere de nova linha deixado por scanf

        switch (opcao) {
        case 0:
            printf("\nFechando programa.\n");
            break;
        case 1: 
            char newGame[MAX_TAM_NOME];
            printf("\nDigite um nome: ");
            fgets(newGame, MAX_TAM_NOME, stdin);
            size_t length = strlen(newGame);
            if (newGame[length - 1] == '\n') {
                newGame[length - 1] = '\0';
            }
            inserirNo2(raiz, newGame, "vazio", "vazio", "vazio", "vazio", "vazio", "vazio");
            break;
        
        case 2:
            // Case 2
            break;
        case 3:
            // Case 3
            removerNo(raiz, "teste");
            break;
        case 4:
            if (buscarNo(raiz, "teste") != NULL)
                mostraBusca(buscarNo(raiz, "teste"));
            break;
        case 5:
            // Case 5
            break;
        case 6:
            // Case 6
            break;
        default:
            printf("\nOpcao invalida!\n");
            break;
        }
    } while (opcao != 0);


    if (buscarNo(raiz, "teste") != NULL)
        mostraBusca(buscarNo(raiz, "teste"));
    else
        printf("\nNenhum dado foi encontrado!\n");

    liberarArvore(raiz);
    liberarMemoria(VetorNomes, total);

    return 0;
}
