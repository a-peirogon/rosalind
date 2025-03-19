/*
Title: RNA Splicing
Rosalind ID: SPLC
Rosalind #: 022
URL: http://rosalind.info/problems/splc
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define MAX_SEQ_LEN 10000
#define MAX_INTRONS 100
#define MAX_INTRON_LEN 1000
#define MAX_RECORDS 200
#define MAX_LINE_LEN 1024
#define CODON_SIZE 3

typedef struct {
    char header[MAX_LINE_LEN];
    char sequence[MAX_SEQ_LEN];
} FastaRecord;

int readFasta(const char *filename, FastaRecord records[], int max_records) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Error: No se puede abrir el archivo %s\n", filename);
        return 0;
    }
    
    char line[MAX_LINE_LEN];
    int record_count = 0;
    int current_record = -1;
    int seq_pos = 0;
    
    while (fgets(line, sizeof(line), file) && record_count < max_records) {
        line[strcspn(line, "\n")] = '\0';
        
        if (line[0] == '>') {
            // Es un encabezado FASTA
            current_record++;
            record_count++;
            seq_pos = 0;
            
            strncpy(records[current_record].header, line, MAX_LINE_LEN - 1);
            records[current_record].header[MAX_LINE_LEN - 1] = '\0';
            records[current_record].sequence[0] = '\0';
        } else if (current_record >= 0) {
            // Es una línea de secuencia
            for (int i = 0; line[i]; i++) {
                if (isalpha(line[i]) && seq_pos < MAX_SEQ_LEN - 1) {
                    records[current_record].sequence[seq_pos++] = toupper(line[i]);
                }
            }
            records[current_record].sequence[seq_pos] = '\0';
        }
    }
    
    fclose(file);
    return record_count;
}

void removeSubstring(char *string, const char *substring) {
    char *match;
    int substring_len = strlen(substring);
    int string_len;
    
    while ((match = strstr(string, substring))) {
        string_len = strlen(match + substring_len);
        memmove(match, match + substring_len, string_len + 1);
    }
}

// Función para traducir un codón a un aminoácido
char translateCodon(const char *codon) {
    if (strcmp(codon, "TTT") == 0 || strcmp(codon, "TTC") == 0) return 'F'; // Fenilalanina
    if (strcmp(codon, "TTA") == 0 || strcmp(codon, "TTG") == 0 || 
        strcmp(codon, "CTT") == 0 || strcmp(codon, "CTC") == 0 || 
        strcmp(codon, "CTA") == 0 || strcmp(codon, "CTG") == 0) return 'L'; // Leucina
    if (strcmp(codon, "ATT") == 0 || strcmp(codon, "ATC") == 0 || 
        strcmp(codon, "ATA") == 0) return 'I'; // Isoleucina
    if (strcmp(codon, "ATG") == 0) return 'M'; // Metionina - Codón de inicio
    if (strcmp(codon, "GTT") == 0 || strcmp(codon, "GTC") == 0 || 
        strcmp(codon, "GTA") == 0 || strcmp(codon, "GTG") == 0) return 'V'; // Valina
    if (strcmp(codon, "TCT") == 0 || strcmp(codon, "TCC") == 0 || 
        strcmp(codon, "TCA") == 0 || strcmp(codon, "TCG") == 0 || 
        strcmp(codon, "AGT") == 0 || strcmp(codon, "AGC") == 0) return 'S'; // Serina
    if (strcmp(codon, "CCT") == 0 || strcmp(codon, "CCC") == 0 || 
        strcmp(codon, "CCA") == 0 || strcmp(codon, "CCG") == 0) return 'P'; // Prolina
    if (strcmp(codon, "ACT") == 0 || strcmp(codon, "ACC") == 0 || 
        strcmp(codon, "ACA") == 0 || strcmp(codon, "ACG") == 0) return 'T'; // Treonina
    if (strcmp(codon, "GCT") == 0 || strcmp(codon, "GCC") == 0 || 
        strcmp(codon, "GCA") == 0 || strcmp(codon, "GCG") == 0) return 'A'; // Alanina
    if (strcmp(codon, "TAT") == 0 || strcmp(codon, "TAC") == 0) return 'Y'; // Tirosina
    if (strcmp(codon, "CAT") == 0 || strcmp(codon, "CAC") == 0) return 'H'; // Histidina
    if (strcmp(codon, "CAA") == 0 || strcmp(codon, "CAG") == 0) return 'Q'; // Glutamina
    if (strcmp(codon, "AAT") == 0 || strcmp(codon, "AAC") == 0) return 'N'; // Asparagina
    if (strcmp(codon, "AAA") == 0 || strcmp(codon, "AAG") == 0) return 'K'; // Lisina
    if (strcmp(codon, "GAT") == 0 || strcmp(codon, "GAC") == 0) return 'D'; // Ácido aspártico
    if (strcmp(codon, "GAA") == 0 || strcmp(codon, "GAG") == 0) return 'E'; // Ácido glutámico
    if (strcmp(codon, "TGT") == 0 || strcmp(codon, "TGC") == 0) return 'C'; // Cisteína
    if (strcmp(codon, "TGG") == 0) return 'W'; // Triptófano
    if (strcmp(codon, "CGT") == 0 || strcmp(codon, "CGC") == 0 || 
        strcmp(codon, "CGA") == 0 || strcmp(codon, "CGG") == 0 || 
        strcmp(codon, "AGA") == 0 || strcmp(codon, "AGG") == 0) return 'R'; // Arginina
    if (strcmp(codon, "GGT") == 0 || strcmp(codon, "GGC") == 0 || 
        strcmp(codon, "GGA") == 0 || strcmp(codon, "GGG") == 0) return 'G'; // Glicina
    if (strcmp(codon, "TAA") == 0 || strcmp(codon, "TAG") == 0 || 
        strcmp(codon, "TGA") == 0) return '*'; // Codones de parada
    return 'X'; // Codón desconocido
}

void translateToStop(const char *dna, char *protein) {
    int dna_len = strlen(dna);
    int prot_index = 0;
    char codon[4];
    
    for (int i = 0; i + 2 < dna_len; i += 3) {
        codon[0] = dna[i];
        codon[1] = dna[i+1];
        codon[2] = dna[i+2];
        codon[3] = '\0';
        
        
        char aa = translateCodon(codon); // Traducir el codón a aminoácido
        
        
        if (aa == '*') {
            break; // Si es un codón de parada, terminar la traducción
        }
        
        protein[prot_index++] = aa; // Añadir el aminoácido a la proteína
    }
    
    protein[prot_index] = '\0';
}

int main() {
    FastaRecord records[MAX_RECORDS];
    int record_count;
    char dna[MAX_SEQ_LEN];
    char protein[MAX_SEQ_LEN/3 + 1];
    
    record_count = readFasta("./rosalind_splc.txt", records, MAX_RECORDS);
    if (record_count <= 1) {
        printf("Error: No se encontraron suficientes secuencias en el archivo.\n");
        return 1;
    }
    
    strcpy(dna, records[0].sequence); // La primera secuencia es el ADN
    
    
    for (int i = 1; i < record_count; i++) {
        removeSubstring(dna, records[i].sequence); // Las secuencias restantes son intrones
    }

    translateToStop(dna, protein); // Traducir el ADN sin intrones a proteína
    
    FILE *outFile = fopen("./022_SPLC.txt", "w");
    if (!outFile) {
        printf("Error: No se puede crear el archivo de salida.\n");
        return 1;
    }
    
    fprintf(outFile, "%s", protein);
    fclose(outFile);
    
    printf("La proteína ha sido guardada en el archivo 022_SPLC.txt\n");
    
    return 0;
}