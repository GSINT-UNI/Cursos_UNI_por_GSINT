from Bio import SeqIO
record = SeqIO.read("NC_000913.gbk", "genbank")

total1=0
total2=0
total3=0
total4=0
total5=0
total6=0
total7=0
total8=0
total9=0
total10=0
total11=0
total12=0

for feature in record.features:
    if feature.type == "gene":
        total1 = total1 + 1
    if feature.type == "CDS":
        total2 = total2 + 1
    if feature.type == "misc_feature":
        total3 = total3 + 1
    if feature.type == "mobile_element":
        total4 = total4 + 1
    if feature.type == "source":
        total5 = total5 + 1
    if feature.type == "rep_origin":
        total6 = total6 + 1
    if feature.type == "tRNA":
        total7 = total7 + 1
    if feature.type == "repeat_region":
        total8 = total8 + 1
    if feature.type == "tmRNA":
        total9 = total9 + 1
    if feature.type == "rRNA":
        total10 = total10 + 1
    if feature.type == "STS":
        total11 = total11 + 1
    if feature.type == "ncRNA":
        total12 = total12 + 1
            
print("Total number of all genes is " + str(total1))
print("Total number of all CDS is " + str(total2))
print("Total number of all misc_feature is " + str(total3))
print("Total number of all mobile_element is " + str(total4))
print("Total number of all source is " + str(total5))
print("Total number of all rep_origin is " + str(total6))
print("Total number of all tRNA is " + str(total7))
print("Total number of all repeat_region is " + str(total8))
print("Total number of all tmRNA is " + str(total9))
print("Total number of all rRNA is " + str(total10))
print("Total number of all STS is " + str(total11))
print("Total number of all ncRNA is " + str(total12))    



