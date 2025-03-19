'''
Title: Finding a Shared Motif
Rosalind ID: LCSM
Rosalind #: 014
URL: http://rosalind.info/problems/lcsm
'''

from Bio import SeqIO

def shortest_seq(seq):
    min_len = float('inf')
    shortest_seq = ''
    for key in seq:
        if len(seq[key]) < min_len:
            min_len = len(seq[key])
            shortest_seq = seq[key]
    return shortest_seq

def shared_motif(seq):
    s_seq = shortest_seq(seq)
    motif = set()
    for i in range(len(s_seq)):
        for j in range(i+1, len(s_seq)+1):
            motif.add(s_seq[i:j])
    for s in seq.values():
        update_motif = list(motif)
        for m in update_motif:
            if m not in s:
                motif.remove(m)
    longest_motif = max(motif, key=len)
    return longest_motif

if __name__ == "__main__":
    # Cargar datos
    seq_name, seq_string = [], []
    with open("./rosalind_lcsm.txt", 'r') as fa:
        for seq_record in SeqIO.parse(fa, 'fasta'):
            seq_name.append(str(seq_record.name))
            seq_string.append(str(seq_record.seq))
    seq = {seq_name[i]: seq_string[i] for i in range(len(seq_name))}
    
    # Encontrar el motivo común más largo
    result = shared_motif(seq)
    
    # Escribir el resultado en el archivo de salida
    with open("./014_LCSM.txt", 'w') as o:
        o.write(result)