/*
Title: Consensus and Profile
Rosalind ID: CONS
Rosalind #: 010
URL: http://rosalind.info/problems/cons
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DNA_LENGTH 1000
#define MAX_SEQUENCES 100

int find_seq_length(char sequences[MAX_SEQUENCES][MAX_DNA_LENGTH], int num_sequences) {
    return strlen(sequences[0]);
}

void calculate_profile_and_consensus(char sequences[MAX_SEQUENCES][MAX_DNA_LENGTH], 
                                     int profile[4][MAX_DNA_LENGTH], 
                                     char consensus[MAX_DNA_LENGTH], 
                                     int num_sequences, 
                                     int seq_length) {
    int i, j;
    
    memset(profile, 0, sizeof(int) * 4 * MAX_DNA_LENGTH);
    
    for (i = 0; i < num_sequences; i++) {
        for (j = 0; j < seq_length; j++) {
            switch(sequences[i][j]) {
                case 'A': profile[0][j]++; break;
                case 'C': profile[1][j]++; break;
                case 'G': profile[2][j]++; break;
                case 'T': profile[3][j]++; break;
            }
        }
    }
    
    for (j = 0; j < seq_length; j++) {
        int max_count = -1;
        int max_nucleotide = 0;
        
        for (i = 0; i < 4; i++) {
            if (profile[i][j] > max_count) {
                max_count = profile[i][j];
                max_nucleotide = i;
            }
        }
        
        switch(max_nucleotide) {
            case 0: consensus[j] = 'A'; break;
            case 1: consensus[j] = 'C'; break;
            case 2: consensus[j] = 'G'; break;
            case 3: consensus[j] = 'T'; break;
        }
    }
    consensus[seq_length] = '\0';
}

int main() {
    FILE *input_file = fopen("./rosalind_cons.txt", "r");
    FILE *output_file = fopen("./010_CONS.txt", "w");
    
    if (input_file == NULL || output_file == NULL) {
        perror("Error opening file");
        return 1;
    }
    
    char line[MAX_DNA_LENGTH];
    char sequences[MAX_SEQUENCES][MAX_DNA_LENGTH];
    int num_sequences = 0;
    int current_sequence = -1;
    
    // Leer el archivo FASTA
    while (fgets(line, sizeof(line), input_file)) {
        int len = strlen(line);
        if (len > 0 && line[len-1] == '\n') {
            line[len-1] = '\0';
            len--;
        }
        
        if (line[0] == '>') {
            // Nueva secuencia
            current_sequence++;
            num_sequences++;
            sequences[current_sequence][0] = '\0';
        } else {
            // Añadir a la secuencia actual
            strcat(sequences[current_sequence], line);
        }
    }
    
    int seq_length = find_seq_length(sequences, num_sequences);
    int profile[4][MAX_DNA_LENGTH];
    char consensus[MAX_DNA_LENGTH];
    
    calculate_profile_and_consensus(sequences, profile, consensus, num_sequences, seq_length);
    
    fprintf(output_file, "%s\n", consensus);
    fprintf(output_file, "A: ");
    for (int j = 0; j < seq_length; j++) {
        fprintf(output_file, "%d ", profile[0][j]);
    }
    fprintf(output_file, "\nC: ");
    for (int j = 0; j < seq_length; j++) {
        fprintf(output_file, "%d ", profile[1][j]);
    }
    fprintf(output_file, "\nG: ");
    for (int j = 0; j < seq_length; j++) {
        fprintf(output_file, "%d ", profile[2][j]);
    }
    fprintf(output_file, "\nT: ");
    for (int j = 0; j < seq_length; j++) {
        fprintf(output_file, "%d ", profile[3][j]);
    }
    fprintf(output_file, "\n");
    
    fclose(input_file);
    fclose(output_file);
    
    return 0;
}