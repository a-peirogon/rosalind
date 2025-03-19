/*
Title: Enumerating Gene Orders
Rosalind ID: PERM
Rosalind #: 019
URL: http://rosalind.info/problems/perm
*/
#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void permute(int *arr, int start, int end, FILE *file) {
    if (start == end) {
        for (int i = 0; i <= end; i++) {
            fprintf(file, "%d ", arr[i]);
        }
        fprintf(file, "\n");
    } else {
        for (int i = start; i <= end; i++) {
            swap(&arr[start], &arr[i]);
            permute(arr, start + 1, end, file);
            swap(&arr[start], &arr[i]);  // Backtrack
        }
    }
}

int factorial(int n) {
    int result = 1;
    for (int i = 2; i <= n; i++) {
        result *= i;
    }
    return result;
}

int main() {
    int n = 6;
    int seq[n];
    for (int i = 0; i < n; i++) {
        seq[i] = i + 1;
    }

    FILE *output_file = fopen("./019_PERM.txt", "w");
    if (output_file == NULL) {
        perror("Error opening file");
        return 1;
    }

    fprintf(output_file, "%d\n", factorial(n));

    permute(seq, 0, n - 1, output_file);

    fclose(output_file);
    printf("Permutaciones guardadas en 019_PERM.txt\n");

    return 0;
}