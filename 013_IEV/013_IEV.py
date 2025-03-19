'''
Title: Calculating Expected Offspring
Rosalind ID: IEV
Rosalind #: 013
URL: http://rosalind.info/problems/iev
'''

# Leer los datos del archivo
with open("./rosalind_iev.txt", 'r') as f:
    data = list(map(int, f.readline().rstrip().split()))
probabilities = [1.0, 1.0, 1.0, 0.75, 0.5, 0.0]
expected_dominant = sum(data[i] * probabilities[i] * 2 for i in range(6))

print(expected_dominant)