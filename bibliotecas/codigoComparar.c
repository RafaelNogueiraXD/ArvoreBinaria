#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Função de comparação para qsort
int comparar_nomes(const void* a, const void* b) {
    const char** nome1 = (const char**)a;
    const char** nome2 = (const char**)b;
    return strcmp(*nome1, *nome2);
}

int main() {
    char* nomes[] = {"Maria", "João", "Ana", "Pedro", "Carlos"};
    int num_nomes = sizeof(nomes) / sizeof(nomes[0]);

    // Ordena a lista de nomes
    qsort(nomes, num_nomes, sizeof(nomes[0]), comparar_nomes);
    // Imprime os nomes ordenados
    for (int i = 0; i < num_nomes; i++) {
        printf("%s\n", nomes[i]);
    }

    return 0;
}
