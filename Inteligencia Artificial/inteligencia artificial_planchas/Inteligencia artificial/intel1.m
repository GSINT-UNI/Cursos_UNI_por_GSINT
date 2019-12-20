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

A11 = sum(x.*x);
A12 = sum(x);
A21 = A12;
A22 = nx;
B1 = sum(x.*yb);
B2 = sum(yb);
A = [ A11  A12
        A21  A22 ];
B = [ B1
        B2 ];
z = inv(A)*B;
a = z(1,1);
b = z(2,1);

y = a*x + b;
figure(1);
plot(x,yb,'*b',x,y,'-r');

[ an a 
  bn b ]
