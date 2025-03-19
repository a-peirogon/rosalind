'''
Title: Independent Alleles
Rosalind ID: LIA
Rosalind #: 015
URL: http://rosalind.info/problems/lia
'''

import math

def prob_het(k, N):
    ''' 
    Calcula la probabilidad de que al menos N organismos sean AaBb después de k generaciones.
    '''
    prob_AaBb = 4 / 16.0  # Probabilidad de que un organismo sea AaBb

    prob = []
    total = 2 ** k  # Número total de organismos en la generación k
    # Suma de la función de probabilidad binomial general
    for r in range(N, total + 1):
        prob.append(nCr(total, r) * (prob_AaBb ** r) * ((1 - prob_AaBb) ** (total - r)))
    return sum(prob)

def nCr(n, r):
    f = math.factorial
    return f(n) // f(r) // f(n - r)

if __name__ == "__main__":
    with open("./rosalind_lia.txt", 'r') as f:
        k, N = map(int, f.readline().strip().split())
    
    result = prob_het(k, N)
    
    print(f"{result:.6f}")