/*
Title: Translating RNA into Protein
Rosalind ID: PROT
Rosalind #: 008
URL: http://rosalind.info/problems/prot
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char* codon_table[64] = {
    "F", "F", "L", "L", "S", "S", "S", "S", "Y", "Y", "*", "*", "C", "C", "*", "W",
    "L", "L", "L", "L", "P", "P", "P", "P", "H", "H", "Q", "Q", "R", "R", "R", "R",
    "I", "I", "I", "M", "T", "T", "T", "T", "N", "N", "K", "K", "S", "S", "R", "R",
    "V", "V", "V", "V", "A", "A", "A", "A", "D", "D", "E", "E", "G", "G", "G", "G"
};

int get_codon_index(const char* codon) {
    int index = 0;
    for (int i = 0; i < 3; i++) {
        index <<= 2;
        switch (codon[i]) {
            case 'U': index += 0; break;
            case 'C': index += 1; break;
            case 'A': index += 2; break;
            case 'G': index += 3; break;
            default: return -1;
        }
    }
    return index;
}

int main() {
    FILE *input_file = fopen("rosalind_prot.txt", "r");
    if (input_file == NULL) {
        perror("Error opening file");
        return 1;
    }

    char rna_sequence[1000];
    fgets(rna_sequence, sizeof(rna_sequence), input_file);
    fclose(input_file);

    rna_sequence[strcspn(rna_sequence, "\n")] = '\0';

    FILE *output_file = fopen("008_PROT.txt", "w");
    if (output_file == NULL) {
        perror("Error opening output file");
        return 1;
    }

    for (int i = 0; i < strlen(rna_sequence); i += 3) {
        char codon[4] = {0};
        strncpy(codon, rna_sequence + i, 3);
        int index = get_codon_index(codon);
        if (index == -1) {
            fprintf(stderr, "Error: Codon no valido encontrado.\n");
            fclose(output_file);
            return 1;
        }
        if (strcmp(codon_table[index], "*") == 0) {
            break;
        }
        fprintf(output_file, "%s", codon_table[index]);
    }

    fclose(output_file);
    printf("Traduccion completada. Resultado guardado en 008_PROT.txt\n");

    return 0;
}