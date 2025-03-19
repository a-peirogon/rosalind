/*
Title: Calculating Expected Offspring
Rosalind ID: IEV
Rosalind #: 013
URL: http://rosalind.info/problems/iev
*/

#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *input_file = fopen("rosalind_iev.txt", "r");
    if (input_file == NULL) {
        perror("Error opening file");
        return 1;
    }

    int data[6];
    for (int i = 0; i < 6; i++) {
        fscanf(input_file, "%d", &data[i]);
    }

    fclose(input_file);

    double probabilities[6] = {1.0, 1.0, 1.0, 0.75, 0.5, 0.0};
    double expected_dominant = 0.0;

    for (int i = 0; i < 6; i++) {
        expected_dominant += data[i] * probabilities[i] * 2;
    }

    printf("%.6f\n", expected_dominant);

    return 0;
}