clc
clear

%Regresion cuadratica
clear

a = 1;
b = 2;

x = 1:0.2:10;
x = x'

nx = length(x);

yb = x.*a + b + rand(nx,1);

figure(1)
plot(x,yb,'bo')

a = 3;
b = -1;

niter = 1000;
Jold = 10^10;
sigma = 0.02;
for k = 1 : niter
    aa(k,1) = a;
    bb(k,1) = b;
    Jnew = sum(a*x + b - yb).^2/nx;
    dJ = sqrt(abs(Jnew - Jold)/Jold);
    if(dJ < 0.01)
        break;
    end
    dJda = (a*sum(x.^2) + b*sum(x)    - sum(x.*yb))/nx;
    dJdb = (a*sum(x)    + b*nx        - sum(yb))/nx;
    %Metodo por descenso por gradiente:
    a = a - sigma*dJda;
    b = b - sigma*dJdb;
    Jold = Jnew;
end

hold on

a
b

y = a*x + b;
plot(x,y);
figure(2);
subplot(2,1,1);
plot(1:length(aa),aa)
subplot(2,1,2);
plot(1:length(bb),bb);