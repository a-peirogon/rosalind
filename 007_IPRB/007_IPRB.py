'''
Title: Mendel's First Law
Rosalind ID: IPRB
Rosalind #: 007
URL: http://rosalind.info/problems/iprb
'''

# k: número de individuos homocigotos dominantes (AA)
# m: número de individuos heterocigotos (Aa)
# n: número de individuos homocigotos recesivos (aa)

''' 
Probabilidad de que dos organismos aleatorios se apareen y produzcan un individuo
con un alelo dominante (es decir, que no sea aa)
'''

def prob_dom(k, m, n):
    # Convertir a flotante para evitar divisiones enteras
    k, m, n = map(float, (k, m, n))
    t = k + m + n  # Población total

    # Probabilidades de seleccionar cada tipo de individuo
    pk = k / t  # Probabilidad de seleccionar un AA
    pm = m / t  # Probabilidad de seleccionar un Aa
    pn = n / t  # Probabilidad de seleccionar un aa

    # Probabilidad máxima (1) menos las probabilidades de obtener un individuo aa
    prob = 1.0

    # Restar la probabilidad de que ambos padres sean aa
    prob -= pn * ((n - 1) / (t - 1))

    # Restar la probabilidad de que un padre sea aa y el otro sea Aa (dos escenarios)
    prob -= 2 * pn * (m / (t - 1)) * 0.5

    # Restar la probabilidad de que ambos padres sean Aa
    prob -= pm * ((m - 1) / (t - 1)) * 0.25

    return prob

# Ejemplo de uso
if __name__ == "__main__":
    # Leer los valores de k, m, n desde la línea de comandos
    import sys
    if len(sys.argv) != 4:
        print("Uso: python 007_IPRB.py k m n")
        sys.exit(1)

    k = int(sys.argv[1])
    m = int(sys.argv[2])
    n = int(sys.argv[3])

    # Calcular la probabilidad
    result = prob_dom(k, m, n)
    print(f"Probabilidad de que la descendencia tenga un alelo dominante: {result:.5f}")