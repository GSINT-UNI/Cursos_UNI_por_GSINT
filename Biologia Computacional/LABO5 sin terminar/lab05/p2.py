from Bio import SeqIO
filename = "NC_000913.faa"
count = 0

for record in SeqIO.parse(filename, "fasta"):
	if( len(record.seq) < 100  ):
		count = count +1
		
print("lenght: " + str(count) )
