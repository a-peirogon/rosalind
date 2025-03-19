/*
Title: Enumerating k-mers Lexicographically
Rosalind ID: LEXF
Rosalind #: 023
URL: http://rosalind.info/problems/lexf
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ALPHABET_SIZE 26
#define MAX_K 10

void generate_kmers(char *alphabet, int n, int k, char *current, FILE *file) {
    if (k == 0) {
        fprintf(file, "%s\n", current);
        return;
    }

    for (int i = 0; i < n; i++) {
        current[strlen(current)] = alphabet[i];
        generate_kmers(alphabet, n, k - 1, current, file);
        current[strlen(current) - 1] = '\0';
    }
}

int main() {
    FILE *input_file = fopen("rosalind_lexf.txt", "r");
    if (input_file == NULL) {
        perror("Error opening file");
        return 1;
    }

    char alphabet[MAX_ALPHABET_SIZE];
    int n = 0;
    int k;

    char line[MAX_ALPHABET_SIZE * 2];
    fgets(line, sizeof(line), input_file);
    char *token = strtok(line, " ");
    while (token != NULL) {
        alphabet[n++] = token[0];
        token = strtok(NULL, " ");
    }

    fscanf(input_file, "%d", &k);
    fclose(input_file);

    FILE *output_file = fopen("023_LEXF.txt", "w");
    if (output_file == NULL) {
        perror("Error opening output file");
        return 1;
    }

    // k-mers
    char current[MAX_K + 1] = "";
    generate_kmers(alphabet, n, k, current, output_file);

    fclose(output_file);
    printf("K-mers guardados en 023_LEXF.txt\n");

    return 0;
}