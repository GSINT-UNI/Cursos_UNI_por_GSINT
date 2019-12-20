clc
clear

%Regresion cuadratica
clear

a = 2;
b = 3;

x = -2:0.2:2;

Q = length(x);

yb = a*x + b;

h = figure(1);
plot(x,yb,'bo');

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
Q = length(x);% Cantidad de datos de prueba
ni = 1;%numero de neuronas de la capa de entrada
no = 4;%numero de neuronas en la capa oculta
ns = 1;%numero de neuronas en la capa de salida
m = 2;

%W1 = [ -0.27; -0.41]
%b1 = [ -0.48; -0.13]
W1 = 0.01*rand(no,ni);
b1 = 0.1*rand(no,1);
%W2 = [ 0.09 -0.17] %1x1
%b2 = [ 0.48] %1x1
W2 = 0.01*rand(ns,no);
b2 = 0.1*rand(ns,1);
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
a0 = [1];
n1 = W1*a0+b1;
a1 = 1./(1+exp(-n1));

n2 = W2*a1 + b2;
a2 = n2;
a2

err = 1 + sin(pi/4) - a2

dfdn2 = ones(1,ns);
dF2 = diag(dfdn2);
S2 = -2*dF2*err

dfdn1 = a1.*(1-a1);
dF1 = diag(dfdn1);
dF1
S1 = dF1*W2'*S2
%%%%%%%%%%%%%%%%%%%%%%%%%%%%5

niter = 10000;
Jold = 10^10;
sigma = 0.01;
for k = 1 : niter
    J = 0;
    for q = 1:Q
       %%%%FEEDFORWARD%%%%
       a0 = x(:,q);
       n1 = W1*a0+b1;
       a1 = 1./(1+exp(-n1));

       n2 = W2*a1 + b2;
       a2 = n2;
       %%%%ERRROR%%%%%%%%
       err = yb(:,q) - a2;
       Jq = err'*err;
       J = J + Jq
       %%%BACKPROPAGATION%%%
       dfdn2 = ones(1,ns);
       dF2 = diag(dfdn2);
       S2 = -2*dF2*err;
       dfdn1 = a1.*(1-a1);
       dF1 = diag(dfdn1);
       S1 = dF1*W2'*S2;
       W2 = W2 - sigma*S2*a1';
       b2 = b2 - sigma*S2;
       W1 = W1 - sigma*S1*a0';
       b1 = b1 - sigma*S1;
    end
    Jnew = J/Q;
    dJ = sqrt(abs(Jnew - Jold)/Jold);
    if(dJ < 0.01)
        break;
    end
    Jold = Jnew;
end

for q = 1:Q
       %%%%FEEDFORWARD%%%%
       a0 = x(:,q);
       xx(q,1) = a0;
       n1 = W1*a0+b1;
       a1 = 1./(1+exp(-n1));

       n2 = W2*a1 + b2;
       a2 = n2;
       yy(q,1) = a2;
end
hold on

plot(xx,yy)