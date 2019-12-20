clc
clear

%Regresion cuadratica
clear


an=1;
bn=2;
cn=3;

a = 1;
b = 2;
c=3;
x = -4:0.2:4;
x = x'
nx = length(x);
yb = a*x.^2 + b.*x + c + 1.5*rand(nx,1);



figure(1)
plot(x,yb,'bo')

a = 3;
b = -1;
c=2;
niter = 1000;
Jold = 10^10;
sigma = 0.02;

for k = 1 : niter
    aa(k,1) = a;
    bb(k,1) = b;
    cc(k,1)=c;
    
    Jnew = sum( a*x.^2 + b.*x + c - yb).^2/nx;
    dJ = sqrt(abs(Jnew - Jold)/Jold);
    if(dJ < 0.01)
        break;
    end
    dJda=(a*sum(x.^4) +b*sum(x.^3)+ c*sum(x.^2)-sum(x.^2.*yb))/nx;
    dJdb=(a*sum(x.^3)+ b*sum(x.^2)+c*sum(x)-sum(x.*yb))/nx;
    dJdc=( a*sum(x.^2)+ b*sum(x)+c*nx-sum(yb))/nx;
    %Metodo por descenso por gradiente:
    a = a - sigma*dJda;
    b = b - sigma*dJdb;
    c=c-sigma*dJdc;
    Jold = Jnew;
end

hold on

a
b
c
y = a*x.^2 + b.*x + c;
plot(x,y);
figure(2);
subplot(3,1,1);
plot(1:length(aa),aa)
subplot(3,1,2);
plot(1:length(bb),bb);
subplot(3,1,3);
plot(1:length(cc),cc);

