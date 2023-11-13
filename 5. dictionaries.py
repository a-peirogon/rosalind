from collections import Counter
print(*(f"{k} {v}\n" for k, v in Counter(input('').split()).items()))
