'''
Title: Inferring mRNA from Protein
Rosalind ID: MRNA
Rosalind #: 017
URL: http://rosalind.info/problems/mrna
'''

from Bio.SeqUtils.CodonUsage import SynonymousCodons
from Bio.SeqUtils import seq1

with open("./rosalind_mrna.txt", 'r') as f:
    protein = f.readline().rstrip()

# dic codones sinónimos
codonTable = {}
for key in SynonymousCodons.keys():
    # seq1
    codonTable[seq1(key)] = len(SynonymousCodons[key])

# combinaciones posibles de ARNm
aa_comb = 1
for aa in protein:
    aa_comb *= codonTable[aa]

result = (aa_comb * 3) % 1000000
print(result)