'''
Title: Transcribing DNA into RNA
Rosalind ID: RNA
Rosalind #: 002
URL: http://rosalind.info/problems/rna
'''
# print((input('').replace("T", "U")))

from Bio.Seq import Seq
import Bio.Alphabet
f = open('data/rosalind_rna.txt', 'r')
data = f.read().replace('\n', '')
f.close()
t = Seq(data, Bio.Alphabet.IUPAC.unambiguous_dna)
o = open('output/002_RNA.txt', 'w')
o.write(str(t.transcribe()))
o.close()
