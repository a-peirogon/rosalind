/*
Title: Overlap Graphs
Rosalind ID: GRPH
Rosalind #: 012
URL: http://rosalind.info/problems/grph
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SEQ_LENGTH 1000
#define MAX_ID_LENGTH 100
#define MAX_SEQUENCES 1000
#define K 3

typedef struct {
    char id[MAX_ID_LENGTH];
    char sequence[MAX_SEQ_LENGTH];
    int length;
} Sequence;

int read_fasta_sequences(const char* filename, Sequence* sequences) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening input file");
        return -1;
    }

    char line[MAX_SEQ_LENGTH];
    int seq_count = -1;
    
    while (fgets(line, sizeof(line), file)) {
        size_t len = strlen(line);
        if (len > 0 && line[len-1] == '\n') {
            line[len-1] = '\0';
            len--;
        }
        
        if (line[0] == '>') {
            seq_count++;
            if (seq_count >= MAX_SEQUENCES) {
                fprintf(stderr, "Demasiadas secuencias en el archivo\n");
                fclose(file);
                return -1;
            }
            
            // Extraer solo el ID (sin el símbolo >)
            strncpy(sequences[seq_count].id, line + 1, MAX_ID_LENGTH - 1);
            sequences[seq_count].id[MAX_ID_LENGTH - 1] = '\0';
            sequences[seq_count].sequence[0] = '\0';
            sequences[seq_count].length = 0;
        } else if (seq_count >= 0) {
            strcat(sequences[seq_count].sequence, line);
            sequences[seq_count].length = strlen(sequences[seq_count].sequence);
        }
    }
    
    fclose(file);
    return seq_count + 1;
}

void create_adjacency_list(Sequence* sequences, int seq_count, const char* output_filename) {
    FILE* outfile = fopen(output_filename, "w");
    if (outfile == NULL) {
        perror("Error opening output file");
        return;
    }
    
    for (int i = 0; i < seq_count; i++) {
        for (int j = 0; j < seq_count; j++) {
            // Verificar que no sea la misma secuencia
            if (strcmp(sequences[i].sequence, sequences[j].sequence) != 0) {
                // Verificar la superposición
                int len_i = sequences[i].length;
                int len_j = sequences[j].length;
                
                // Si ambas secuencias tienen al menos K caracteres
                if (len_i >= K && len_j >= K) {
                    // Verificar si los últimos K caracteres de i son iguales a los primeros K de j
                    if (strncmp(sequences[i].sequence + len_i - K, sequences[j].sequence, K) == 0) {
                        fprintf(outfile, "%s %s\n", sequences[i].id, sequences[j].id);
                    }
                }
            }
        }
    }
    
    fclose(outfile);
}

int main() {
    Sequence sequences[MAX_SEQUENCES];
    const char* input_filename = "./rosalind_grph.txt";
    const char* output_filename = "./012_GRPH.txt";
    
    int seq_count = read_fasta_sequences(input_filename, sequences);
    if (seq_count <= 0) {
        fprintf(stderr, "Resultado guardado en 012_GRPH.txt\n");
        return 1;
    }
    
    create_adjacency_list(sequences, seq_count, output_filename);
    
    return 0;
}