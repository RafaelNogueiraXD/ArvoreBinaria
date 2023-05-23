
// Função de comparação para qsort
/*para usar basta por qsort(listanomes, tamanhoLista, sizeof(nomes[0]), comparar_nomes); */
#define MAX_TAM_NOME 100
#define MAX_NOMES 200
#define MAX_LINE_SIZE 1024
#define MAX_LINE_LENGTH 1000
#define MAX_COLUMNS 10
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
void menu(){
    int op;
    printf("\nOpcoes: \n");
    printf("\n\t 0 - Fechar programa");
    printf("\n\t 1 - Cadastrar novos itens.");
    printf("\n\t 2 - Atualizar determinado item");
    printf("\n\t 3 - Remover item");
    printf("\n\t 4 - Consultar por item");
    printf("\n\t 5 - Vizualizar um item");
    printf("\n\t 6 - exportar informacoes");
 
}

No* lerArquivo(char* nomeArquivo, char*** VetorNomes, int* total) {
    FILE* file = fopen(nomeArquivo, "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return NULL;
    }
    printf("\n Achamos o arquivo!\n");

    No* raiz = NULL;
    char line[MAX_LINE_LENGTH];
    char *token;
    char *columns[MAX_COLUMNS];
    int columnCount = 0;
    int troca = 0;

    while (fgets(line, sizeof(line), file) != NULL) {
        token = strtok(line, ",");
        columnCount = 0;

        while (token != NULL && columnCount < MAX_COLUMNS) {
            columns[columnCount] = token;
            columnCount++;
            token = strtok(NULL, ",");
        }

        *VetorNomes = realloc(*VetorNomes, (*total + 1) * sizeof(char*));
        (*VetorNomes)[*total] = malloc(strlen(columns[0]) + 1);
        strcpy((*VetorNomes)[*total], columns[0]);
        (*total)++;

        if (strcmp(columns[0], "Acid Drop") == 0)
            troca = 1;

        if (troca == 0)
            raiz = inserirNo(raiz, columns[0], columns[1], columns[2], columns[3], columns[4], columns[5], columns[6]);
        else
            raiz = inserirNo(raiz, columns[0], "Vazio", "Vazio", columns[1], columns[3], columns[4], columns[5]);
    }

    fclose(file);
    return raiz;
}

void liberarMemoria(char** VetorNomes, int total) {
    for (int i = 0; i < total; i++) {
        free(VetorNomes[i]);
    }
    free(VetorNomes);
}
