import urllib.request
import re


target_url = 'https://raw.githubusercontent.com/Grol4Espinoza/Curso-Ing.-de-Software-/master/pc2/ventas
'
data = urllib.request.urlopen(target_url)
ventaEnero = 0
for line in data: # files are iterable
    x = re.search("Enero(:)?\s*S/\.\s(\d+)(\.\d+)?", line)
    strtoint = x.group(2)+x.group(3)
    ventaEnero = ventaEnero + float(strtoint)

data.close()


 


