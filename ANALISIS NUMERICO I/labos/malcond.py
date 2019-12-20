a = np.array([[1, -.01], [2, .01]])
print("cond(a)={0}".format(LA.cond(a)))
#### queremos resolver ax=y
####                   (a+da)x=y
y = np.array([2,1]).reshape((2, 1))
da= np.array([[0, 0], [0, .005]])
x0 = np.linalg.solve(a, y)
x1 = np.linalg.solve(a+da, y)

print("Solucion inicial ={0} ".format(x0.reshape(2,)))

print("Solucion perturbada ={0} ".format(x1.reshape(2,)))
