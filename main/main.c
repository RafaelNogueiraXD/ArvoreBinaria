#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../bibliotecas/funcoes.h"
#include "../bibliotecas/funcoesAtv.h"
#include "../bibliotecas/busca.h"

int main() {
    Container* container = alocaContainer();
    char** VetorNomes = NULL;
    int total = 0, opcao;
    char caracter[MAX_TAM_NOME], op[MAX_TAM_NOME];
    container->arvore = lerArquivo2("../dados/customizado.csv", &VetorNomes, &total);
    if (container->arvore == NULL) {
        liberarMemoria(VetorNomes, total);
        return 1;
    }
    
    removerVazios(&container->arvore);
    do{
        limpaTela();
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
            inserirJogo(container->arvore, obterChar("nome",1), obterChar("title",1), obterChar("code",1), obterChar("Designer ou programador",1), obterChar("Ano",1), obterChar("Genero",1), obterChar("Notes",10), obterChar("link",4), obterChar("link",4));
            break;        
        case 2:
            atualizarDados(container->arvore, obterChar("nome",1));
            break;
        case 3:
            strcpy(caracter,obterChar("nome",1));

            removerJogo(container->arvore, caracter);
            break;
        case 4:
            strcpy(caracter,obterChar("nome",1));
            jogo *aux = buscarJogo(container->arvore, caracter);
            if (aux != NULL){
                mostraBusca(aux);
                printf("Deseja abrir as imagens do jogo? (1 - sim/ 2 - nao)");
                scanf("%d", &opcao);
                if(opcao == 1){
                    abrirImagem(aux->capa);
                    abrirImagem(aux->imagem);
                }
            }
            else{ 
                printf("\nAqui esta uma lista do que voce quis dizer: \n");
                printf("Valores encontrados: %d", buscaPrefixo(container->arvore, caracter, 0));
            }
           break;
        case 5:
            percorrerEmOrdem(container->arvore);
            break;
        case 6:
            exportarArvoreParaCSV(container->arvore, "../dados/customizado3.csv");
            break;
        case 7:
            addImagens(container->arvore,obterChar("nome",1));
        break;
        default:
            printf("\nOpcao invalida!\n");
            break;
        }
        if(opcao != 0){
            printf("\n\t\tPrecissone Enter para continuar !");
            getchar();
        }
    } while (opcao != 0);
    liberarArvore(container->arvore);
    liberarMemoria(VetorNomes, total);

    return 0;
}