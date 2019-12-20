#!/usr/bin/python
from Bio import SeqIO
fasta_record = SeqIO.read("NC_000913.fna", "fasta")
print("Archivo formato FASTA")
print(fasta_record.id + " length " + str(len(fasta_record)))
print("*******************")
print("Archivo formato GBK")
genbank_record = SeqIO.read("NC_000913.gbk", "genbank")
print(genbank_record.id + " length " + str(len(genbank_record)))

