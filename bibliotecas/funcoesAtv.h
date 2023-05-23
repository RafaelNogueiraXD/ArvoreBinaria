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
}
No* inserirNo2(No* raiz, char* chave, char* searsTitle, char* code, char* designerOrProgrammer, char* year, char* genre, char* notes) {
    if (raiz == NULL) {
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

    int comparacao = strcmp(chave, raiz->chave);
    if (comparacao < 0) {
        raiz->esquerda = inserirNo2(raiz->esquerda, chave, searsTitle, code, designerOrProgrammer, year, genre, notes);
    } else if (comparacao > 0) {
        raiz->direita = inserirNo2(raiz->direita, chave, searsTitle, code, designerOrProgrammer, year, genre, notes);
    }

    return raiz;
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
