'''
Title: Longest Increasing Subsequence
Rosalind ID: LGIS
Rosalind #: 024
URL: http://rosalind.info/problems/lgis/
'''
def longest_increasing_subsequence(arr):
    """
    Encuentra la subsecuencia creciente más larga y devuelve los índices
    utilizando el algoritmo de programación dinámica.
    """
    n = len(arr)
    # L[i] = longitud de la LIS terminando en arr[i]
    L = [1] * n
    prev = [-1] * n
    
    for i in range(1, n):
        for j in range(0, i):
            if arr[i] > arr[j] and L[i] < L[j] + 1:
                L[i] = L[j] + 1
                prev[i] = j
    
    longest_idx = 0
    for i in range(1, n):
        if L[i] > L[longest_idx]:
            longest_idx = i
    
    result = []
    while longest_idx >= 0:
        result.append(arr[longest_idx])
        longest_idx = prev[longest_idx]
    
    return result[::-1]


def longest_decreasing_subsequence(arr):
    """
    Encuentra la subsecuencia decreciente más larga utilizando el mismo algoritmo
    que para la creciente pero con comparación invertida.
    """
    n = len(arr)
    L = [1] * n
    prev = [-1] * n
    
    for i in range(1, n):
        for j in range(0, i):
            if arr[i] < arr[j] and L[i] < L[j] + 1:
                L[i] = L[j] + 1
                prev[i] = j
    
    longest_idx = 0
    for i in range(1, n):
        if L[i] > L[longest_idx]:
            longest_idx = i
    
    result = []
    while longest_idx >= 0:
        result.append(arr[longest_idx])
        longest_idx = prev[longest_idx]
    
    return result[::-1]


with open("rosalind_lgis.txt", "r") as f:
    lines = f.readlines()
    n = int(lines[0].strip())
    permutation = list(map(int, lines[1].strip().split()))

increasing = longest_increasing_subsequence(permutation)
decreasing = longest_decreasing_subsequence(permutation)

with open("024_LGIS.txt", "w") as f:
    f.write(" ".join(map(str, increasing)) + "\n")
    f.write(" ".join(map(str, decreasing)) + "\n")

print(" ".join(map(str, increasing)))
print(" ".join(map(str, decreasing)))