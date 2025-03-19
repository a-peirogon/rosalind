/*
Title: Inferring mRNA from Protein
Rosalind ID: MRNA
Rosalind #: 017
URL: http://rosalind.info/problems/mrna
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MODULO 1000000

// codones para un aminoácido dado
int getCodonCount(char aa) {
    switch (aa) {
        case 'F': return 2;  // Fenilalanina (UUU, UUC)
        case 'L': return 6;  // Leucina (UUA, UUG, CUU, CUC, CUA, CUG)
        case 'S': return 6;  // Serina (UCU, UCC, UCA, UCG, AGU, AGC)
        case 'Y': return 2;  // Tirosina (UAU, UAC)
        case 'C': return 2;  // Cisteína (UGU, UGC)
        case 'W': return 1;  // Triptófano (UGG)
        case 'P': return 4;  // Prolina (CCU, CCC, CCA, CCG)
        case 'H': return 2;  // Histidina (CAU, CAC)
        case 'Q': return 2;  // Glutamina (CAA, CAG)
        case 'R': return 6;  // Arginina (CGU, CGC, CGA, CGG, AGA, AGG)
        case 'I': return 3;  // Isoleucina (AUU, AUC, AUA)
        case 'M': return 1;  // Metionina (AUG)
        case 'T': return 4;  // Treonina (ACU, ACC, ACA, ACG)
        case 'N': return 2;  // Asparagina (AAU, AAC)
        case 'K': return 2;  // Lisina (AAA, AAG)
        case 'V': return 4;  // Valina (GUU, GUC, GUA, GUG)
        case 'A': return 4;  // Alanina (GCU, GCC, GCA, GCG)
        case 'D': return 2;  // Ácido aspártico (GAU, GAC)
        case 'E': return 2;  // Ácido glutámico (GAA, GAG)
        case 'G': return 4;  // Glicina (GGU, GGC, GGA, GGG)
        case '*': return 3;  // Codones de parada (UAA, UAG, UGA)
        default: return 0;   // Aminoácido desconocido
    }
}

int main() {
    FILE *file;
    char protein[10000];  // Buffer para almacenar la secuencia de proteínas
    
    file = fopen("./rosalind_mrna.txt", "r");
    if (file == NULL) {
        printf("Error al abrir el archivo\n");
        return 1;
    }
    
    if (fgets(protein, sizeof(protein), file) == NULL) {
        printf("Error al leer el archivo\n");
        fclose(file);
        return 1;
    }
    fclose(file);
    
    size_t len = strlen(protein);
    if (len > 0 && protein[len - 1] == '\n') {
        protein[len - 1] = '\0';
        len--;
    }
    
    long long result = 1;
    
    for (size_t i = 0; i < len; i++) {
        result = (result * getCodonCount(protein[i])) % MODULO;
    }
    
    // codones de parada (3)
    result = (result * getCodonCount('*')) % MODULO;
    printf("%lld\n", result);
    return 0;
}