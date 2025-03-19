'''
Title: Finding a Protein Motif
Rosalind ID: MPRT
Rosalind #: 016
URL: http://rosalind.info/problems/mprt
'''

import re
import urllib.request
from Bio import SeqIO
from io import StringIO

# Expresión regular para el motivo N-glicosilación
# N{any but P}[S or T]{any but P}
# Usamos (?=...) para permitir superposiciones
motif = re.compile('(?=N[^P][ST][^P])')

with open("./rosalind_mprt.txt", 'r') as dataset:
    protein_ids = [line.strip() for line in dataset]

uniprot_url = "http://www.uniprot.org/uniprot/"

with open("./016_MPRT.txt", 'w') as outhandle:
    for protein in protein_ids:
        try:
            # suprimir cualquier sufijo como "_HUMAN" o "_YEAST"
            clean_protein_id = protein.split('_')[0] 
            
            url = f"{uniprot_url}{clean_protein_id}.fasta"
            request = urllib.request.Request(url)
            response = urllib.request.urlopen(request)
            fasta_data = response.read().decode('utf-8')  # Decodificar los bytes a una cadena
            
            seq_record = SeqIO.read(StringIO(fasta_data), "fasta")
            seq = str(seq_record.seq)
            
            # motivo N-glicosilación
            locations = [m.start() + 1 for m in re.finditer(motif, seq)]
            if locations:
                print(protein, file=outhandle)
                print(" ".join(map(str, locations)), file=outhandle)
        except urllib.error.URLError as e:
            print(f"Error al obtener la secuencia para {protein}: {e}")
        except Exception as e:
            print(f"Error inesperado para {protein}: {e}")