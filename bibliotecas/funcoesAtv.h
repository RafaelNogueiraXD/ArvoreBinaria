jogo* buscarJogo(jogo* raiz, char* chave) {
    if (raiz == NULL || strcmp(chave, raiz->chave) == 0) {
        return raiz;
    }
    if (strcmp(chave, raiz->chave) < 0) {
        return buscarJogo(raiz->esquerda, chave);
    } else {
        return buscarJogo(raiz->direita, chave);
    }
}
void mostraBusca(jogo* raiz){
    printf("Chave: %s\n", raiz->chave);
    printf("Sears Title: %s\n", raiz->searsTitle);
    printf("Code: %s\n", raiz->code);
    printf("Designer or Programmer: %s\n", raiz->designerOrProgrammer);
    printf("Year: %s\n", raiz->year);
    printf("Genre: %s\n", raiz->genre);
    printf("Notes: %s\n\n", raiz->notes);  
    printf("Imagem de Capa: %s\n", raiz->capa);
    printf("Imagem do Jogo: %s\n",raiz->imagem);
}

jogo* encontrarMinimo(jogo* raiz) {
    if (raiz->esquerda == NULL) {
        return raiz;
    }
    return encontrarMinimo(raiz->esquerda);
}

jogo* removerJogo(jogo* raiz, char* chave) {
    if (raiz == NULL) {
        return NULL;
    }

    int comparacao = strcmp(chave, raiz->chave);
    if (comparacao < 0) {
        raiz->esquerda = removerJogo(raiz->esquerda, chave);
    } else if (comparacao > 0) {
        raiz->direita = removerJogo(raiz->direita, chave);
    } else {

        if (raiz->esquerda == NULL) {
            jogo* temp = raiz->direita;
            free(raiz->chave);
            free(raiz->searsTitle);
            free(raiz->code);
            free(raiz->designerOrProgrammer);
            free(raiz->year);
            free(raiz->genre);
            free(raiz->notes);
            free(raiz);
            return temp;
        } else if (raiz->direita == NULL) {
            jogo* temp = raiz->esquerda;
            free(raiz->chave);
            free(raiz->searsTitle);
            free(raiz->code);
            free(raiz->designerOrProgrammer);
            free(raiz->year);
            free(raiz->genre);
            free(raiz->notes);
            free(raiz);
            return temp;
        } else {
            jogo* minimo = encontrarMinimo(raiz->direita);
            raiz->chave = strdup(minimo->chave);
            raiz->searsTitle = strdup(minimo->searsTitle);
            raiz->code = strdup(minimo->code);
            raiz->designerOrProgrammer = strdup(minimo->designerOrProgrammer);
            raiz->year = strdup(minimo->year);
            raiz->genre = strdup(minimo->genre);
            raiz->notes = strdup(minimo->notes);
            raiz->direita = removerJogo(raiz->direita, minimo->chave);
        }
    }
    return raiz;
}
void percorrerEmOrdemArquivo(jogo* raiz, FILE* arquivo) {
    if (raiz != NULL) {
        percorrerEmOrdemArquivo(raiz->esquerda, arquivo);
        fprintf(arquivo, "%s,%s,%s,%s,%s,%s,%s,%s,%s\n", raiz->chave, raiz->searsTitle, raiz->code, raiz->designerOrProgrammer, raiz->year, raiz->genre, raiz->notes, raiz->capa, raiz->imagem);
        percorrerEmOrdemArquivo(raiz->direita, arquivo);
    }
}

void exportarArvoreParaCSV(jogo* raiz, const char* nomeArquivo) {
    FILE* arquivo = fopen(nomeArquivo, "w");
    if (arquivo == NULL) {
        printf("Erro ao criar o arquivo %s.\n", nomeArquivo);
        return;
    }

    percorrerEmOrdemArquivo(raiz, arquivo);

    fclose(arquivo);
    printf("Arquivo %s exportado com sucesso.\n", nomeArquivo);
}

void atualizarDados(jogo* raiz, char* chave) {
    char novoSearsTitle[MAX_TAM_NOME];
    char novoCode[MAX_TAM_NOME];
    char novoDesignerOrProgrammer[MAX_TAM_NOME];
    char novoYear[MAX_TAM_NOME];
    char novoGenre[MAX_TAM_NOME];
    char novoNotes[MAX_TAM_NOME];
    char novaCapa[MAX_TAM_NOME];
    char novaImagem[MAX_TAM_NOME];

    if (raiz == NULL) {
        printf("O nome fornecido nao foi encontrado na base de dados.\n");
        return;
    }

    int comparacao = strcmp(chave, raiz->chave);
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

        free(raiz->searsTitle);
        raiz->searsTitle = strdup(novoSearsTitle);
        free(raiz->code);
        raiz->code = strdup(novoCode);

        free(raiz->designerOrProgrammer);
        raiz->designerOrProgrammer = strdup(novoDesignerOrProgrammer);

        free(raiz->year);
        raiz->year = strdup(novoYear);

        free(raiz->genre);
        raiz->genre = strdup(novoGenre);

        free(raiz->notes);
        raiz->notes = strdup(novoNotes);

        free(raiz->capa);
        raiz->capa = strdup(novaCapa);

        free(raiz->imagem);
        raiz->imagem = strdup(novaImagem);

        printf("Dados atualizados de: %s\n", chave);
    } else if (comparacao < 0) {
        atualizarDados(raiz->esquerda, chave);
    } else {
        atualizarDados(raiz->direita, chave);
    }
}
void addImagens(jogo* raiz, char* chave) {
    char novaCapa[MAX_TAM_NOME];
    char novaImagem[MAX_TAM_NOME];

    if (raiz == NULL) {
        printf("O nome fornecido nao foi encontrado na base de dados.\n");
        return;
    }

    int comparacao = strcmp(chave, raiz->chave);
    if (comparacao == 0) {
        printf("\n\tDado encontrado, digite as imagens:");
        strcpy(novaCapa,obterChar("Link Capa",4));
        strcpy(novaImagem,obterChar("Link Imagem", 4));

        free(raiz->capa);
        raiz->capa = strdup(novaCapa);

        free(raiz->imagem);
        raiz->imagem = strdup(novaImagem);

        printf("Dados atualizados de: %s\n", chave);
    } else if (comparacao < 0) {
        addImagens(raiz->esquerda, chave);
    } else {
        addImagens(raiz->direita, chave);
    }
}
