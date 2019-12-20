from Bio import SeqIO
input_filename = sys.argv[1]
output_filename = sys.argv[2]
count = SeqIO.convert(input_filename, "gb", output_filename, "fasta")
print(str(count) + " records converted")
