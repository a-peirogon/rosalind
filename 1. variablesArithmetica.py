def hypotenuse(a, b):
    return a**2 + b**2 if a < 1000 and b < 1000 else None
print(hypotenuse(*map(int, input().split())))

