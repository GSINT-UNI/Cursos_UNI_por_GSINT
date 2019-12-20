""#include <iostream>
#include "Objeto.cpp"

using namespace std;

int main (int argc, char **argv) {
   Objeto ob1(2,0,0,1);
   Objeto ob2(0,0,0,1);
   if (Objeto::colision(ob1,ob2)==true){
      cout << "se intersectan" << endl;
   }else
      cout << "no se intersectan"<<endl;

}
