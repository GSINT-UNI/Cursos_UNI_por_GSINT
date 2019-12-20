from Bio import SeqIO
import sys
filename=sys.argv[1]
count = 0
for record in SeqIO.parse(filename, "fasta"):
	count = count + 1

print("Existen " + str(count) + " regsitros en el archivo " + sys.argv[1])

