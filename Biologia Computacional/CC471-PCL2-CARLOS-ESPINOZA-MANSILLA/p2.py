from Bio import SeqIO

output_handle = open("p2.txt", "w")

print( "\nimprimir los id cuyas seq terminen en TFSL y sus longitudes\n")

filename = "PCL2.gb"
for record in SeqIO.parse(filename, "gb"):
	if record.seq[-4:] == "TFSL" :
		print("Record " + record.id + ", length " + str(len(record.seq)) + ", terminan en " + str( record.seq[-4:] ))
		output_handle.write("Record " + record.id + ", length " + str(len(record.seq)) + ", terminan en " + str( record.seq[-4:] )+"\n")

print( "volcado al archivo p2.txt completo." )
output_handle.close()


