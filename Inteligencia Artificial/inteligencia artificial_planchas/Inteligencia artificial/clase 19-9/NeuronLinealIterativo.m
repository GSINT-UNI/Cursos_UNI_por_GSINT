% Regresion Lineal
% Metodo Iterativo
% y = ax + b
% Analizar efecto de: eta, aini, bini, Niter, epsab

clear;
clc;
close all;

an = 3;
bn = -2;

x = -10:0.1:10;
x = x';
N = length(x);
yb = an*x + bn + 3.0*randn(N,1);

figure(1);
plot(x,yb,'*');

sumx2 = sum(x.*x);
sumx = sum(x);
sumxyb = sum(x.*yb);
sumyb = sum(yb);

epsab = 0.25;
aini = -30;
bini = 15;
a = aini;
b = bini;
Niter = 1000;
eta = input('eta: ');
for k = 1:Niter
  aold = a;
  bold = b;
  yn = a*x + b;   
  figure(1);
  plot(x,yb,'*b',x,yn,'-r');  
  grid;
  axis([-10 10 -40 40]);
  pause(0.1);
  aa(k,1) = a;
  bb(k,1) = b;
  nn(k,1) = k;
  dJda = sumx2*a + sumx*b - sumxyb;
  dJdb = sumx*a + b*N - sumyb;
  dJda = dJda/N;
  dJdb = dJdb/N;
  a = a - eta*dJda;
  b = b - eta*dJdb;  
  dapor = abs((a-aold)/a) * 100;
  dbpor = abs((b - bold)/b) * 100;
  if((dapor < epsab) & (dbpor < epsab ))
     break;
  end
end

[ an  a
  bn  b ]
  

figure(1);
plot(x,yb,'*b',x,yn,'-r');  
grid;
axis([-10 10 -40 40]);
figure(2);
subplot(2,1,1);   plot(nn,aa,'*');
subplot(2,1,2);   plot(nn,bb,'*');







