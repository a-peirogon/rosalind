'''
My solution to Rosalind Bioinformatics Problem 005

Title: Computing GC Content
Rosalind ID: GC
Rosalind #: 005
URL: http://rosalind.info/problems/gc
'''

from Bio.SeqUtils import GC

f = open("./rosalind_gc.txt", 'r')
raw_data = f.readlines()
f.close()

samples = {}
cur_key = ''

for i in raw_data:
    if i[0] == '>':
        cur_key = i[1:].rstrip()
        samples[cur_key] = '' 
    else:
        samples[cur_key] += i.rstrip()
gc_samples = {}

for s_id, s in samples.items(): 
    gc_samples[s_id] = GC(s)

gc_id = max(gc_samples, key = gc_samples.get)
gc_value = max(gc_samples.values())

o = open('./005_GC.txt', 'w')
o.writelines('\n'.join([gc_id, str(gc_value)]))
o.close()