
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
    int height;
    struct jogo* esquerda;
    struct jogo* direita;
} jogo;

typedef struct{
        jogo* arvore;
}Container;
Container *alocaContainer(){
    Container *container = (Container*) malloc(sizeof(Container));
    container->arvore = NULL;
    return container;
}
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
    novoNo->height = 1;
    novoNo->esquerda = NULL;
    novoNo->direita = NULL;
    return novoNo;
}
int max(int a, int b) {
    return (a > b) ? a : b;
}
int height(jogo* node) {
    if (node == NULL) {
        return 0;
    }
    return node->height;
}
int balanceamento(jogo* node) {
    if (node == NULL) {
        return 0;
    }
    return height(node->esquerda) - height(node->direita);
}
jogo* rotaDireita(jogo* y) {
    jogo* x = y->esquerda;
    jogo* T2 = x->direita;

    x->direita = y;
    y->esquerda = T2;

    y->height = 1 + max(height(y->esquerda), height(y->direita));
    x->height = 1 + max(height(x->esquerda), height(x->direita));

    return x;
}
jogo* rotaEsquerda(jogo* x) {
    jogo* y = x->direita;
    jogo* T2 = y->esquerda;

    y->esquerda = x;
    x->direita = T2;

    x->height = 1 + max(height(x->esquerda), height(x->direita));
    y->height = 1 + max(height(y->esquerda), height(y->direita));

    return y;
}

jogo* inserirJogo(jogo* root, char* chave, char* searsTitle, char* code, char* designerOrProgrammer, char* year, char* genre, char* notes, char* capa, char* imagem) {
    if (root == NULL) {
        return addJogo(chave, searsTitle, code, designerOrProgrammer, year, genre, notes, capa, imagem);
    }

    int cmp = strcmp(chave, root->chave);

    if (cmp < 0) {
        root->esquerda = inserirJogo(root->esquerda, chave, searsTitle, code, designerOrProgrammer, year, genre, notes, capa, imagem);
    }
    else if (cmp > 0) {
        root->direita = inserirJogo(root->direita, chave, searsTitle, code, designerOrProgrammer, year, genre, notes, capa, imagem);
    }
    else {
        return root;
    }

    root->height = 1 + max(height(root->esquerda), height(root->direita));

    int balance = balanceamento(root);

    if (balance > 1 && strcmp(chave, root->esquerda->chave) < 0) {
        return rotaDireita(root);
    }

    if (balance < -1 && strcmp(chave, root->direita->chave) > 0) {
        return rotaEsquerda(root);
    }

    if (balance > 1 && strcmp(chave, root->esquerda->chave) > 0) {
        root->esquerda = rotaEsquerda(root->esquerda);
        return rotaDireita(root);
    }

    if (balance < -1 && strcmp(chave, root->direita->chave) < 0) {
        root->direita = rotaDireita(root->direita);
        return rotaEsquerda(root);
    }

    return root;
}
void percorrerEmOrdem(jogo* arvore) {
    if (arvore != NULL) {
        percorrerEmOrdem(arvore->esquerda);
        printf("Chave: %s\n", arvore->chave);
        printf("Sears Title: %s\n", arvore->searsTitle);
        printf("Code: %s\n", arvore->code);
        printf("Designer or Programmer: %s\n", arvore->designerOrProgrammer);
        printf("Year: %s\n", arvore->year);
        printf("Genre: %s\n", arvore->genre);
        printf("Notes: %s\n\n", arvore->notes);
        percorrerEmOrdem(arvore->direita);
    }
}

