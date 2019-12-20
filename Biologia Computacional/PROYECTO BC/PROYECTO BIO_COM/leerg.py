from Bio import SeqIO

from Bio import AlignIO
from Bio.Phylo.TreeConstruction import DistanceCalculator
from Bio.Phylo.TreeConstruction import DistanceTreeConstructor
from Bio import Phylo
import pylab

def upgma_tree(fichero_clw):
    with open(fichero_clw, "r") as aln:
        #usar AlignIO tpara leer el archivo de alineamiento en formato 'clustal' format
        alignment = AlignIO.read(aln, "fasta")

    #calcular la  matriz de distancias
    calculator = DistanceCalculator('identity')
    # añade la matriz de  distancias al objeto calculator y lo retorna
    dm = calculator.get_distance(alignment)
    print(dm)    
    #initialize a DistanceTreeConstructor object based on our distance calculator object
    constructor = DistanceTreeConstructor(calculator)

    #build the tree
    #upgma_tree = constructor.build_tree(alignment)
    upgma_tree = constructor.upgma(dm)


    #draw the tree
    Phylo.draw(upgma_tree)


def nj_tree(fichero_clw):
    with open(fichero_clw, "r") as aln:
        #usar AlignIO tpara leer el archivo de alineamiento en formato 'clustal' format
        alignment = AlignIO.read(aln, "fasta")

    #calcular la  matriz de distancias
    calculator = DistanceCalculator('identity')
    # añade la matriz de  distancias al objeto calculator y lo retorna
    dm = calculator.get_distance(alignment)
    print(dm)    
    #initialize a DistanceTreeConstructor object based on our distance calculator object
    constructor = DistanceTreeConstructor(calculator)
    #build the tree
    #upgma_tree = constructor.build_tree(alignment)
    nj_tree = constructor.nj(dm)
    Phylo.draw(nj_tree)
    




def leer(fastafilename):
	fastalist = open('fastaselec.fasta','a') #archivo unificado de fasta
	recordstr = open(fastafilename,'r')	#lee el archivo fasta con una secuencia
	for line in recordstr.readlines():	#escribe linea por linea
		fastalist.write(line)
	fastalist.close()										#cierra el unificado


def sel_fasta(filename):
    f=open(filename,"r")
    content=f.read()
    f.close()
    return content
    
    
#upgma_tree("musculo.fasta")
