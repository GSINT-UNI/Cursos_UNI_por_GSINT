% Este programa lee imagenes en formato jpg
% y las pixelea para bajar su resolución y
% el tamaño de la matriz

clear all;
close all;
clc;

I1 = imread('beatiful2.jpg','jpg');
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
nfc = 230;
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
   if(any(Icol < 240)) 
     break;
   end  
end
Iz3 = Iz2(:,1:c2);
figure(5);
imshow(uint8(Iz3));

[ff cc] = size(Iz3);
% Pixelamiento en cuadrados de 10x10
% Izz = Iz3(1:720,1:530);





% Pixelamiento en cuadrados de 20x20
% Izz = Iz3(1:1640,1:1380);
% Izz = Iz3(1:720,1:520)



f= input('Filas :    ');
c= input('Columnas : ');

ff3  = f*floor(ff/f);
cc3 = c*floor(cc/c);

ii = 1;
for i = 1:f:ff3
   jj = 1; 
   for j = 1:c:cc3
      im = Iz3(i:i+f-1,j:j+c-1);
      im = sum(sum(im))/(f*c); 
      Inueva(ii,jj) = round(im); 
      jj = jj + 1;
   end
   ii = ii + 1;
end
figure(10);
imshow(uint8(Inueva));




I40 = Inueva;
I40bn = 255*round(I40/255*0.85);
save I40bn;
figure(13);
imshow(uint8(I40bn));
I41bn = 255*round(I40/255*0.90);
figure(14);
imshow(uint8(I41bn));
I42bn = 255*round(I40/255*0.95);
figure(15);
imshow(uint8(I42bn));


