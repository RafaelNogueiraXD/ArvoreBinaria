
// Função de comparação para qsort
/*para usar basta por qsort(listanomes, tamanhoLista, sizeof(nomes[0]), comparar_nomes); */
#define MAX_TAM_NOME 100
#define MAX_NOMES 200
#define MAX_LINE_SIZE 1024
int comparar_nomes(const void* a, const void* b) {  
    const char** nome1 = (const char**)a;
    const char** nome2 = (const char**)b;
    return strcmp(*nome1, *nome2);
}


void lerNomes(char nomes[MAX_NOMES][MAX_TAM_NOME], int *quantidade, char *nome) {
    if (*quantidade < MAX_NOMES) {
        strcpy(nomes[*quantidade], nome);
        (*quantidade)++;
    }
}

typedef struct No {
    char* chave;
    char* searsTitle;
    char* code;
    char* designerOrProgrammer;
    char* year;
    char* genre;
    char* notes;
    struct No* esquerda;
    struct No* direita;
} No;

// Função para criar um novo nó
No* criarNo(char* chave, char* searsTitle, char* code, char* designerOrProgrammer, char* year, char* genre, char* notes) {
    No* novoNo = (No*)malloc(sizeof(No));
    novoNo->chave = strdup(chave);
    novoNo->searsTitle = strdup(searsTitle);
    novoNo->code = strdup(code);
    novoNo->designerOrProgrammer = strdup(designerOrProgrammer);
    novoNo->year = strdup(year);
    novoNo->genre = strdup(genre);
    novoNo->notes = strdup(notes);
    novoNo->esquerda = NULL;
    novoNo->direita = NULL;
    return novoNo;
}

// Função para inserir um nó na árvore
No* inserirNo(No* raiz, char* chave, char* searsTitle, char* code, char* designerOrProgrammer, char* year, char* genre, char* notes) {
    if (raiz == NULL) {
        return criarNo(chave, searsTitle, code, designerOrProgrammer, year, genre, notes);
    }

    int comparacao = strcmp(chave, raiz->chave);
    if (comparacao < 0) {
        raiz->esquerda = inserirNo(raiz->esquerda, chave, searsTitle, code, designerOrProgrammer, year, genre, notes);
    } else if (comparacao > 0) {
        raiz->direita = inserirNo(raiz->direita, chave, searsTitle, code, designerOrProgrammer, year, genre, notes);
    }

    return raiz;
}

// Função para percorrer a árvore em ordem alfabética
void percorrerEmOrdem(No* raiz) {
    if (raiz != NULL) {
        percorrerEmOrdem(raiz->esquerda);
        printf("Chave: %s\n", raiz->chave);
        printf("Sears Title: %s\n", raiz->searsTitle);
        printf("Code: %s\n", raiz->code);
        printf("Designer or Programmer: %s\n", raiz->designerOrProgrammer);
        printf("Year: %s\n", raiz->year);
        printf("Genre: %s\n", raiz->genre);
        printf("Notes: %s\n\n", raiz->notes);
        percorrerEmOrdem(raiz->direita);
    }
}

// Função para liberar a memória ocupada pela árvore
void liberarArvore(No* raiz) {
    if (raiz != NULL) {
        liberarArvore(raiz->esquerda);
        liberarArvore(raiz->direita);
        free(raiz->chave);
        free(raiz->searsTitle);
        free(raiz->code);
        free(raiz->designerOrProgrammer);
        free(raiz->year);
        free(raiz->genre);
        free(raiz->notes);
        free(raiz);
    }
}
