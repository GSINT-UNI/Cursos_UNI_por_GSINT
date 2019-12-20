import numpy as np
def cholesky(c):
    a=np.array(c)
    l=np.zeros_like(a)
    l[0,0]=np.sqrt(a[0,0])
    l[1:,0]=a[1:,0]/l[0,0]
    for j in range(1,n-1):
        l[j,j]=np.sqrt(
                a[j,j]-np.sum(l[j,0:j]**2))
        for i in range(j+1,n):
            l[i,j]=(a[i,j]-l[i,0:j].dot(
                            l[j,0:j]))/l[j,j]
    l[-1,-1]=np.sqrt(a[-1,-1]-np.sum(
            l[-1,0:-1]**2))
    return(l)

n=3
a= np.array([4 ,-2 ,2, 
             -2, 2, -4,
             2, -4, 11],
             dtype='f').reshape((n,n))
a=a.dot(a.T)
print('a =\n'+'\n'.join([''.join(['{:8.3f}'.format(item) for item in row]) 
      for row in a]))
l=cholesky(a)
print('l =\n'+'\n'.join([''.join(['{:8.3f}'.format(item) for item in row]) 
      for row in l]))
