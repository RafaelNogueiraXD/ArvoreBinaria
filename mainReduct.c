#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bibliotecas/funcoes.h"
#include "bibliotecas/funcoesAtv.h"
#include "bibliotecas/busca.h"
int main() {
    jogo* raiz = NULL;
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
        printf("\n\t escolha: "); 
        scanf("%d", &opcao);
        getchar(); 
        switch (opcao) {
        case 0:
            printf("\nFechando programa.\n");
            break;
        case 1: 
            printf("\n\n Informe os dados do jogo: ");
            inserirJogo(raiz, obterChar("nome",1), obterChar("title",1), obterChar("code",1), obterChar("Designer ou programador",1), obterChar("Ano",1), obterChar("Genero",1), obterChar("Notes",10), obterChar("link",4), obterChar("link",4));
            break;        
        case 2:
            atualizarDados(raiz, obterChar("nome",1));
            break;
        case 3:
            strcpy(caracter,obterChar("nome",1));

            removerJogo(raiz, caracter);
            break;
        case 4:
            strcpy(caracter,obterChar("nome",1));
            if (buscarJogo(raiz, caracter) != NULL)
                mostraBusca(buscarJogo(raiz, caracter));
            else{ 
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
        case 7:
            addImagens(raiz,obterChar("nome",1));
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
