/*
Title: Locating Restriction Sites
Rosalind ID: REVP
Rosalind #: 021
URL: http://rosalind.info/problems/revp
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SEQ_LENGTH 1000

// Función para obtener el complemento inverso de una secuencia de ADN
void reverse_complement(char *seq, char *rev_comp) {
    int len = strlen(seq);
    for (int i = 0; i < len; i++) {
        switch (seq[i]) {
            case 'A': rev_comp[len - i - 1] = 'T'; break;
            case 'T': rev_comp[len - i - 1] = 'A'; break;
            case 'C': rev_comp[len - i - 1] = 'G'; break;
            case 'G': rev_comp[len - i - 1] = 'C'; break;
            default: rev_comp[len - i - 1] = seq[i]; break;
        }
    }
    rev_comp[len] = '\0';
}

int main() {
    FILE *input_file = fopen("rosalind_revp.txt", "r");
    if (input_file == NULL) {
        perror("Error opening file");
        return 1;
    }

    char line[MAX_SEQ_LENGTH];
    char seq[MAX_SEQ_LENGTH] = "";
    while (fgets(line, sizeof(line), input_file)) {
        if (line[0] != '>') {
            strcat(seq, line);
        }
    }
    fclose(input_file);

    // Eliminar el salto de línea
    seq[strcspn(seq, "\n")] = '\0';

    FILE *output_file = fopen("021_REVP.txt", "w");
    if (output_file == NULL) {
        perror("Error opening output file");
        return 1;
    }

    for (int start = 0; start < strlen(seq); start++) {
        for (int end = strlen(seq); end > start; end--) {
            int length = end - start;
            if (length < 4) break;
            if (length > 12) continue;

            char subseq[MAX_SEQ_LENGTH] = {0};
            strncpy(subseq, seq + start, length);
            subseq[length] = '\0';

            char rev_comp[MAX_SEQ_LENGTH] = {0};
            reverse_complement(subseq, rev_comp);

            if (strcmp(subseq, rev_comp) == 0) {
                fprintf(output_file, "%d %d\n", start + 1, length);
            }
        }
    }

    fclose(output_file);
    printf("Resultado guardado en 021_REVP.txt\n");

    return 0;
}