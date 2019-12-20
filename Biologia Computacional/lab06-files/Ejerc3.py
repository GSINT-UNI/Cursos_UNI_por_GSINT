#!/usr/bin/python

from Bio import SeqIO
record = SeqIO.read("NC_000913.gbk", "genbank")
total = 0
#lista para almacenar los tipos de información en la secuencia
types=[]
for feature in record.features:
    feature_name = feature.qualifiers   
    types.append(feature.type)

# eliminamos los datos repetidos de la lista types
types=list(set(types))           

# cantidades de cada tipo
sizes=[0]*len(types)

#diccionario que almacenará los resultados de los tipos y las cantidades
dictionary=dict(zip(types,sizes))


for feature in record.features:
    feature_name = feature.qualifiers   
    dictionary.update({feature.type:dictionary[feature.type]+1})
    
comprobacion=0
print("Imprimiendo tipos encontrados y cantidades por cada uno: ")
for key in dictionary:
    print key, ":", dictionary[key]
    comprobacion=comprobacion+dictionary[key]


