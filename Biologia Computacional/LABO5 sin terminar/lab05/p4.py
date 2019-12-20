from Bio import SeqIO
import matplotlib.pyplot as plt
import numpy as np

filename = "NC_000913.faa"
i=1

x = [len(record.seq) for record in SeqIO.parse(filename, "fasta") ]

plt.title('Histograma: seq lenght')
plt.hist(x,bins = 100,edgecolor = 'black')
plt.grid(True)
plt.show()
plt.clf()			
