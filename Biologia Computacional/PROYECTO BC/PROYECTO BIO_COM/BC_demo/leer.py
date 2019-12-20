from Bio import SeqIO

fastalist = open('fastaselec.fasta','w')

def leer(fastafilename):
	recordstr = open(fasta_selec,'r')
	for line in recordstr.readlines():
		fastalist.write(line)
	
	#record = SeqIO.read(fastafilename, "fasta")
	return recordstr

#record = leer(fasta_selec)

#fastalist = open('fastaselec.fasta','w')
#fastalist.write(str(record))
#fastalist.close()

fasta_selec = 'ACF75208.1.fasta'
print(leer(fasta_selec))
fasta_selec = 'AFQ38169.1.fasta'
print(leer(fasta_selec))
fastalist.close()