void liberarArvore(jogo* arvore) {
    if (arvore != NULL) {
        liberarArvore(arvore->esquerda);
        liberarArvore(arvore->direita);
        free(arvore->chave);
        free(arvore->searsTitle);
        free(arvore->code);
        free(arvore->designerOrProgrammer);
        free(arvore->year);
        free(arvore->genre);
        free(arvore->capa);
        free(arvore->imagem);
        free(arvore->notes);
        free(arvore);
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

    jogo* arvore = NULL;
    char line[MAX_LINE_LENGTH];
    char *token;
    char *coluna[MAX_COLUMNS];
    int contador = 0;
    int troca = 0;

    while (fgets(line, sizeof(line), file) != NULL) {
        token = strtok(line, ",");
        contador = 0;
        if (token == NULL) {
            continue; // Pular para a próxima iteração do loop externo
        }
        while (token != NULL && contador < MAX_COLUMNS) {
            coluna[contador] = token;
            contador++;
            token = strtok(NULL, ",");
        }

        *VetorNomes = realloc(*VetorNomes, (*total + 1) * sizeof(char*));
        (*VetorNomes)[*total] = malloc(strlen(coluna[0]) + 1);
        strcpy((*VetorNomes)[*total], coluna[0]);
        (*total)++;

        for (int i = contador; i < MAX_COLUMNS; i++) {
            coluna[i] = "vazio";
        }

        // if (strcmp(coluna[0], "Acid Drop") == 0 && strcmp(nomeArquivo, "../dados/customizado.csv") != 0)
        //     troca = 1;
        if(strcmp(coluna[0], "vazio") == 0 || strcmp(coluna[0], "Vazio") == 0)continue;
        else{
            if (troca == 0)
                arvore = inserirJogo(arvore, coluna[0], coluna[1], coluna[2], coluna[3], coluna[4], coluna[5], coluna[6], coluna[7], coluna[8]);
            else
                arvore = inserirJogo(arvore, coluna[0], "Vazio", "Vazio", coluna[1], coluna[3], coluna[4], coluna[5], "vazio", "vazio");
        }
    }

    fclose(file);
    return arvore;
}

jogo* lerArquivo(char* nomeArquivo, char*** VetorNomes, int* total) {
    FILE* file = fopen(nomeArquivo, "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return NULL;
    }
    printf("\n Achamos o arquivo!\n");

    jogo* arvore = NULL;
    char line[MAX_LINE_LENGTH];
    char *token;
    char *coluna[MAX_COLUMNS];
    int contador = 0;
    int troca = 0;

    while (fgets(line, sizeof(line), file) != NULL) {
        token = strtok(line, ",");
        contador = 0;

        while (token != NULL && contador < MAX_COLUMNS) {
            coluna[contador] = token;
            contador++;
            token = strtok(NULL, ",");
        }

        *VetorNomes = realloc(*VetorNomes, (*total + 1) * sizeof(char*));
        (*VetorNomes)[*total] = malloc(strlen(coluna[0]) + 1);
        strcpy((*VetorNomes)[*total], coluna[0]);
        (*total)++;
        if (strcmp(coluna[0], "Acid Drop") == 0)
            troca = 1;
        if (troca == 0)
            arvore = inserirJogo(arvore, coluna[0], coluna[1], coluna[2], coluna[3], coluna[4], coluna[5], coluna[6], "vazio", "vazio");
        else
            arvore = inserirJogo(arvore, coluna[0], "Vazio", "Vazio", coluna[1], coluna[3], coluna[4], coluna[5], "vazio", "vazio");
    }

    fclose(file);
    return arvore;
}
int buscaPrefixo(jogo* arvore, char prefixo[], int achado) {
    if (arvore == NULL) {
        return achado;
    }
    int comparacao = strncmp(prefixo, arvore->chave, strlen(prefixo));
    if (comparacao == 0) {
        printf("%s\n", arvore->chave);
        achado++;
    }
    if (comparacao <= 0) {
        achado = buscaPrefixo(arvore->esquerda, prefixo, achado);
    }
    if (comparacao >= 0) {
        achado = buscaPrefixo(arvore->direita, prefixo, achado);
    }
    return achado;
}
jogo* buscaPrefixoNo(jogo* arvore, char prefixo[], int achado) {
    if (arvore == NULL) {
        return NULL;
    }
    int comparacao = strncmp(prefixo, arvore->chave, strlen(prefixo));
    if (comparacao == 0) {
        return arvore;
    }
    if (comparacao < 0) {
        return buscaPrefixoNo(arvore->esquerda, prefixo, achado);
    }
    if (comparacao > 0) {
        return buscaPrefixoNo(arvore->direita, prefixo, achado);
    }
    return NULL; // Retorna NULL se o prefixo não for encontrado
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
void limpaTela(){
    #ifdef __linux__
        system("clear");
    #elif _WIN32
        system("cls");
    #else
    #endif
}


