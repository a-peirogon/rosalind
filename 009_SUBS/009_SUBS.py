'''
Title: Finding a Motif in DNA
Rosalind ID: SUBS
Rosalind #: 009
URL: http://rosalind.info/problems/subs
'''

from Bio import motifs
from Bio.Seq import Seq

with open("./rosalind_subs.txt", 'r') as f:
    raw_seq = f.readline().rstrip()
    motif = f.readline().rstrip()

instances = [Seq(motif)]
m = motifs.create(instances)

seq = Seq(raw_seq)

locations = []
for pos in m.instances.search(seq):
    locations.append(pos[0] + 1)  # Ajustar a 1-based numbering

with open("./009_SUBS.txt", 'w') as o:
    o.write(" ".join(map(str, locations)))