#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned long long factorial(int n) {
    unsigned long long result = 1;
    for (int i = 2; i <= n; i++) {
        result *= i;
    }
    return result;
}

int main() {
    FILE *file;
    char filename[] = "./rosalind_pmch.txt";
    char line[1000];
    char seq[1000] = ""; // Almacenará la secuencia de ADN
    int counts[256] = {0}; // Contador de nucleótidos (ASCII)

    file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error al abrir el archivo");
        return 1;
    }

    while (fgets(line, sizeof(line), file)) {
        if (line[0] == '>') {
            continue;
        }
        line[strcspn(line, "\n")] = 0;
        strcat(seq, line);
    }
    fclose(file);

    for (int i = 0; seq[i] != '\0'; i++) {
        counts[(int)seq[i]]++;
    }

    unsigned long long pn = factorial(counts['A']) * factorial(counts['C']);

    FILE *output = fopen("./026_PMCH.txt", "w");
    if (output == NULL) {
        perror("Error al abrir el archivo de salida");
        return 1;
    }
    fprintf(output, "%llu\n", pn);
    fclose(output);

    printf("Resultado calculado y guardado en 026_PMCH.txt\n");
    return 0;
}