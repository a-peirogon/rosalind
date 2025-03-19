'''
Title: Complementing a Strand of DNA
Rosalind ID: REVC
Rosalind #: 003
URL: http://rosalind.info/problems/revc
'''

from Bio.Seq import Seq
import Bio.Alphabet

complement = {'A': 'T', 'C': 'G', 'G': 'C', 'T': 'A'}
print(''.join(complement[base] for base in input('')[::-1]))

# f = open('data/rosalind_revc.txt', 'r')
# data = f.read().replace('\n', '')
# f.close()

# t = Seq(data, Bio.Alphabet.IUPAC.unambiguous_dna)
# o = open('output/003_REVC.txt', 'w')
# o.write(str(t.reverse_complement()))
# o.close()
