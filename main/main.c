#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../bibliotecas/funcoes.h"
#include "../bibliotecas/funcoesAtv.h"
#include "../bibliotecas/busca.h"
void imprimiGraphviz(jogo* root){
    FILE *arq = fopen("graph.txt","a");
    if (root->direita != NULL){
        fprintf(arq," %s -> %s \n", root->chave, root->direita->chave);
        imprimiGraphviz(root->direita);
    }
    if (root->esquerda != NULL){
        fprintf(arq," %s -> %s \n", root->chave, root->esquerda->chave);
        imprimiGraphviz(root->esquerda);
    }  
}
void printLevelOrder(jogo* root) {
    if (root == NULL) {
        return;
    }
    FILE *arq = fopen("graph.txt","w");
    jogo** queue = (jogo**)malloc(100 * sizeof(jogo*));
    int front = 0;
    int rear = 0;
    int levelCount = 0;
    int currentLevelCount = 1;
    int nextLevelCount = 0;
    char color[100];

    printf("Nível 1: ");
    queue[rear++] = root;
    fprintf(arq,"\n node [style=filled];\n");
        

    // A [fillcolor=red];
    // B [fillcolor=green];
    // C [fillcolor=blue];
    // D [fillcolor=yellow];

    while (front < rear) {
        jogo* current = queue[front++];
        printf("%s ", current->chave);
        switch (levelCount)
        {
        case 1:
            strcpy(arq,"red");  
            break;
        
        default:
            break;
        }
        fprintf(arq,"%s [filled=%s]", current->chave, color);
        currentLevelCount--;

        if (current->esquerda != NULL) {
            queue[rear++] = current->esquerda;
            nextLevelCount++;
        }
        if (current->direita != NULL) {
            queue[rear++] = current->direita;
            nextLevelCount++;
        }

        if (currentLevelCount == 0) {
            levelCount++;
            currentLevelCount = nextLevelCount;
            nextLevelCount = 0;
            if (currentLevelCount > 0) {
                printf("\nNível %d: ", levelCount + 1);
                if(levelCount == 2)strcpy(color, "red");
                if(levelCount == 3)strcpy(color, "yellow");
                if(levelCount == 4)strcpy(color, "purple");
                if(levelCount == 5)strcpy(color, "green");
                if(levelCount == 6)strcpy(color, "blue");
                if(levelCount == 7)strcpy(color, "pink");
                if(levelCount == 8)strcpy(color, "");
            }
        }
    }

    printf("\n");

    free(queue);
}
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
        case 8:
            imprimiGraphviz(container->arvore);
            printLevelOrder(container->arvore);
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
