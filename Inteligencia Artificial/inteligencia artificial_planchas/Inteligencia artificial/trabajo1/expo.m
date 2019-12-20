clc
clear

%Regresion exponencial
clear

a = 1;
b = 2;

x = -6:0.2:6;
x = x';

nx = length(x);
y  = b.*exp(x.*a) + 1.5*rand(nx,1);
lny = x.*a + rand(nx,1) + log(b) + 1.5*rand(nx,1);

figure(1)
plot(x,y,'bo')

aa = [sum(x.^2) sum(x)
     sum(x) nx];
bb = [sum(x.*lny)
     sum(lny)];
cc = inv(aa)*bb;

cc
a = cc(1,1);
b = cc(2,1);

hold on

y = b.*exp(x.*cc(1,1));
plot(x,y)
