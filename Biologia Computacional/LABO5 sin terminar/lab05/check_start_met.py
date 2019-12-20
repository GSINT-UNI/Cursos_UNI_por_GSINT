from Bio import SeqIO
filename = "fetch_sample_data.sh"

bad = 0

for record in SeqIO.parse(filename, "fasta"):
	if not record.seq.startswith("M"):
		bad = bad + 1
		print(record.id + " starts " + record.seq[0])
		
print("Found " + str(bad) + " records in " + filename + " which did not start with M")
