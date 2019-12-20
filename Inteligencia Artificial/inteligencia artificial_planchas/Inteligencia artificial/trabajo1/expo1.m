%METODO DIRECTO
clear

a = 1;
b = 2;

x = -4:0.2:4;
x = x';

nx = length(x);
y=b.*exp(x.*a)+1.5*rand(nx,1);
lny=x.*a+rand(nx,1)+log(b)+1.5*rand(nx,1);

figure(1)
plot(x,y,'bo')


A = [sum(x.^2) sum(x)
     sum(x)   nx    ];
B = [sum(x.*lny)
     sum(lny)];
C = inv(A)*B;

C
a=C(1,1);
b=C(2,1);

hold on


y=b.*exp(x.*C(1,1));
plot(x,y)

