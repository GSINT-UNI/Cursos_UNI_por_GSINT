
clear;
clc;
close all;

load cara1pix;
carapix = cara1pix;
figure(1);
imshow(carapix);
%carapix(35:37,15:17) = zeros(3,3);       % Negro
%carapix(40:41,20:21) = zeros(2,2);       % Negro 
%carapix(41:42,12:13) = zeros(2,2);
carapix(15,20:35) = zeros(1,16);          % Negro
carapix(6:7,26:27) = 255*ones(2,2);           % Blanco
carapix(9:10,18:19) = 255*ones(2,2);           % Blanco
carapix(:,47:50) = 255*ones(50,4);
carapix(1:4,:) = 255*ones(4,50);
carapix(12:14,15:35) = 255*ones(3,21);
carapix(32:34,15:17) = zeros(3,3);       % Negro

figure(2);
imshow(carapix);


cara = abs((carapix-255)/255);

[nf nc] = size(cara);
x(1,:) = cara(1,:);
for k = 2:nf
    x = [ x  cara(k,:) ];
end
[ nxf nxc ] = size(x);
nx = nxf;

ne = nxc;
load pesoscarasfotos;    % Carga nm v w bias
if(bias == 1)
   ne = ne +1;
   x = [ x ones(nx,1) ];   
end

in = x';
m = v'*in;
%n = 1.0./(1+exp(-m));    % Sigmoidea 1
n = 2.0./(1+exp(-m)) - 1; % sigmoidea 2
%n = exp(-m.^2);         % Gaussiana
out = w'*n;
y = out;

[maxy k] = max(y);
if(k == 1)
    disp('La Cara es 1');
elseif(k == 2)
    disp('La Cara es 2');
elseif(k == 3)
    disp('La Cara es 3');
elseif(k == 4)
    disp('La Cara es 4')
end

figure(3);
axis([ 0 nc  0  nf  ])
hold on;
for i = 1:nc
   for j = 1:nf
       if(cara(i,j) == 1)
           plot(j,(nf-i+1),'*b');
       end
   
   end
end
grid;
