#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura de um nó da árvore
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

int main() {
    No* raiz = NULL;

    // Inserir strings na árvore
    raiz = inserirNo(raiz, "Maria", "Sears Title 1", "Code 1", "Designer 1", "2021", "Genre 1", "Notes 1");
    raiz = inserirNo(raiz, "João", "Sears Title 2", "Code 2", "Designer 2", "2022", "Genre 2", "Notes 2");
    raiz = inserirNo(raiz, "Ana", "Sears Title 3", "Code 3", "Designer 3", "2023", "Genre 3", "Notes 3");
    raiz = inserirNo(raiz, "Pedro", "Sears Title 4", "Code 4", "Designer 4", "2024", "Genre 4", "Notes 4");
    raiz = inserirNo(raiz, "Carlos", "Sears Title 5", "Code 5", "Designer 5", "2025", "Genre 5", "Notes 5");

    // Percorrer e imprimir os campos em ordem alfabética
    percorrerEmOrdem(raiz);

    // Liberar a memória ocupada pela árvore
    liberarArvore(raiz);

    return 0;
}
