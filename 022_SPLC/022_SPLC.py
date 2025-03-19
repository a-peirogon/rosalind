'''
Title: RNA Splicing
Rosalind ID: SPLC
Rosalind #: 022
URL: http://rosalind.info/problems/splc
'''

from Bio import SeqIO
from Bio.Seq import Seq

with open("./rosalind_splc.txt", 'r') as f:
    records = list(SeqIO.parse(f, "fasta"))

dna = str(records[0].seq)
introns = [str(record.seq) for record in records[1:]]

for intron in introns:
    dna = dna.replace(intron, "") # Eliminar los intrones del ADN

protein = Seq(dna).translate(to_stop=True )# Traducir el ADN a proteína
with open("./022_SPLC.txt", 'w') as o:
    o.write(str(protein))