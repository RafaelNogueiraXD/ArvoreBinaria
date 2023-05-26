No* buscarNo(No* raiz, char* chave) {
    if (raiz == NULL || strcmp(chave, raiz->chave) == 0) {
        return raiz;
    }
    if (strcmp(chave, raiz->chave) < 0) {
        return buscarNo(raiz->esquerda, chave);
    } else {
        return buscarNo(raiz->direita, chave);
    }
}
void mostraBusca(No* raiz){
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

No* encontrarMinimo(No* raiz) {
    if (raiz->esquerda == NULL) {
        return raiz;
    }
    return encontrarMinimo(raiz->esquerda);
}

// Função para remover um nó da árvore
No* removerNo(No* raiz, char* chave) {
    if (raiz == NULL) {
        return NULL;
    }

    int comparacao = strcmp(chave, raiz->chave);
    if (comparacao < 0) {
        raiz->esquerda = removerNo(raiz->esquerda, chave);
    } else if (comparacao > 0) {
        raiz->direita = removerNo(raiz->direita, chave);
    } else {
        // Caso em que encontramos o nó a ser removido

        // Se o nó não tem filhos ou apenas um filho, removemos o nó diretamente
        if (raiz->esquerda == NULL) {
            No* temp = raiz->direita;
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
            No* temp = raiz->esquerda;
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
            // Caso em que o nó a ser removido possui dois filhos
            No* minimo = encontrarMinimo(raiz->direita);
            raiz->chave = strdup(minimo->chave);
            raiz->searsTitle = strdup(minimo->searsTitle);
            raiz->code = strdup(minimo->code);
            raiz->designerOrProgrammer = strdup(minimo->designerOrProgrammer);
            raiz->year = strdup(minimo->year);
            raiz->genre = strdup(minimo->genre);
            raiz->notes = strdup(minimo->notes);
            raiz->direita = removerNo(raiz->direita, minimo->chave);
        }
    }
    return raiz;
}
void percorrerEmOrdemArquivo(No* raiz, FILE* arquivo) {
    if (raiz != NULL) {
        percorrerEmOrdemArquivo(raiz->esquerda, arquivo);
        fprintf(arquivo, "%s,%s,%s,%s,%s,%s,%s\n", raiz->chave, raiz->searsTitle, raiz->code, raiz->designerOrProgrammer, raiz->year, raiz->genre, raiz->notes);
        percorrerEmOrdemArquivo(raiz->direita, arquivo);
    }
}

void exportarArvoreParaCSV(No* raiz, const char* nomeArquivo) {
    FILE* arquivo = fopen(nomeArquivo, "w");
    if (arquivo == NULL) {
        printf("Erro ao criar o arquivo %s.\n", nomeArquivo);
        return;
    }

    percorrerEmOrdemArquivo(raiz, arquivo);

    fclose(arquivo);
    printf("Arquivo %s exportado com sucesso.\n", nomeArquivo);
}

void atualizarDados(No* raiz, char* chave) {
    char novoSearsTitle[MAX_TAM_NOME];
    char novoCode[MAX_TAM_NOME];
    char novoDesignerOrProgrammer[MAX_TAM_NOME];
    char novoYear[MAX_TAM_NOME];
    char novoGenre[MAX_TAM_NOME];
    char novoNotes[MAX_TAM_NOME];
    char novaCapa[MAX_TAM_NOME];
    char novaImagem[MAX_TAM_NOME];

    if (raiz == NULL) {
        printf("A chave fornecida nao foi encontrada na arvore.\n");
        return;
    }

    int comparacao = strcmp(chave, raiz->chave);
    if (comparacao == 0) {
        // Atualizar os dados do nó
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

        printf("Dados atualizados com sucesso para a chave: %s\n", chave);
    } else if (comparacao < 0) {
        atualizarDados(raiz->esquerda, chave);
    } else {
        atualizarDados(raiz->direita, chave);
    }
}
