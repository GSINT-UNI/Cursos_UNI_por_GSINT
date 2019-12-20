% Program for training a neural network for controlling a car-robot.
% The network is trained using the Dynamic Back Propagation Algorithm.
% The network is trained only for four initial positions. The network is
% able to generalize for other initial positions.
% Incremental learning regarding initial positions.


clear;
clc;
close all;

disp('Hello Hello');

ndata = 1000;    % Steps for a run
     
x_ini = [ -2     -2      2       2       % Incremental learning 
            pi/2   -pi/2   pi/2   -pi/2 ];
      
ne = 2;    % No bias
nm = 50;
ns = 1;

v = 0.1*randn(ne,nm);
w = 0.1*randn(nm,ns);
c = zeros(nm,1);
a = ones(nm,1);

% load redcarro;
% load redcarro1;

eta  = input('Input learning rate for v, w: ');
etaa  = input('Input learning rate for sigmoid slope a: ');
% etac  = input('Input learning rate for sigmoid center c: ');    
etac = 0;

%errormax = input('Input error function maximum value (%) : ');
errormax = 5;     % Cualquier valor
errormax = errormax/100;
contmax = input('Input the maximum number of steps: ');

cont = 1;
erreltotal = 1;
   dw_old = 0;  
   dv_old = 0;
   dc_old = 0;
   da_old = 0;
   
   r = 0.01;
   L = 2;
   
   u = 0;
 %  estado = x_ini;
   
while( (erreltotal > errormax) & (cont < contmax) ) 
   ersum2 = zeros(ns,1);
   dJdw = 0;
   dJdv = 0;
   dx1dw_t = zeros(nm,ns);        
   dx2dw_t = zeros(nm,ns);
   dx1dv_t = zeros(ne,nm);
   dx2dv_t = zeros(ne,nm);
   dx1dc_t = zeros(nm,1);        
   dx2dc_t = zeros(nm,1);   
   dx1da_t = zeros(nm,1);        
   dx2da_t = zeros(nm,1);  
   dJdw_t  = zeros(nm,ns);
   dJdv_t  = zeros(ne,nm); 
   dJdc_t  = zeros(nm,1);
   dJda_t  = zeros(nm,1); 
   
   
%   x = x_ini;
%   clear u;
%   clear estado;

   ktot = 0;
   for j = 1:4
      
      x = x_ini(:,j);
   
      for k = 1:ndata-1
      in_red = [ x(1,1)
                     x(2,1) - pi/2 ];
      m = v'*in_red;
      n = 2.0./(1 + exp(-(m-c)./a)) - 1;  
%      n = m;
      out_red = w'*n;
      
%      if( out_red > 1.1918 )   % tangente(50 grados)
%          out_red = 1.1918;
%      elseif(out_red < -1.1918 )
%          out_red = -1.1918;
%      end  

      u(k,j) = out_red';
      [ x' out_red' ];
      estado(k,:,j) = x';
      jacob = [ 1  -r*sin(x(2,1))
                0  1 ];
      dxdu = [ 0
               -r/L ];   
      z(1,1) = x(1,1) + r*cos(x(2,1));
      z(2,1) = x(2,1) - r/L*u(k,j);
      x = z;
      
      dndm = diag((1 - n.*n)./(2*a));  
%     dndm = diag(ones(nm,1));
      dudw_s = [ n ];
      dudv_s = in_red*w'*dndm;
      
      dudc_s = w .* ((n.*n-1)./(2.0.*a));
      duda_s = w .* ((n.*n-1).*(m-c)./(2*a.*a));
      
      dudx = w'*dndm*v';

      jacob_t = dxdu*dudx + jacob;
      dx1dw_t = dxdu(1,1).*dudw_s + jacob_t(1,1).*dx1dw_t + jacob_t(1,2).*dx2dw_t;
      dx2dw_t = dxdu(2,1).*dudw_s + jacob_t(2,1).*dx1dw_t + jacob_t(2,2).*dx2dw_t;
      dx1dv_t = dxdu(1,1).*dudv_s + jacob_t(1,1).*dx1dv_t + jacob_t(1,2).*dx2dv_t;
      dx2dv_t = dxdu(2,1).*dudv_s + jacob_t(2,1).*dx1dv_t + jacob_t(2,2).*dx2dv_t;      
      dx1dc_t = dxdu(1,1).*dudc_s + jacob_t(1,1).*dx1dc_t + jacob_t(1,2).*dx2dc_t;
      dx2dc_t = dxdu(2,1).*dudc_s + jacob_t(2,1).*dx1dc_t + jacob_t(2,2).*dx2dc_t;
      dx1da_t = dxdu(1,1).*duda_s + jacob_t(1,1).*dx1da_t + jacob_t(1,2).*dx2da_t;
      dx2da_t = dxdu(2,1).*duda_s + jacob_t(2,1).*dx1da_t + jacob_t(2,2).*dx2da_t;    
      
      out_des = [ 0    pi/2 ];
      out_des = out_des';
      er = (x - out_des);
      erJ = (x - out_des).^1;
      dJdw_t =  dJdw_t + erJ(1,1).*dx1dw_t + erJ(2,1).*dx2dw_t;
      dJdv_t =  dJdv_t + erJ(1,1).*dx1dv_t + erJ(2,1).*dx2dv_t;
      dJdc_t =  dJdc_t + erJ(1,1).*dx1dc_t + erJ(2,1).*dx2dc_t;     
      dJda_t =  dJda_t + erJ(1,1).*dx1da_t + erJ(2,1).*dx2da_t;
      
      ersum2 = ersum2 + er.^2;
      if( (abs(x(1,1)) > 10)  | (abs(x(2,1)) > 10) )
          break;
      end
    
   end
   ktot = ktot + k; 
end

      dJdw_t = dJdw_t/ktot;
      dJdv_t = dJdv_t/ktot;  
      dJdc_t = dJdc_t/ktot;
      dJda_t = dJda_t/ktot;
      dw = dJdw_t;
      dv = dJdv_t;
      dc = dJdc_t;      
      da = dJda_t;
      w = w - eta*dw;
      v = v - eta*dv;
      c = c - etac*dc;
      a = a - etaa*da;
      
      dw_old = dw;
      dv_old = dv;
      dc_old = dc;
      da_old = da;
      
  ersum2total = sum(ersum2)
  cont = cont + 1;

end  

save redcarro nm v w c a;

figure(1);
plot(estado(:,:,1));
title('First Initial Position');
xlabel('Learning Steps');
grid;
figure(2);
plot(estado(:,:,2));
title('Second Initial Position');
xlabel('Learning Steps');
grid;
figure(3);
plot(estado(:,:,3));
title('Third Initial Position');
xlabel('Learning Steps');
grid;
figure(4);
plot(estado(:,:,4));
title('Fourth Initial Position');
xlabel('Learning Step');
grid;
