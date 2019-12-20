% Validation of a trained neural network for driving a car.
% The car starts for arbitraty initial positions and must achieve the final desired position.
% The neural network was trained so that the car achieves the desired position:
% x*=0, phi* = pi/2.

clear;
clc;
close all;



ymax = 50;

xini = input('Initial coordinate x [-18 18] : ');
yini = input('Initial coordinate y [0 20]   : ');
phiini = input('Initial inclination phi (degrees -90<>270) : ');
phiini = phiini*pi/180;
xast = input('Desired x coordinate: ');

x_ini = [ xini         % x coordinate
            yini         % y coordinate
            phiini ];    % Phi angle
       
ne = 2;    % No bias
nm = 50;
ns = 1;

load redcarro;

  
   r = 0.01;
   L = 2;
   deltamax = 50;       % Maximum steering anle 
   umax = tan(deltamax*pi/180);   
   
   x = x_ini;
   k = 1;
   fiast = pi/2;
   while( x(2,1) < ymax )
       in_red = [ x(1,1) - xast;
                     x(3,1) - fiast ];
      m = v'*in_red;
      n = 2.0./(1 + exp(-(m-c)./a)) - 1;  
      out_red = w'*n;
      if( out_red > umax)
          out_red = umax;
      elseif(out_red < -umax )
          out_red = -umax;
      end    
      u(k,1) = out_red';
      posX(k,1) = x(1,1);
      posY(k,1) = x(2,1);
      phi(k,1)  = x(3,1);
      
      x(1,1) = x(1,1) + r*cos(x(3,1));
      x(2,1) = x(2,1) + r*sin(x(3,1));
      x(3,1) = x(3,1) - r/L*u(k,1);
      k = k + 1;
   end
   
   npx = length(posX);
   figure(1);
   axis([ -20 20 0 40 ]);   
   xlabel('Coordinate X');
   ylabel('Coordinate Y');
   title('Robot Trajectory');
   grid;
   hold on;  
   for k = 1:15:npx
      plot(posX(k,1),posY(k,1),'o','Linewidth',3);
      pause(0.0001);
   end   
   
   delta = atan(u) * 180/pi;
   figure(2);
   plot(delta);
   grid;
   title('Steering Angle');
   xlabel('Time (sec)');
   ylabel('Degrees');
   