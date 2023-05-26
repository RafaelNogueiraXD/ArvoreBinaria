
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

typedef struct jogo {
    char* chave;
    char* searsTitle;
    char* code;
    char* designerOrProgrammer;
    char* year;
    char* genre;
    char* notes;
    char *capa;
    char *imagem;
    struct jogo* esquerda;
    struct jogo* direita;
} jogo;

jogo* addJogo(char* chave, char* searsTitle, char* code, char* designerOrProgrammer, char* year, char* genre, char* notes, char* capa, char * imagem) {
    jogo* novoNo = (jogo*)malloc(sizeof(jogo));
    novoNo->chave = strdup(chave);
    novoNo->searsTitle = strdup(searsTitle);
    novoNo->code = strdup(code);
    novoNo->designerOrProgrammer = strdup(designerOrProgrammer);
    novoNo->year = strdup(year);
    novoNo->genre = strdup(genre);
    novoNo->notes = strdup(notes);
    novoNo->capa = strdup(capa);
    novoNo->imagem = strdup(imagem);
    novoNo->esquerda = NULL;
    novoNo->direita = NULL;
    return novoNo;
}

jogo* inserirJogo(jogo* raiz, char* chave, char* searsTitle, char* code, char* designerOrProgrammer, char* year, char* genre, char* notes, char*capa, char *imagem) {
    if (raiz == NULL) {
        return addJogo(chave, searsTitle, code, designerOrProgrammer, year, genre, notes, capa, imagem);
    }

    int comparacao = strcmp(chave, raiz->chave);
    if (comparacao < 0) {
        raiz->esquerda = inserirJogo(raiz->esquerda, chave, searsTitle, code, designerOrProgrammer, year, genre, notes, capa, imagem);
    } else if (comparacao > 0) {
        raiz->direita = inserirJogo(raiz->direita, chave, searsTitle, code, designerOrProgrammer, year, genre, notes, capa , imagem);
    }

    return raiz;
}

void percorrerEmOrdem(jogo* raiz) {
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

void liberarArvore(jogo* raiz) {
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
    printf("\nOpcoes: \n");
    printf("\n\t 0 - Fechar programa");
    printf("\n\t 1 - Cadastrar novos itens.");
    printf("\n\t 2 - Atualizar determinado item");
    printf("\n\t 3 - Remover item");
    printf("\n\t 4 - Consultar por item");
    printf("\n\t 5 - Vizualizar todos os itens item");
    printf("\n\t 6 - exportar informacoes");
    printf("\n\t 7 - adicionar imagem");
}
jogo* lerArquivo2(char* nomeArquivo, char*** VetorNomes, int* total) {
    FILE* file = fopen(nomeArquivo, "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return NULL;
    }
    printf("\nAchamos o arquivo %s!\n", nomeArquivo);

    jogo* raiz = NULL;
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

        for (int i = columnCount; i < MAX_COLUMNS; i++) {
            columns[i] = "vazio";
        }

        if (strcmp(columns[0], "Acid Drop") == 0 && strcmp(nomeArquivo, "../dados/arquivo.csv") != 0)
            troca = 1;

        if (troca == 0)
            raiz = inserirJogo(raiz, columns[0], columns[1], columns[2], columns[3], columns[4], columns[5], columns[6], columns[7], columns[8]);
        else
            raiz = inserirJogo(raiz, columns[0], "Vazio", "Vazio", columns[1], columns[3], columns[4], columns[5], "vazio", "vazio");
    }

    fclose(file);
    return raiz;
}

jogo* lerArquivo(char* nomeArquivo, char*** VetorNomes, int* total) {
    FILE* file = fopen(nomeArquivo, "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return NULL;
    }
    printf("\n Achamos o arquivo!\n");

    jogo* raiz = NULL;
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
            raiz = inserirJogo(raiz, columns[0], columns[1], columns[2], columns[3], columns[4], columns[5], columns[6], "vazio", "vazio");
        else
            raiz = inserirJogo(raiz, columns[0], "Vazio", "Vazio", columns[1], columns[3], columns[4], columns[5], "vazio", "vazio");
    }

    fclose(file);
    return raiz;
}
int buscaPrefixo(jogo* raiz, char prefixo[], int achado) {
    if (raiz == NULL) {
        return achado;
    }
    int comparacao = strncmp(prefixo, raiz->chave, strlen(prefixo));
    if (comparacao == 0) {
        printf("%s\n", raiz->chave);
        achado++;
    }
    if (comparacao <= 0) {
        achado = buscaPrefixo(raiz->esquerda, prefixo, achado);
    }
    if (comparacao >= 0) {
        achado = buscaPrefixo(raiz->direita, prefixo, achado);
    }
    return achado;
}



void liberarMemoria(char** VetorNomes, int total) {
    for (int i = 0; i < total; i++) {
        free(VetorNomes[i]);
    }
    free(VetorNomes);
}
char* obterChar(char *anunciado, int tamanho) {
    char* newGame = (char*)malloc((tamanho * MAX_TAM_NOME) * sizeof(char));
    printf("\nDigite um %s: ", anunciado);
    fgets(newGame, MAX_TAM_NOME, stdin);
    fflush(stdin);
    size_t length = strlen(newGame);
    if (newGame[length - 1] == '\n') {
        newGame[length - 1] = '\0';
    }
    return newGame;
}

void menuBuscas(){
    printf("\n Voce pode pesquisar por: ");
    printf("\n\t 1 - Nome");
    printf("\n\t 2 - SearsTitle");
    printf("\n\t 3 - Code");
    printf("\n\t 4 - Designer ou Programmer");
    printf("\n\t 5 - Ano");
    printf("\n\t 6 - Genero");
    printf("\n\t 7 - Notes");
    printf("\n\t 8 - Capa");
    printf("\n\t 9 - Imagem");
}