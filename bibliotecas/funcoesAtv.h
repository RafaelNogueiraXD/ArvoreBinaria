jogo* buscarJogo(jogo* arvore, char* chave) {
    if (arvore == NULL || strcmp(chave, arvore->chave) == 0) {
        return arvore;
    }
    if (strcmp(chave, arvore->chave) < 0) {
        return buscarJogo(arvore->esquerda, chave);
    } else {
        return buscarJogo(arvore->direita, chave);
    }
}
void mostraBusca(jogo* arvore){
    printf("Chave: %s\n", arvore->chave);
    printf("Sears Title: %s\n", arvore->searsTitle);
    printf("Code: %s\n", arvore->code);
    printf("Designer or Programmer: %s\n", arvore->designerOrProgrammer);
    printf("Year: %s\n", arvore->year);
    printf("Genre: %s\n", arvore->genre);
    printf("Notes: %s\n\n", arvore->notes);  
    printf("Imagem de Capa: %s\n", arvore->capa);
    printf("Imagem do Jogo: %s\n",arvore->imagem);
}

jogo* encontrarMinimo(jogo* arvore) {
    if (arvore->esquerda == NULL) {
        return arvore;
    }
    return encontrarMinimo(arvore->esquerda);
}

jogo* removerJogo(jogo* arvore, char* chave) {
    if (arvore == NULL) {
        return NULL;
    }

    int comparacao = strcmp(chave, arvore->chave);
    if (comparacao < 0) {
        arvore->esquerda = removerJogo(arvore->esquerda, chave);
    } else if (comparacao > 0) {
        arvore->direita = removerJogo(arvore->direita, chave);
    } else {

        if (arvore->esquerda == NULL) {
            jogo* temp = arvore->direita;
            free(arvore->chave);
            free(arvore->searsTitle);
            free(arvore->code);
            free(arvore->designerOrProgrammer);
            free(arvore->year);
            free(arvore->genre);
            free(arvore->notes);
            free(arvore);
            return temp;
        } else if (arvore->direita == NULL) {
            jogo* temp = arvore->esquerda;
            free(arvore->chave);
            free(arvore->searsTitle);
            free(arvore->code);
            free(arvore->designerOrProgrammer);
            free(arvore->year);
            free(arvore->genre);
            free(arvore->notes);
            free(arvore);
            return temp;
        } else {
            jogo* minimo = encontrarMinimo(arvore->direita);
            arvore->chave = strdup(minimo->chave);
            arvore->searsTitle = strdup(minimo->searsTitle);
            arvore->code = strdup(minimo->code);
            arvore->designerOrProgrammer = strdup(minimo->designerOrProgrammer);
            arvore->year = strdup(minimo->year);
            arvore->genre = strdup(minimo->genre);
            arvore->notes = strdup(minimo->notes);
            arvore->direita = removerJogo(arvore->direita, minimo->chave);
        }
    }
    return arvore;
}
void percorrerEmOrdemArquivo(jogo* arvore, FILE* arquivo) {
    if (arvore != NULL) {
        percorrerEmOrdemArquivo(arvore->esquerda, arquivo);
        fprintf(arquivo, "%s,%s,%s,%s,%s,%s,%s,%s,%s\n", arvore->chave, arvore->searsTitle, arvore->code, arvore->designerOrProgrammer, arvore->year, arvore->genre, arvore->notes, arvore->capa, arvore->imagem);
        percorrerEmOrdemArquivo(arvore->direita, arquivo);
    }
}

void exportarArvoreParaCSV(jogo* arvore, const char* nomeArquivo) {
    FILE* arquivo = fopen(nomeArquivo, "w");
    if (arquivo == NULL) {
        printf("Erro ao criar o arquivo %s.\n", nomeArquivo);
        return;
    }

    percorrerEmOrdemArquivo(arvore, arquivo);

    fclose(arquivo);
    printf("Arquivo %s exportado com sucesso.\n", nomeArquivo);
}

void atualizarDados(jogo* arvore, char* chave) {
    char novoSearsTitle[MAX_TAM_NOME];
    char novoCode[MAX_TAM_NOME];
    char novoDesignerOrProgrammer[MAX_TAM_NOME];
    char novoYear[MAX_TAM_NOME];
    char novoGenre[MAX_TAM_NOME];
    char novoNotes[MAX_TAM_NOME];
    char novaCapa[MAX_TAM_NOME];
    char novaImagem[MAX_TAM_NOME];

    if (arvore == NULL) {
        printf("O nome fornecido nao foi encontrado na base de dados.\n");
        return;
    }

    int comparacao = strcmp(chave, arvore->chave);
    if (comparacao == 0) {
        printf("\n\tDado encontrado, digite as novas informacoes:");
        strcpy(novoSearsTitle, obterChar("Titulo",1));
        strcpy(novoCode,obterChar("Codigo",1));
        strcpy(novoDesignerOrProgrammer,obterChar("Designer ou programador",1));
        strcpy(novoYear,obterChar(" Ano ",1));
        strcpy(novoGenre,obterChar("Genero",1));
        strcpy(novoNotes,obterChar("Notes", 100));
        strcpy(novaCapa,obterChar("Link Capa",4));
        strcpy(novaImagem,obterChar("Link Imagem", 4));

        free(arvore->searsTitle);
        arvore->searsTitle = strdup(novoSearsTitle);
        free(arvore->code);
        arvore->code = strdup(novoCode);

        free(arvore->designerOrProgrammer);
        arvore->designerOrProgrammer = strdup(novoDesignerOrProgrammer);

        free(arvore->year);
        arvore->year = strdup(novoYear);

        free(arvore->genre);
        arvore->genre = strdup(novoGenre);

        free(arvore->notes);
        arvore->notes = strdup(novoNotes);

        free(arvore->capa);
        arvore->capa = strdup(novaCapa);

        free(arvore->imagem);
        arvore->imagem = strdup(novaImagem);

        printf("Dados atualizados de: %s\n", chave);
    } else if (comparacao < 0) {
        atualizarDados(arvore->esquerda, chave);
    } else {
        atualizarDados(arvore->direita, chave);
    }
}
void addImagens(jogo* arvore, char* chave) {
    char novaCapa[MAX_TAM_NOME];
    char novaImagem[MAX_TAM_NOME];

    if (arvore == NULL) {
        printf("O nome fornecido nao foi encontrado na base de dados.\n");
        return;
    }

    int comparacao = strcmp(chave, arvore->chave);
    if (comparacao == 0) {
        printf("\n\tDado encontrado, digite as imagens:");
        strcpy(novaCapa,obterChar("Link Capa",4));
        strcpy(novaImagem,obterChar("Link Imagem", 4));

        free(arvore->capa);
        arvore->capa = strdup(novaCapa);

        free(arvore->imagem);
        arvore->imagem = strdup(novaImagem);

        printf("Dados atualizados de: %s\n", chave);
    } else if (comparacao < 0) {
        addImagens(arvore->esquerda, chave);
    } else {
        addImagens(arvore->direita, chave);
    }
}
void abrirImagem(char *string){
    char* str_path_e_nome_da_imagem = string;
    char* str_arg = (char*)malloc(256);
    
    #ifdef _WIN32 // Verificar se está executando no Windows
        strcpy(str_arg, "explorer "); // No Windows: abrir arquivo com o programa padrão
    #else
        strcpy(str_arg, "xdg-open "); // No Linux: abrir arquivo com o programa padrão
    #endif
    
    strcat(str_arg, str_path_e_nome_da_imagem);
    system(str_arg);
    
    free(str_arg);
}
