#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bibliotecas/funcoes.h"
#include "bibliotecas/funcoesAtv.h"

int main() {
    No* raiz = NULL;
    char** VetorNomes = NULL;
    int total = 0, opcao;
    char caracter[MAX_TAM_NOME];
    raiz = lerArquivo2("../dados/arquivo.csv", &VetorNomes, &total);
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
            printf("\n\n Informe os dados do jogo: ");
            inserirNo(raiz, obterChar("nome",1), obterChar("title",1), obterChar("code",1), obterChar("Designer ou programador",1), obterChar("Ano",1), obterChar("Genero",1), obterChar("Notes",10), obterChar("link",4), obterChar("link",4));
            break;        
        case 2:
            atualizarDados(raiz, obterChar("nome",1));
            break;
        case 3:
            strcpy(caracter,obterChar("nome",1));
            removerNo(raiz, caracter);
            break;
        case 4:
            strcpy(caracter,obterChar("nome",1));
            if (buscarNo(raiz, caracter) != NULL)
                mostraBusca(buscarNo(raiz, caracter));
            else{ 
                printf("\n\tNao foi encontrado nenhum Item com esse nome 1m especifico!");
                printf("\nAqui esta uma lista do que voce quis dizer: \n");
                printf("Valores encontrados: %d", buscaPrefixo(raiz, caracter, 0));
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

    liberarArvore(raiz);
    liberarMemoria(VetorNomes, total);

    return 0;
}
