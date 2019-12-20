import numpy as np
### numero de condicion ######
from numpy import linalg as LA
a = np.array([[1, 0, -1], [0, 1, 0], [1, 0, 1]])
print(a)
print("cond(a)={0}".format(LA.cond(a)))
print("cond(a,'fro')={0}".format(LA.cond(a, 'fro')))
