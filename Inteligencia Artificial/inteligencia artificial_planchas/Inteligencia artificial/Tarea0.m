%Regresion lineal
clear

a = 2;
b = 3;

x = 1:0.2:10;
x = x'

nx = length(x);

yb = x*a + b + 2*rand(nx,1)

figure(1)
plot(x,yb,'bo')

A = [sum(x.*x) sum(x)
     sum(x)   nx    ];
B = [sum(x.*yb)
     sum(yb)];
C = inv(A)*B;

C

hold on

y = C(1,1)*x + C(2,1);
plot(x,y)

