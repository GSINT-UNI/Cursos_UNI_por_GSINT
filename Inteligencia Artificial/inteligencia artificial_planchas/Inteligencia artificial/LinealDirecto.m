%Regresion lineal
clear

%Creo mis constantes para la funcion a genera
a = 2;
b = 3;

%Genero mi intervalo X
x = 1:0.2:10;
x = x'

%Guardo el tamaño del numero de puntos en x
nx = length(x);

%Genero la funcion con algo ruido
yb = x*a + b + 0.2*rand(nx,1)

%Creo un marco
h = figure(1)
%Llego el marco con el ploteo
plot(x,yb,'bo')
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%Hasta el momento solo se ha generado los datos,
%Es similar como si lo hubiesemos obtenido de forma experimental
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Primero al ver la grafica observamos que la grafica tiende a ser 
% una funcion lineal, por lo cual definimos nuestro modelo matematico
% y = a*x + b;
% Donde ahora nuestro problema sera encontrar las constantes a y b
% Por ello definimos nuestra funcion a optimizar:
% J = E(( y - yb)^2) = sum( ( y - yb )^2 )/nx;
% yb : es el valor obtenido experimentalmente
% Todos sabemos que para optimizar una funcion debemos calcular los puntos
% criticos, lo cual aqui lo hacemos calculando la Gradiente de J e
% igualarla a 0
% => dJda = 0 ^ dJdb = 0
% Al desarrollar ambos calculos optendremos algo asi:
% dJda = sum(2*( y - yb )*x )/nx = 0 => sum((y - yb)*x) = 0 
%        => sum( (a*x + b - yb)*x) => a*sum(x^2) + b*sum(x) - sum(x*yb) = 0
%        => a*sum(x^2) + b*sum(x) = sum(x*yb)
% dJdb = sum(2*( y - yb ))/nx = 0    => sum(y - yb) = 0
%        => sum( a*x + b - yb ) = 0 => a*sum(x) + b*nx - sum(yb) = 0
%        => a*sum(x) + b*nx = sum(yb);
%DE ESTO SE OBTIENE EL SISTEMA DE ECUACIONES:
%a*sum(x^2) + b*sum(x) = sum(x*yb)
%a*sum(x) + b*nx = sum(yb);
% El cual se puede expresar matricialmente AC = B;
% A = [sum(x.*x) sum(x)
%     sum(x)   nx    ];
% C = [ a
%       b];
% B = [ sum(x*yb)
%       sum(yb)
%       ];
% Y el resto ya saben como calcular C, multiplicando por la inversa de A,
% ambos lados de la ecuacion.
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
A = [sum(x.*x) sum(x)
     sum(x)   nx    ];
B = [sum(x.*yb)
     sum(yb)];
C = inv(A)*B;

C

hold on

y = C(1,1)*x + C(2,1);
plot(x,y)

print(h,'-djpeg','-r200','C:\Users\LuisSullca\Documents\MATLAB/LinealDirecto.jpg')
close(h);