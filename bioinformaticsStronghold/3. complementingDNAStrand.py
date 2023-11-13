complement = {'A': 'T', 'C': 'G', 'G': 'C', 'T': 'A'}
print(''.join(complement[base] for base in input('')[::-1]))

