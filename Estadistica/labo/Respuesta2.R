# Nombre : Carlos Alberto Espinoza Mansilla 20162187C

#(a)
#vector que va a rellenar la matriz
x1=c(4.3,3.1,8.2,8.2,3.2,0.9,1.6,6.5) 
#creación de la matriz 4x2 ordenada por fila
A=matrix(x1,nrow=4,ncol=2,byrow=TRUE) 
A

#(b)
#para confirmar que las dimensiones de A son 3x2
#si si elimina una fila voy a "eliminar" la fila 2

A[c(1,3,4),c(1,2)]
dim(A[c(1,3,4),c(1,2)])

#(c)
#para ordenar la segunda columna de la matriz voy a
#concatenar la primera la columna de la matriz original 
#con la segunda pero ya ordenada
A=cbind(A[,1],sort(A[,2]))
A

#(d)
#R devuelve una matriz columna con 3 filas
matrix(A[c(1,2,3),2],ncol=1)

#(e)
#simplemente tomaré los elementos 3,1 3,2 4,1 4,2 de A
B=A[c(3,4),c(1,2)]
B

#(f)
#se reescribe los datos en el orden pedido
A[4,2]=-0.5*B[1,1]
A[1,2]=-0.5*B[2,2]
A[4,1]=-0.5*B[1,1]
A[1,1]=-0.5*B[2,2]
A

#(g)
#Creacion de la matriz "C"
C=diag(c(2,3,5,-1),4) 
C

#Se realiza la operacion inversa(C)*C - I 
solve(C)%*%C - diag(4)
#se comprueba que da la matriz nula
