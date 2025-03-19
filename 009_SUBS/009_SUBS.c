/*
Title: Finding a Motif in DNA
Rosalind ID: SUBS
Rosalind #: 009
URL: http://rosalind.info/problems/subs
*/

#include <stdio.h>
#include <string.h>

#define MAX_SEQ_LENGTH 1000

int main() {
    FILE *input_file = fopen("rosalind_subs.txt", "r");
    if (input_file == NULL) {
        perror("Error opening file");
        return 1;
    }

    char sequence[MAX_SEQ_LENGTH];
    char motif[MAX_SEQ_LENGTH];
    fgets(sequence, MAX_SEQ_LENGTH, input_file);
    fgets(motif, MAX_SEQ_LENGTH, input_file);
    fclose(input_file);

    // Eliminar el salto de línea
    sequence[strcspn(sequence, "\n")] = '\0';
    motif[strcspn(motif, "\n")] = '\0';

    FILE *output_file = fopen("009_SUBS.txt", "w");
    if (output_file == NULL) {
        perror("Error opening output file");
        return 1;
    }

    int motif_length = strlen(motif);
    int first = 1;

    for (int i = 0; i <= strlen(sequence) - motif_length; i++) {
        if (strncmp(sequence + i, motif, motif_length) == 0) {
            if (!first) {
                fprintf(output_file, " ");
            }
            fprintf(output_file, "%d", i + 1);  // 1-based numbering
            first = 0;
        }
    }

    fclose(output_file);
    printf("Posiciones del motivo guardadas en 009_SUBS.txt\n");

    return 0;
}