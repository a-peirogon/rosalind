'''
Title: Counting DNA Nucleotides
Rosalind ID: DNA
Rosalind #: 001
URL: http://rosalind.info/problems/dna
'''
from collections import Counter
print(" ".join("{}".format(v) for k, v in sorted(Counter(input('')).items())))
