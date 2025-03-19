#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int* longest_increasing_subsequence(int arr[], int n, int* length) {
    // L[i] = longitud de la LIS terminando en arr[i]
    int* L = (int*)malloc(n * sizeof(int));
    int* prev = (int*)malloc(n * sizeof(int));
    
    for (int i = 0; i < n; i++) {
        L[i] = 1;
        prev[i] = -1;
    }
    
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (arr[i] > arr[j] && L[i] < L[j] + 1) {
                L[i] = L[j] + 1;
                prev[i] = j;
            }
        }
    }
    
    int longest_idx = 0;
    for (int i = 1; i < n; i++) {
        if (L[i] > L[longest_idx]) {
            longest_idx = i;
        }
    }
    
    *length = L[longest_idx];
    
    int* result = (int*)malloc(*length * sizeof(int));
    int curr_idx = longest_idx;
    int curr_pos = *length - 1;
    
    while (curr_idx >= 0) {
        result[curr_pos] = arr[curr_idx];
        curr_idx = prev[curr_idx];
        curr_pos--;
    }
    
    free(L);
    free(prev);
    
    return result;
}

int* longest_decreasing_subsequence(int arr[], int n, int* length) {
    // L[i] = longitud de la LDS terminando en arr[i]
    int* L = (int*)malloc(n * sizeof(int));
    int* prev = (int*)malloc(n * sizeof(int));
    
    for (int i = 0; i < n; i++) {
        L[i] = 1;
        prev[i] = -1;
    }
    
    // Construir L[] y prev[]
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (arr[i] < arr[j] && L[i] < L[j] + 1) {
                L[i] = L[j] + 1;
                prev[i] = j;
            }
        }
    }
    
    int longest_idx = 0;
    for (int i = 1; i < n; i++) {
        if (L[i] > L[longest_idx]) {
            longest_idx = i;
        }
    }
    
    *length = L[longest_idx];
    
    int* result = (int*)malloc(*length * sizeof(int));
    int curr_idx = longest_idx;
    int curr_pos = *length - 1;
    
    while (curr_idx >= 0) {
        result[curr_pos] = arr[curr_idx];
        curr_idx = prev[curr_idx];
        curr_pos--;
    }
    
    free(L);
    free(prev);
    
    return result;
}

int main() {
    FILE *fp_in, *fp_out;
    int n;
    int *permutation;
    
    fp_in = fopen("rosalind_lgis.txt", "r");
    if (fp_in == NULL) {
        printf("Error.\n");
        return 1;
    }
    
    // Leer n
    fscanf(fp_in, "%d", &n);
    
    // Asignar memoria para la permutación
    permutation = (int*)malloc(n * sizeof(int));
    
    // Leer la permutación
    for (int i = 0; i < n; i++) {
        fscanf(fp_in, "%d", &permutation[i]);
    }
    
    fclose(fp_in);
    
    // Encontrar subsecuencias más largas
    int inc_length, dec_length;
    int *increasing = longest_increasing_subsequence(permutation, n, &inc_length);
    int *decreasing = longest_decreasing_subsequence(permutation, n, &dec_length);
    
    // Abrir archivo de salida
    fp_out = fopen("024_LGIS.txt", "w");
    if (fp_out == NULL) {
        printf("Error.\n");
        free(permutation);
        free(increasing);
        free(decreasing);
        return 1;
    }
    
    // Escribir subsecuencia creciente
    for (int i = 0; i < inc_length; i++) {
        fprintf(fp_out, "%d ", increasing[i]);
        printf("%d ", increasing[i]);
    }
    fprintf(fp_out, "\n");
    printf("\n");
    
    // Escribir subsecuencia decreciente
    for (int i = 0; i < dec_length; i++) {
        fprintf(fp_out, "%d ", decreasing[i]);
        printf("%d ", decreasing[i]);
    }
    fprintf(fp_out, "\n");
    printf("\n");
    
    // Cerrar archivo y liberar memoria
    fclose(fp_out);
    free(permutation);
    free(increasing);
    free(decreasing);
    
    return 0;
}