#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bibliotecas/funcoes.h"
#include "bibliotecas/funcoesAtv.h"
char* obterNomeJogo() {
    char* newGame = (char*)malloc(MAX_TAM_NOME * sizeof(char));
    printf("\nDigite um nome: ");
    fgets(newGame, MAX_TAM_NOME, stdin);
    fflush(stdin);
    size_t length = strlen(newGame);
    if (newGame[length - 1] == '\n') {
        newGame[length - 1] = '\0';
    }
    return newGame;
}

int main() {
    No* raiz = NULL;
    char** VetorNomes = NULL;
    int total = 0, opcao;
    char caracter[MAX_TAM_NOME],c2[MAX_TAM_NOME],c3[MAX_TAM_NOME],c4[MAX_TAM_NOME],c5[MAX_TAM_NOME],c6[MAX_TAM_NOME],c7[MAX_TAM_NOME*100];
    raiz = lerArquivo("../dados/AtariCSV.csv", &VetorNomes, &total);
    if (raiz == NULL) {
        liberarMemoria(VetorNomes, total);
        return 1;
    }
    do{
        menu(); 
        scanf("%d", &opcao);
        getchar(); // Limpar o caractere de nova linha deixado por scanf

        switch (opcao) {
        case 0:
            printf("\nFechando programa.\n");
            break;
        case 1: 
            strcpy(caracter,obterNomeJogo());
            inserirNo(raiz, caracter, "vazio", "vazio", "vazio", "vazio", "vazio", "vazio", "vazio", "vazio");
            break;        
        case 2:
            //atualiar um item 
            break;
        case 3:
            strcpy(caracter,obterNomeJogo());
            removerNo(raiz, "teste");
            break;
        case 4:
            strcpy(caracter,obterNomeJogo());
            if (buscarNo(raiz, caracter) != NULL)
                mostraBusca(buscarNo(raiz, caracter));
            else{ 
                printf("\n\tNao foi encontrado nenhum Item com esse nome especifico!");
                printf("\nAqui esta uma lista do que voce quis dizer: \n");
                printf("Valores encontrados: %d", buscaPrefixo(raiz, caracter));
            } 
           break;
        case 5:
            percorrerEmOrdem(raiz);
            break;
        case 6:
            exportarArvoreParaCSV(raiz, "../dados/arquivo.csv");
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
