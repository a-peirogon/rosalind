'''
Title: Translating RNA into Protein
Rosalind ID: PROT
Rosalind #: 008
URL: http://rosalind.info/problems/prot
'''

from Bio.Seq import Seq

with open("./rosalind_prot.txt", 'r') as f:
    rna_sequence = f.read().replace('\n', '')

seq = Seq(rna_sequence)
protein = seq.translate(to_stop=True)

with open("./008_PROT.txt", 'w') as o:
    o.write(str(protein))