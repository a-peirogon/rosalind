
/*
Title: Counting Point Mutations
Rosalind ID: HAMM
Rosalind #: 006
URL: http://rosalind.info/problems/hamm
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1000

int main() {
    FILE *file = fopen("rosalind_hamm.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    char seq1[MAX_LINE_LENGTH];
    char seq2[MAX_LINE_LENGTH];

    // Leer las dos secuencias
    fgets(seq1, MAX_LINE_LENGTH, file);
    fgets(seq2, MAX_LINE_LENGTH, file);

    fclose(file);

    // Eliminar saltos de línea
    seq1[strcspn(seq1, "\n")] = '\0';
    seq2[strcspn(seq2, "\n")] = '\0';

    // Verificar que las secuencias tengan la misma longitud
    if (strlen(seq1) != strlen(seq2)) {
        printf("Error: Las secuencias tienen longitudes diferentes.\n");
        return 1;
    }

    int mutations = 0;

    // Contar las diferencias
    for (int i = 0; i < strlen(seq1); i++) {
        if (seq1[i] != seq2[i]) {
            mutations++;
        }
    }

    printf("%d\n", mutations);

    return 0;
}