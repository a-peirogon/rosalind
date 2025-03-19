/*
Title: Open Reading Frames
Rosalind ID: ORF
Rosalind #: 018
URL: http://rosalind.info/problems/orf
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define MAX_SEQ_LEN 10000
#define MAX_PROTEINS 100
#define MAX_PROTEIN_LEN 1000
#define CODON_SIZE 3

// Estructura para almacenar proteínas únicas
typedef struct {
    char sequences[MAX_PROTEINS][MAX_PROTEIN_LEN];
    int count;
} ProteinSet;

void initProteinSet(ProteinSet *set) {
    set->count = 0;
}

bool proteinExists(ProteinSet *set, const char *protein) {
    for (int i = 0; i < set->count; i++) {
        if (strcmp(set->sequences[i], protein) == 0) {
            return true;
        }
    }
    return false;
}

void addProtein(ProteinSet *set, const char *protein) {
    if (!proteinExists(set, protein) && set->count < MAX_PROTEINS) {
        strcpy(set->sequences[set->count], protein);
        set->count++;
    }
}

// complementar una base nitrogenada
char complement(char nucleotide) {
    switch (nucleotide) {
        case 'A': return 'T';
        case 'T': return 'A';
        case 'G': return 'C';
        case 'C': return 'G';
        default: return nucleotide;
    }
}

void reverseComplement(const char *seq, char *result) {
    int len = strlen(seq);
    for (int i = 0; i < len; i++) {
        result[i] = complement(seq[len - i - 1]);
    }
    result[len] = '\0';
}

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

bool isStopCodon(const char *codon) {
    return (strcmp(codon, "TAA") == 0 || strcmp(codon, "TAG") == 0 || strcmp(codon, "TGA") == 0);
}

void translateToStop(const char *dna, char *protein) {
    int dnaLen = strlen(dna);
    int protIndex = 0;
    char codon[4];
    
    for (int i = 0; i + 2 < dnaLen; i += 3) {
        strncpy(codon, dna + i, 3);
        codon[3] = '\0';
        
        if (isStopCodon(codon)) {
            break;
        }
        
        // Traducir el codón a aminoácido y añadirlo a la proteína
        protein[protIndex++] = translateCodon(codon);
    }
    
    protein[protIndex] = '\0';
}

int readFasta(const char *filename, char *sequence) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Error: No se puede abrir el archivo %s\n", filename);
        return 0;
    }
    
    char line[1024];
    bool header = true;
    int seqLen = 0;
    
    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = '\0';
        
        if (line[0] == '>') {
            header = true;
            continue;
        }
        
        if (header) {
            header = false;
            seqLen = 0;
        }
        
        for (int i = 0; line[i]; i++) {
            if (isalpha(line[i])) {
                sequence[seqLen++] = toupper(line[i]);
            }
        }
    }
    
    sequence[seqLen] = '\0';
    fclose(file);
    return seqLen;
}

int main() {
    char sequence[MAX_SEQ_LEN];
    char revComp[MAX_SEQ_LEN];
    ProteinSet proteins;
    
    // Inicializar el conjunto de proteínas
    initProteinSet(&proteins);
    
    // Leer la secuencia de ADN
    if (!readFasta("./rosalind_orf.txt", sequence)) {
        return 1;
    }
    
    reverseComplement(sequence, revComp);
    
    // Procesar ambas hebras
    char *strands[2] = {sequence, revComp};
    
    for (int s = 0; s < 2; s++) {
        char *strand = strands[s];
        int strandLen = strlen(strand);
        
        for (int start = 0; start <= strandLen - 3; start++) {
            char codon[4];
            strncpy(codon, strand + start, 3);
            codon[3] = '\0';
            
            // (ATG)
            if (strcmp(codon, "ATG") == 0) {
                bool hasStopCodon = false;
                for (int i = start + 3; i <= strandLen - 3; i += 3) {
                    char stopCodon[4];
                    strncpy(stopCodon, strand + i, 3);
                    stopCodon[3] = '\0';
                    
                    if (isStopCodon(stopCodon)) {
                        hasStopCodon = true;
                        break;
                    }
                }
                
                if (hasStopCodon) {
                    char protein[MAX_PROTEIN_LEN];
                    translateToStop(strand + start, protein);
                    addProtein(&proteins, protein);
                }
            }
        }
    }
    
    FILE *outFile = fopen("./018_ORF.txt", "w");
    if (!outFile) {
        printf("Error: No se puede crear el archivo de salida\n");
        return 1;
    }
    
    for (int i = 0; i < proteins.count; i++) {
        fprintf(outFile, "%s\n", proteins.sequences[i]);
    }
    
    fclose(outFile);
    printf("Se encontraron %d proteinas unicas.\n", proteins.count);
    
    return 0;
}