clc
clear

%Regresion cubica
clear

a = 3;
b = 2;
c = -1;
d = 4;

x = 1:0.8:10;
x = x';

nx = length(x);

yb = a*x.^3 + b*x.^2 + c.*x + d + 1.5*rand(nx,1);

figure(1);
plot(x,yb,'bo');

a = 3;
b = -2;
c = 1;
d = 2;

niter = 1000;
Jold = 10^10;
sigma = 0.0000002;
for k = 1 : niter
    aa(k,1) = a;
    bb(k,1) = b;
    cc(k,1) = c;
    dd(k,1) = d;
    Jnew = sum(a*x.^3 + b*x.^2 + c.*x + d - yb).^2/nx;
    dJ = sqrt(abs(Jnew - Jold)/Jold);
    if(dJ < 0.01)
        break;
    end
    dJda=(a*sum(x.^6) + b*sum(x.^5) + c*sum(x.^4) + d*sum(x.^3) - sum(x.^3.*yb))/nx; 
    dJdb=(a*sum(x.^5) + b*sum(x.^4) + c*sum(x.^3) + d*sum(x.^2) - sum(x.^2.*yb))/nx;
    dJdc=(a*sum(x.^4) + b*sum(x.^3) + c*sum(x.^2) + d*sum(x) - sum(x.^2.*yb))/nx;
    dJdd=(a*sum(x.^3) + b*sum(x.^2) + c*sum(x) + d*nx - sum(yb))/nx;
    %Metodo por descenso por gradiente:
    a = a - sigma*dJda;
    b = b - sigma*dJdb;
    c = c - sigma*dJdc;
    d = d - sigma*dJdd;
    Jold = Jnew;
end

hold on

a
b
c
d

y = a*x.^3 + b.*x.^2+c.*x + c;
plot(x,y);
figure(2);
subplot(4,1,1);
plot(1:length(aa),aa)
subplot(4,1,2);
plot(1:length(bb),bb);
subplot(4,1,3);
plot(1:length(cc),cc);
subplot(4,1,4);
plot(1:length(dd),dd);
