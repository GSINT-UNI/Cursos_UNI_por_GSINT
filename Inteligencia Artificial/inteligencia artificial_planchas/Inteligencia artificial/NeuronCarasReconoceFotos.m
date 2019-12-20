% Entrenamiento patron

clear;
clc;
close all;

load cara1pix;  load cara2pix;  load cara3pix;  load cara4pix; 
figure(1);
subplot(2,2,1);  imshow(cara1pix);
subplot(2,2,2);  imshow(cara2pix);
subplot(2,2,3);  imshow(cara3pix);
subplot(2,2,4);  imshow(cara4pix);
disp('Press ENTER');
pause;
% Transformando del rango 0(negro)-255(blanco) a 0(blanco)-1(negro)  
cara1 = abs((cara1pix-255)/255);
cara2 = abs((cara2pix-255)/255);
cara3 = abs((cara3pix-255)/255);
cara4 = abs((cara4pix-255)/255);
% clear cara1pix cara2pix cara3pix cara4pix;

[nf nc] = size(cara1);
x(1,:) = cara1(1,:);
x(2,:) = cara2(1,:);
x(3,:) = cara3(1,:);
x(4,:) = cara4(1,:);
for k = 2:nf
   caras = [ cara1(k,:)
             cara2(k,:)
             cara3(k,:)
             cara4(k,:)  ];
   x = [ x  caras ];
end
[ nxf nxc ] = size(x);
nx = nxf;

yb(1,:) = [ 1 0 0 0 ]; 
yb(2,:) = [ 0 1 0 0 ]; 
yb(3,:) = [ 0 0 1 0 ]; 
yb(4,:) = [ 0 0 0 1 ]; 

[ nyf nyc ] = size(yb);
ny = nyf;

ne = nxc;
nm = 10;
ns = nyc;
bias = input('Bias:  SI = 1 : ');
if(bias == 1)
   ne = ne +1;
   x = [ x ones(nx,1) ];   
end
v = 0.2*(rand(ne,nm) - 0.5)*2;
w = 0.2*(rand(nm,ns) - 0.5)*2;
% load pesoscaras;

eta = input('eta pesos : ');

for iter = 1:2000
count(iter,1) = iter;
dJdw = 0;
dJdv = 0;
for k = 1:nx   
in = (x(k,:))';
m = v'*in;
% n = 1.0./(1+exp(-m));    % Sigmoidea 1
n = 2.0./(1+exp(-m)) - 1; % sigmoidea 2
%n = exp(-m.^2);         % Gaussiana
out = w'*n;
y(k,:) = out';
er = out - (yb(k,:))';
error(k,:) = er;
% dndm = n.*(1 - n);       % Sigmoidea 1
dndm = (1 - n.*n)/2;     % Sigmoidea 2
%dndm = -2.0*(n.*m);     % Gaussiana
dydw = n; 
dJdw = 1*dJdw + dydw*er';    
dJdv = 1*dJdv + in*((w*er).*dndm)';    
%w = w - eta*dJdw/nx;   
%v = v - eta*dJdv/nx;      
end
w = w - eta*dJdw/nx;   
v = v - eta*dJdv/nx; 
JJ = 0.5*sum(sum(error.*error))
J(iter,1) = JJ;
end

save pesoscarasfotos ns nm v w  bias; 

figure(2);
plot(y(1,:),'or');   % Se grafica sin redondeo
hold on;
plot(yb(1,:),'*b');

figure(3);
plot(count,J);

