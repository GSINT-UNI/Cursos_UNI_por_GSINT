clear;
clc;
close all;

an = 2;
bn = 3;
x = -3:0.05:2;
x = x';
nx = length(x);
yb = an*x +bn + 0.5*randn(nx,1);
figure(1);
plot(x,yb,'*b')

eta = input('eta: ');
sumx2 = sum(x.*x);       sumx = sum(x);
sumxyb = sum(x.*yb);   sumyb = sum(yb);
a = 3;
b = -1;
niter = 1000;
Jold = 1e10;
for k = 1:niter
     aa(k,1) = a;
     bb(k,1) = b;
     iter(k,1) = k;
     y = a*x + b;
     J = 0.5*(sum(y -yb).^2)/nx;
     dJrel = sqrt(abs(J - Jold)/Jold);
     if(dJrel < 0.01)
         break;
     end
     dJda = a*sumx2 + b*sumx - sumxyb;
     dJdb = a*sumx + b*nx - sumyb;
     a = a - eta*dJda/nx;
     b = b - eta*dJdb/nx;
     Jold = J;
end

y = a*x + b;
figure(1);
plot(x,yb,'*b',x,y,'-r');
figure(2);
subplot(2,1,1); plot(iter,aa,'ob');
subplot(2,1,2); plot(iter,bb,'ob');

[ an a 
  bn b ]
