from Bio import SeqIO
filename = "NC_000913.faa"
count = 0

for record in SeqIO.parse(filename, "fasta"):
	count = count + len(record.seq) 
			
print("lenght: " + str(count) )
