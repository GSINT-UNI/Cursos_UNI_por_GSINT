from Bio import SeqIO

print "Carlos Espinoza Mansilla 20162187C"

output_handle = open("p1.txt", "w")

print( "\nparte 1.2 :  imprimir los id existentes y sus longitudes\n")

filename = "PCL2.gb"
for record in SeqIO.parse(filename, "gb"):
	print("Record " + record.id + ", length " + str(len(record.seq)))
	


print( "\nparte 1.3 : imprimir solo los mayores a 223 aminoacidos y su total\n")
output_handle.write("\nparte 1.3 : imprimir solo los mayores a 223 aminoacidos y su total\n")
count = 0
for record in SeqIO.parse(filename, "gb"):
	if len(record.seq) > 223 :
		print("Record " + record.id + ", length " + str(len(record.seq)))
		output_handle.write("Record " + record.id + ", length " + str(len(record.seq))+"\n")
	count = count + 1
print( "el total es " + str(count) )
output_handle.write("el total es " + str(count))
print( "volcado al archivo p1.txt completo." )
output_handle.close()
