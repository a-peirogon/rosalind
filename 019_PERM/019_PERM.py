'''
Title: Enumerating Gene Orders
Rosalind ID: PERM
Rosalind #: 019
URL: http://rosalind.info/problems/perm
'''

from itertools import permutations
from math import factorial

# Definir el valor de n
n = 3
seq = range(1, n + 1)

with open("./019_PERM.txt", 'w') as o:
    o.write(f"{factorial(n)}\n")

    for perm in permutations(seq):
        o.write(" ".join(map(str, perm)))
        o.write("\n")