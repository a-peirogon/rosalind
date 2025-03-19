'''
Title: Consensus and Profile
Rosalind ID: CONS
Rosalind #: 010
URL: http://rosalind.info/problems/cons
'''

from Bio import motifs
from Bio.Seq import Seq

with open("./rosalind_cons.txt", 'r') as f:
    raw_data = f.readlines()

motif_dict = {}
cur_key = ''

# Parsear el dataset (formato FASTA)
for i in raw_data:
    if i[0] == '>':
        cur_key = i[1:].rstrip() 
        motif_dict[cur_key] = '' 
    else:
        motif_dict[cur_key] += i.rstrip()

instances = [Seq(seq) for seq in motif_dict.values()]
m = motifs.create(instances)

profile = m.counts
consensus = m.consensus

with open("./010_CONS.txt", 'w') as o:
    o.write(str(consensus) + "\n")
    for key, value in profile.items():
        o.write(f"{key}: {' '.join(map(str, value))}\n")