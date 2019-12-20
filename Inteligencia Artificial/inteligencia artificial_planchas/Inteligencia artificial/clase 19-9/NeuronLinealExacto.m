% Regresion Lineal
% Metodo Exacto
% y = ax + b

clear;
clc;
close all;

a = 3;
b = -2;

x = -10:0.1:10;
x = x';
nx = length(x);

yb = a*x + b + 3.0*randn(nx,1);

figure(1);
plot(x,yb,'*');
hold on;
disp(' ');
disp('Press ENTER');
pause;

A1 = sum(x.*x);
A2 = sum(x);
B1 = sum(x);
B2 = nx;
C1 = sum(yb.*x);
C2 = sum(yb);

A = [ A1  B1
      A2  B2 ];
C = [ C1
      C2 ];
      
X = inv(A) * C;
an = X(1,1);
bn = X(2,1);

[ a  an
  b  bn ]
  
yn = an*x + bn;  
figure(1);
plot(x,yn,'-r');  









