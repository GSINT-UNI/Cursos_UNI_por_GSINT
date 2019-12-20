#CARLOS ALBERTO ESPINOZA MANSILLA pcl1.py Martes 9 de abril de 2019
#importamos las librerias necesarias
from Bio import SeqIO
import os
#creamos un array para guardar las secuencias 

records = []

#lee los archivos dentro de la carpeta secfasta y los concatena
for archivo in os.listdir("secfasta"):
	seq = open("secfasta" + "/" + archivo)
	record = SeqIO.read( seq, "fasta" )
	records.append ( record )

#guarda toda la cadena dentro de un nueco archivo totalfasta.fasta
SeqIO.write( records, "totalfasta.fasta", "fasta" )
