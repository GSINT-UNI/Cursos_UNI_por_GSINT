% Este programa lee imagenes en formato jpg
% y las pixelea para bajar su resolución y
% el tamaño de la matriz

clear all;
close all;
clc;

I1 = imread('cara55.jpg','jpg');
figure(1);
imshow(uint8(I1));
I2 = I1;
Iz = I1(:,:,2);
[nf nc] = size(Iz);
size(Iz)
figure(2);
imshow(uint8(Iz));
for f = 1:nf
  Ifila = Iz(f,:);
  if(any(Ifila < 255)) 
      break;
  end
end
nfc = 1800;
Iz1 = Iz(f:nfc,:);
figure(3);
imshow(uint8(Iz1));

for c1 = 1:nc
   Icol = Iz1(:,c1);
   if(any(Icol < 255)) 
     break;
   end
end
Iz2 = Iz1(:,c1:nc);
figure(4);
imshow(uint8(Iz2));


[nc2 nf2] = size(Iz2);
for c2 = nc2:-1:1
   Icol = Iz2(:,c2);
   if(any(Icol < 255)) 
     break;
   end  
end
Iz3 = Iz2(:,1:c2);
figure(5);
imshow(uint8(Iz3));

[ff1 cc1] = size(Iz3);

f = input('Numero de filas: ');
c = input('Numero de columnas: ');

ff2  = f*floor(ff1/f);
cc2 = c*floor(cc1/c);

ii = 1;
for i = 1:f:ff2
   jj = 1; 
   for j = 1:c:cc2
      im = Iz3(i:i+f-1,j:j+c-1);
      im = sum(sum(im))/(f*c); 
      Inueva(ii,jj) = round(im); 
      jj = jj + 1;
   end
   ii = ii + 1;
end
figure(6);
imshow(uint8(Inueva));

I40 = Inueva;
I40bn = 255*round(I40/255*0.85);
figure(7);
imshow(uint8(I40bn));
I41bn = 255*round(I40/255*0.90);
figure(8);
imshow(uint8(I41bn));
I42bn = 255*round(I40/255*0.95);
figure(9);
imshow(uint8(I42bn));
save cara1px I40bn;
save cara2px I40bn;
save cara3px I40bn;
save cara4px I40bn;