'''
Title: Counting Point Mutations
Rosalind ID: HAMM
Rosalind #: 006
URL: http://rosalind.info/problems/hamm
'''

f = open("./rosalind_hamm.txt", 'r')
raw_data = f.readlines()
f.close()

# Eliminar saltos de línea y espacios en blanco
seq1 = raw_data[0].strip()
seq2 = raw_data[1].strip()

# Verificar que las secuencias tengan la misma longitud
if len(seq1) != len(seq2):
    print("Error: Las secuencias tienen longitudes diferentes.")
    exit(1)

mutations = 0  # Inicializar contador de mutaciones

# Iterar a través de las secuencias y contar las diferencias
for i in range(len(seq1)):
    if seq1[i] != seq2[i]:
        mutations += 1

print(mutations)