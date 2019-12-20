### numero de condicion de una funcion######
w_roots=np.arange(1,21)
W=np.poly(w_roots)
perturb=np.zeros_like(W)
perturb[1]=1e-7
W_perturb = W + perturb
perturbed_roots=np.roots(W_perturb)
w_roots = np.sort(w_roots)
perturbed_roots = np.sort(perturbed_roots)
print((LA.norm(perturbed_roots-w_roots)/
    LA.norm(perturb)))
######################################################
# Esta directiva habilita los graficos en notebook 
%matplotlib inline
######################################################
import matplotlib.pyplot as plt
plt.plot(w_roots,np.zeros_like(w_roots),'o')
plt.plot(perturbed_roots.real,perturbed_roots.imag,'*')
plt.show()
