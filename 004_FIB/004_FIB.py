'''
Title: Rabbit and Recurrence Relations
Rosalind ID: FIB
Rosalind #: 004
URL: http://rosalind.info/problems/fib
'''

n,k=map(int,input().split());a,b=1,1
for i in range(2,n):a,b=b,b+k*a
print(b)

