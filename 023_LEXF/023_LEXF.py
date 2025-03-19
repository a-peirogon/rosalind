'''
Title: Enumerating k-mers Lexicographically
Rosalind ID: LEXF
Rosalind #: 023
URL: http://rosalind.info/problems/lexf
'''

from itertools import product

with open("./rosalind_lexf.txt", 'r') as f:
    alphabet = f.readline().rstrip().split()
    n = int(f.readline().rstrip())

with open("./023_LEXF.txt", 'w') as outhandle:
    for perm in product(alphabet, repeat=n):
        outhandle.write("".join(perm) + "\n")