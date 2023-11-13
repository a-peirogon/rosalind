from collections import Counter
print(" ".join("{}".format(v) for k, v in sorted(Counter(input('')).items())))
