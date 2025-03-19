'''
Title: Overlap Graphs
Rosalind ID: GRPH
Rosalind #: 012
URL: http://rosalind.info/problems/grph
'''

from Bio import SeqIO

def adjacency_list(k, input_handle, output_handle):
    seqs = list(SeqIO.parse(input_handle, "fasta"))
    
    with open(output_handle, 'w') as output:
        for value in range(len(seqs)):
            for inner_value in range(len(seqs)):
                if seqs[value].seq != seqs[inner_value].seq:
                    # Verificar si las secuencias tienen superposición
                    if str(seqs[value].seq)[:k] == str(seqs[inner_value].seq)[-k:]:
                        # Guardar solo los IDs de las secuencias
                        output.write(f"{seqs[inner_value].id} {seqs[value].id}\n")

k = 3
input_handle = "./rosalind_grph.txt"
output_handle = "./012_GRPH.txt"

adjacency_list(k, input_handle, output_handle)