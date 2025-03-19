'''
Title: Open Reading Frames
Rosalind ID: ORF
Rosalind #: 018
URL: http://rosalind.info/problems/orf
'''

from Bio import SeqIO
from Bio.Data import CodonTable

with open("./rosalind_orf.txt", 'r') as f:
    record = SeqIO.read(f, "fasta")

standard_table = CodonTable.unambiguous_dna_by_name["Standard"]
stop_codons = standard_table.stop_codons

def chunker(seq, size):
    return (seq[pos:pos + size] for pos in range(0, len(seq), size))

proteins = set()

for strand in [record.seq, record.seq.reverse_complement()]:
    # menos de 3 nucleótidos
    for start in range(len(strand) - 2):
        start_codon = str(strand[start:start + 3])
        # verificar codón de inicio
        if start_codon == "ATG":
            frame = str(strand[start:])
            # codón de parada en el marco de lectura
            if any(st in chunker(frame[3:], 3) for st in stop_codons):
                prot = str(strand[start:].translate(to_stop=True))
                proteins.add(prot)

with open("./018_ORF.txt", 'w') as outhandle:
    outhandle.write("\n".join(proteins))