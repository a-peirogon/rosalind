/*
Title: Calculating Protein Mass
Rosalind ID: PRTM
Rosalind #: 020
URL: http://rosalind.info/problems/prtm
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// masas monoisotópicas
double aa_mass_dict[26] = {
    ['A' - 'A'] = 71.03711,
    ['C' - 'A'] = 103.00919,
    ['D' - 'A'] = 115.02694,
    ['E' - 'A'] = 129.04259,
    ['F' - 'A'] = 147.06841,
    ['G' - 'A'] = 57.02146,
    ['H' - 'A'] = 137.05891,
    ['I' - 'A'] = 113.08406,
    ['K' - 'A'] = 128.09496,
    ['L' - 'A'] = 113.08406,
    ['M' - 'A'] = 131.04049,
    ['N' - 'A'] = 114.04293,
    ['P' - 'A'] = 97.05276,
    ['Q' - 'A'] = 128.05858,
    ['R' - 'A'] = 156.10111,
    ['S' - 'A'] = 87.03203,
    ['T' - 'A'] = 101.04768,
    ['V' - 'A'] = 99.06841,
    ['W' - 'A'] = 186.07931,
    ['Y' - 'A'] = 163.06333
};

int main() {
    FILE *input_file = fopen("rosalind_prtm.txt", "r");
    if (input_file == NULL) {
        perror("Error opening file");
        return 1;
    }

    char protein[1000];
    fscanf(input_file, "%s", protein);
    fclose(input_file);

    double mw = 0.0;
    for (int i = 0; i < strlen(protein); i++) {
        mw += aa_mass_dict[protein[i] - 'A'];
    }

    printf("%.3f\n", mw);

    return 0;
}