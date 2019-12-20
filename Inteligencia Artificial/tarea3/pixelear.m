% Este programa lee imagenes en formato jpg
% y las pixelea para bajar su resolución y
% el tamaño de la matriz

clear all;
close all;
clc;
#leer la imagen a modificar
I1 = imread('imagenesvalidacion/cara2mod.jpg','jpg');
%==============================================================
figure(1); #prepara la ventana para mostrar la imagen
imshow(uint8(I1));
I2 = I1;
Iz = I1(:,:,2);
[nf nc] = size(Iz);
%figure(2);
%imshow(uint8(Iz));

#lee desde arriba hasta encontrar un pixel diferente de blanco
for f = 1:nf
  Ifila = Iz(f,:);
  if(any(Ifila < 255)) 
      break;
  end
end
%==============================================================
%el valor nfc es el que decide donde cortar por abajo.
% Cambiar este valor para cada foto
k = 3
nfc = nf - nf/k;        % Recorte del cuello
Iz1 = Iz(f:nfc,:);
figure(3);
imshow(uint8(Iz1));
%==============================================================

%recorta la imagen por la izquierda(por columnas) 
for c1 = 1:nc
   Icol = Iz1(:,c1);
   if(any(Icol < 255)) 
     break;
   end
end
Iz2 = Iz1(:,c1:nc);
%figure(4);
%imshow(uint8(Iz2));

%==============================================================

%recorta la imagen por la derecha(por columnas)
[nc2 nf2] = size(Iz2);
for c2 = nc2:-1:1
   Icol = Iz2(:,c2);
   if(any(Icol < 240)) 
     break;
   end  
end
Iz3 = Iz2(:,1:c2);
%figure(5);
%imshow(uint8(Iz3));
[ff cc] = size(Iz3);

%==============================================================
% INICIO DEL PIXELEADO

%tamaño final de la imagen
tamfinalf = 50
tamfinalc = 50
numf  = floor(ff/tamfinalf);
numc = floor(cc/tamfinalc);

ff1  = numf*floor(ff/numf);
cc1 = numc*floor(cc/numc);

% Pixelamiento en cuadrados de 10x10
% Izz = Iz3(1:720,1:530);
ii = 1;
for i = 1:numf:ff1
   jj = 1; 
   for j = 1:numc:cc1 
      im = Iz3(i:i+numf-1,j:j+numc-1);
      im = sum(sum(im))/(numf*numc); 
      Inueva(ii,jj) = round(im); 
      jj = jj + 1;
   end
   ii = ii + 1;
end
%figure(8);
%imshow(uint8(Inueva));

I40 = Inueva;
I40bn = 255*round(I40/255*0.85);
%figure(13);
%imshow(uint8(I40bn));
I41bn = 255*round(I40/255*0.90);
%figure(14);
%imshow(uint8(I41bn));
I42bn = 255*round(I40/255*0.95);
fig=figure(15);
imshow(uint8(I42bn));

%==============================================================
[ff2 cc2] = size(I42bn);
Ifinal = I42bn(1:tamfinalf,1:tamfinalc);
[numfinalf numfinalc] = size(Ifinal);

%grabamos informacion del archivo para leerlo en los otros
save -ascii imagenespx/cara2modpx Ifinal;
