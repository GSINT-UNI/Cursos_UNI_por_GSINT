% Este programa lee imagenes en formato jpg
% y las pixelea para bajar su resolución y
% el tamaño de la matriz

clear all;
close all;
clc;

I1 = imread('cara3.jpg','jpg');
figure(1);
imshow(uint8(I1));
I2 = I1;
Iz = I1(:,:,2);
[nf nc] = size(Iz);
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

% Pixelamiento en cuadrados de 10x10
Izz = Iz3(1:1650,1:1390);
ii = 1;
for i = 1:10:1650
   jj = 1; 
   for j = 1:10:1390 
      im = Iz3(i:i+9,j:j+9);
      im = sum(sum(im))/100; 
      Inueva10(ii,jj) = round(im); 
      jj = jj + 1;
   end
   ii = ii + 1;
end
figure(8);
imshow(uint8(Inueva10));

% Pixelamiento en cuadrados de 20x20
Izz = Iz3(1:1640,1:1380);
ii = 1;
for i = 1:20:1640
   jj = 1; 
   for j = 1:20:1380 
      im = Iz3(i:i+19,j:j+19);
      im = sum(sum(im))/400; 
      Inueva20(ii,jj) = round(im); 
      jj = jj + 1;
   end
   ii = ii + 1;
end
figure(9);
imshow(uint8(Inueva20));

% Pixelamiento en cuadrados de 30x30
Izz = Iz3(1:1650,1:1380);
ii = 1;
for i = 1:30:1650
   jj = 1; 
   for j = 1:30:1380 
      im = Iz3(i:i+29,j:j+29);
      im = sum(sum(im))/900; 
      Inueva30(ii,jj) = round(im); 
      jj = jj + 1;
   end
   ii = ii + 1;
end
figure(10);
imshow(uint8(Inueva30));

% Pixelamiento en cuadrados de 40x40
Izz = Iz3(1:1640,1:1360);
ii = 1;
for i = 1:40:1640
   jj = 1; 
   for j = 1:40:1360 
      im = Iz3(i:i+39,j:j+39);
      im = sum(sum(im))/1600; 
      Inueva40(ii,jj) = round(im); 
      jj = jj + 1;
   end
   ii = ii + 1;
end
figure(11);
imshow(uint8(Inueva40));

% Pixelamiento en cuadrados de 40x30
Izz = Iz3(1:1640,1:1380);
ii = 1;
for i = 1:40:1640
   jj = 1; 
   for j = 1:30:1380 
      im = Iz3(i:i+39,j:j+29);
      im = sum(sum(im))/1200; 
      Inueva43(ii,jj) = round(im); 
      jj = jj + 1;
   end
   ii = ii + 1;
end
figure(11);
imshow(uint8(Inueva43));

% Pixelamiento en cuadrados de 30x40
Izz = Iz3(1:1650,1:1360);
ii = 1;
for i = 1:30:1650
   jj = 1; 
   for j = 1:40:1360 
      im = Iz3(i:i+29,j:j+39);
      im = sum(sum(im))/1200; 
      Inueva34(ii,jj) = round(im); 
      jj = jj + 1;
   end
   ii = ii + 1;
end
figure(12);
imshow(uint8(Inueva34));


I40 = Inueva40;
I40bn = 255*round(I40/255*0.75);
figure(13);
imshow(uint8(I40bn));
I41bn = 255*round(I40/255*0.90);
figure(14);
imshow(uint8(I41bn));
I42bn = 255*round(I40/255*0.98);
figure(15);
imshow(uint8(I42bn));


