/*
Title: Independent Alleles
Rosalind ID: LIA
Rosalind #: 015
URL: http://rosalind.info/problems/lia
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

long long factorial(int n) {
    long long result = 1;
    for (int i = 2; i <= n; i++) {
        result *= i;
    }
    return result;
}

long long nCr(int n, int r) {
    return factorial(n) / (factorial(r) * factorial(n - r));
}

// Función para calcular la probabilidad
double prob_het(int k, int N) {
    double prob_AaBb = 4.0 / 16.0;
    double prob = 0.0;
    int total = pow(2, k);

    for (int r = N; r <= total; r++) {
        prob += nCr(total, r) * pow(prob_AaBb, r) * pow(1 - prob_AaBb, total - r);
    }

    return prob;
}

int main() {
    FILE *input_file = fopen("rosalind_lia.txt", "r");
    if (input_file == NULL) {
        perror("Error opening file");
        return 1;
    }

    int k, N;
    fscanf(input_file, "%d %d", &k, &N);
    fclose(input_file);

    double result = prob_het(k, N);

    printf("%.6f\n", result);

    return 0;
}