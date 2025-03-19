/*
Title: Mendel's First Law
Rosalind ID: IPRB
Rosalind #: 007
URL: http://rosalind.info/problems/iprb
*/

#include <stdio.h>
#include <stdlib.h>

// Función para calcular la probabilidad de que la descendencia tenga un alelo dominante
double prob_dom(int k, int m, int n) {
    double k_d = (double)k;
    double m_d = (double)m;
    double n_d = (double)n;
    double t = k_d + m_d + n_d;  // Población total

    // Probabilidades de seleccionar cada tipo de individuo
    double pk = k_d / t;  // Probabilidad de seleccionar un AA
    double pm = m_d / t;  // Probabilidad de seleccionar un Aa
    double pn = n_d / t;  // Probabilidad de seleccionar un aa

    // Probabilidad máxima (1) menos las probabilidades de obtener un individuo aa
    double prob = 1.0;

    // Restar la probabilidad de que ambos padres sean aa
    prob -= pn * ((n_d - 1) / (t - 1));

    // Restar la probabilidad de que un padre sea aa y el otro sea Aa (dos escenarios)
    prob -= 2 * pn * (m_d / (t - 1)) * 0.5;

    // Restar la probabilidad de que ambos padres sean Aa
    prob -= pm * ((m_d - 1) / (t - 1)) * 0.25;

    return prob;
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Uso: %s k m n\n", argv[0]);
        return 1;
    }

    // Leer los valores de k, m, n desde la línea de comandos
    int k = atoi(argv[1]);
    int m = atoi(argv[2]);
    int n = atoi(argv[3]);

    // Calcular la probabilidad
    double result = prob_dom(k, m, n);
    printf("Probabilidad de que la descendencia tenga un alelo dominante: %.5f\n", result);

    return 0;
}