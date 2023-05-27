jogo* buscas(jogo* raiz, char* nomeCampo, int categoria) {
    if (raiz == NULL) {
        return NULL;
    }

    int comparacao = 0;

    switch (categoria) {
        case 1:
            comparacao = strcmp(nomeCampo, raiz->chave);
            break;
        case 2:
            comparacao = strcmp(nomeCampo, raiz->searsTitle);
            break;
        case 3:
            comparacao = strcmp(nomeCampo, raiz->code);
            break;
        case 4:
            comparacao = strcmp(nomeCampo, raiz->designerOrProgrammer);
            break;
        case 5:
            comparacao = strcmp(nomeCampo, raiz->year);
            break;
        case 6:
            comparacao = strcmp(nomeCampo, raiz->genre);
            break;
        case 7:
            comparacao = strcmp(nomeCampo, raiz->notes);
            break;
        case 8:
            comparacao = strcmp(nomeCampo, raiz->capa);
            break;
        case 9:
            comparacao = strcmp(nomeCampo, raiz->imagem);
            break;
        default:
            return NULL;
    }

    if (comparacao == 0) {
        return raiz;
    } else if (comparacao < 0) {
        return buscas(raiz->esquerda, nomeCampo, categoria);
    } else {
        return buscas(raiz->direita, nomeCampo, categoria);
    }
}
void removerVazios(jogo** arvore) {
    printf("tentando remover o vazio:  ");
    char caracter[4]; // Certifique-se de ter espaço suficiente para armazenar o prefixo
    strcpy(caracter, "vaz");
    jogo* aux2 = buscaPrefixoNo(*arvore, caracter, 0);
    while (aux2 != NULL) {
        printf("tentando achar e remover. . .");
        *arvore = removerJogo(*arvore, aux2->chave);
        // Atualize o valor de caracter para um novo prefixo
        aux2 = buscaPrefixoNo(*arvore, caracter, 0);
    }
}
