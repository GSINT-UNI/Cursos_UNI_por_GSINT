#include <iostream>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <cmath>
#include <string>
using namespace std;

float pi;

float f(float x)
{
  return(sin(3*pi * x));
}

int main()
{
  const int n = 50, m = 500;
  int i, j;
  float h , k = 0.002;
  h=1./n;
  float t, x, rho;
  float U[n],V[n],W[n];
  ofstream fileout;
  static char outname[256];

  U[0] = U[n] = 0;
  V[0] = V[n] = 0;
  W[0] = W[n] = 0;

  rho = (k * k) / (h * h);
  pi = 4.0 * atan(1.0);

  fileout.open("0001.dat"); 
  for (i = 1; i <= n - 1; i++)
  {
     x = i * h;
     W[i] = f(x);
     V[i] = 0.5 * (rho * ( f(x-h) + f(x+h) ) + 2 * (1 - rho) * f(x) );

      fileout<<x<<" "<<V[i]<<endl;
  }
 fileout.close();

  for (j = 2; j <= m; j++)
  {
    sprintf(outname,"%04d.dat",j);
    fileout.open(outname); 
    for (i = 1; i <= n - 1; i++)
    {
      x = i * h;
      U[i] = rho * (V[i+1] + V[i-1]) + 2 * (1 - rho) * V[i] - W[i];
      fileout<<x<<" "<<U[i]<<endl;
    }
    fileout.close();

    for (i = 1; i <= n - 1; i++)
    {
      W[i] = V[i];
      V[i] = U[i];
    }

  }

}









