/*
Title: Finding a Shared Motif
Rosalind ID: LCSM
Rosalind #: 014
URL: http://rosalind.info/problems/lcsm
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SEQ_LENGTH 1000
#define MAX_SEQS 10

typedef struct {
    char id[50];
    char seq[MAX_SEQ_LENGTH];
} FastaEntry;

int main() {
    FILE *input_file = fopen("rosalind_lcsm.txt", "r");
    if (input_file == NULL) {
        perror("Error opening file");
        return 1;
    }

    FastaEntry entries[MAX_SEQS];
    int seq_count = 0;
    char line[MAX_SEQ_LENGTH];

    while (fgets(line, sizeof(line), input_file)) {
        if (line[0] == '>') {
            if (seq_count > 0) {
                entries[seq_count - 1].seq[strlen(entries[seq_count - 1].seq)] = '\0';
            }
            strncpy(entries[seq_count].id, line + 1, strlen(line) - 2);
            entries[seq_count].id[strlen(line) - 2] = '\0';
            seq_count++;
        } else {
            strcat(entries[seq_count - 1].seq, line);
            entries[seq_count - 1].seq[strlen(entries[seq_count - 1].seq) - 1] = '\0';
        }
    }

    fclose(input_file);

    // Encontrar la secuencia más corta
    int shortest_index = 0;
    for (int i = 1; i < seq_count; i++) {
        if (strlen(entries[i].seq) < strlen(entries[shortest_index].seq)) {
            shortest_index = i;
        }
    }

    char *shortest_sequence = entries[shortest_index].seq;
    char lcs[MAX_SEQ_LENGTH] = "";

    // Buscar el substring común más largo
    for (int length = strlen(shortest_sequence); length > 0; length--) {
        for (int start = 0; start <= strlen(shortest_sequence) - length; start++) {
            char substring[MAX_SEQ_LENGTH] = {0};
            strncpy(substring, shortest_sequence + start, length);
            substring[length] = '\0';

            int all_match = 1;
            for (int i = 0; i < seq_count; i++) {
                if (strstr(entries[i].seq, substring) == NULL) {
                    all_match = 0;
                    break;
                }
            }
            if (all_match) {
                strcpy(lcs, substring);
                break;
            }
        }
        if (strlen(lcs) > 0) {
            break;
        }
    }

    FILE *output_file = fopen("./014_LCSM.txt", "w");
    if (output_file == NULL) {
        perror("Error opening output file");
        return 1;
    }

    fprintf(output_file, "%s\n", lcs);
    fclose(output_file);

    printf("Motivo común más largo guardado en ./014_LCSM.txt\n");

    return 0;
}