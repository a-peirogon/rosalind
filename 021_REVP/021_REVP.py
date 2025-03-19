'''
Title: Locating Restriction Sites
Rosalind ID: REVP
Rosalind #: 021
URL: http://rosalind.info/problems/revp
'''

from Bio import SeqIO
from Bio.Seq import Seq

with open("./rosalind_revp.txt", 'r') as f:
    seq_record = SeqIO.read(f, "fasta")
    seq = seq_record.seq

with open("./021_REVP.txt", 'w') as outhandle:
    for start in range(len(seq)):
        for end in range(len(seq), start, -1):
            if end - start < 4:
                break  # Subsegmentos más cortos no son de interés
            else:
                subseq = seq[start:end]
                if subseq == subseq.reverse_complement():
                    # longitud del palíndromo inverso
                    if 4 <= len(subseq) <= 12:
                        outhandle.write(f"{start + 1} {len(subseq)}\n")