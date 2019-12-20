#include "iostream"
#include "math.h"
using namespace std;
class Elemento{
public:
   Elemento(float x,float y,float z,float r){
      ex = x;
      ey = y;
      ez = z;
      er = r;

   }
   void setPos(float x,float y,float z);
   void getPos(float &x,float &y,float &z);
   void setR(float r);
   void getR(float &r);
   float getY();
   static bool compare(Elemento e1,Elemento e2){
      if(sqrt( pow(e1.ex-e2.ex,2)+pow(e1.ey-e2.ey,2)+pow(e1.ez-e2.ez,2))<=e1.er+e2.er)
         return 1;
      else
         return 0;
   }
   Elemento* sig;
private:
   float ex,ey,ez;
   float er;
};

void Elemento::setR(float r){
   this->er=r;
}

void Elemento::getR(float &r){
   r=er;
}

float Elemento::getY(){
   return ey;
}
void Elemento::setPos(float x,float y,float z){
   this->ex = x;
   this->ey = y;
   this->ez = z;
}

void Elemento::getPos(float &x,float &y,float &z){
   x = ex;
   y = ey;
   z = ez;
}

class Lista{
public:
   Lista(){
      inicio = NULL;
      fin = NULL;
      tam=0;
   }

   Elemento* inicio;
   Elemento* fin;
   int tam;
   //comparacion de listas
   static bool compare(Lista l1, Lista l2){
      Elemento* act1 = l1.inicio;
      Elemento* act2;
      for (int i = 0; i < l1.tam && act1!=NULL; i++){
         act2 = l2.inicio;
         for (int j = 0; j < l2.tam && act2!=NULL; j++) {
            if (Elemento::compare(*act1,*act2))
               return true;
            else
               act2 = act2->sig;
         }
         act1= act1->sig;
      }
      return false;
   }
   void agregar(float x,float y,float z,float r);
   void quitar();
};

void Lista::agregar(float x,float y,float z,float r){
   Elemento* nuevo_elemento = new Elemento(x,y,z,r);
   nuevo_elemento->sig=NULL;
   if (inicio == NULL){
      tam = 1;
      inicio = nuevo_elemento;
   }else {
      tam++;
      fin->sig = nuevo_elemento;
   }
   fin = nuevo_elemento;
}



class Piso{
public:
   Piso(float nx,float ny,float nz,float na,float nb){
      x = nx;
      y = ny;
      z = nz;
      a = na;
      b = nb;
   }
   void setPos(float nx,float ny,float nz);
   void getPos(float &nx,float &ny,float &nz);
   void setBounds(float na,float nb);
   void getBounds(float &na,float &nb);
   float getY();

   static bool compare(Piso p, Elemento e){
      float x,y,z,r;
      e.getPos(x,y,z);
      e.getR(r);
      if (p.x <= x + r && p.z <= z + r ){
         if(x - r <= p.x + p.a && z - r <= p.z + p.b){
            if(p.y <= y + r && y - r <= p.y)
               return true;
         }
      }
      return false;
   }

private:
   float x,y,z,a,b;

};

void Piso::setPos(float nx,float ny,float nz){
   this->x = nx;
   this->y = ny;
   this->z = nz;
}

void Piso::getPos(float &nx,float &ny,float &nz){
   nx = x;
   ny = y;
   nz = z;
}

float Piso::getY(){
   return y;
}
void Piso::setBounds(float na,float nb){
   a = na;
   b = nb;
}

void Piso::getBounds(float &na,float &nb){
   na = a;
   nb = b;
}

class Pared{
public:
   Pared(float nx,float ny,float nz,float na,float nb,char nd){
      x = nx;
      y = ny;
      z = nz;
      a = na;//anchura en x o z
      b = nb;//altura
      d = nd;
   }
   void setPos(float nx,float ny,float nz);
   void getPos(float &nx,float &ny,float &nz);
   void setBounds(float na,float nb);
   void getBounds(float &na,float &nb);
   float getY();

   static bool compare(Pared p, Lista l){
      if(p.d == 'z'){
         float x,y,z,r;
         Elemento * act = l.inicio;
         for (int i=0;i<l.tam;i++){
            act->getPos(x,y,z);
            act->getR(r);
            if (p.y <= y + r && p.z <= z + r ){
               if(y - r <= p.y + p.b && z - r <= p.z + p.a){
                  if(p.x <= x + r && x - r <= p.x)
                     return true;
               }
            }
            act = act->sig;
         }
         return false;
      }else{
         float x,y,z,r;
         Elemento * act = l.inicio;
         for (int i=0;i<l.tam;i++){
            act->getPos(x,y,z);
            act->getR(r);
            if (p.x <= x + r && p.y <= y + r ){
               if(x - r <= p.x + p.a && y - r <= p.y + p.b){
                  if(p.z <= z + r && z - r <= p.z)
                     return true;
               }
            }
            act = act->sig;
         }
         return false;

      }
   }
   static bool compare(Pared p, Elemento* e){
      if(p.d == 'z'){
         float x,y,z,r;
         e->getPos(x,y,z);
         e->getR(r);
         if (p.y <= y + r && p.z <= z + r ){
            if(y - r <= p.y + p.b && z - r <= p.z + p.a){
               if(p.x <= x + r && x - r <= p.x)
                  return true;
            }
         }
         return false;
      }else{
         float x,y,z,r;
         e->getPos(x,y,z);
         e->getR(r);
         if (p.x <= x + r && p.y <= y + r ){
            if(x - r <= p.x + p.a && y - r <= p.y + p.b){
               if(p.z <= z + r && z - r <= p.z)
                  return true;
            }
         }
         return false;

      }
   }
private:
   float x,y,z,a,b;
   char d; //direccion x o z
};

void Pared::setPos(float nx,float ny,float nz){
   this->x = nx;
   this->y = ny;
   this->z = nz;
}

void Pared::getPos(float &nx,float &ny,float &nz){
   nx = x;
   ny = y;
   nz = z;
}

float Pared::getY(){
   return y;
}
void Pared::setBounds(float na,float nb){
   a = na;
   b = nb;
}

void Pared::getBounds(float &na,float &nb){
   na = a;
   nb = b;
}



class Cuerpo{
public:
   Cuerpo(bool s,bool g, bool c){
      solid = s;
      gravity = g;
      colition = c;
   }
   Lista list;
   Lista test_list;
   void refreshColitionCaracter(float x, float y, float z);

private:
   bool solid;
   bool gravity;
   bool colition;

};

void Cuerpo::refreshColitionCaracter(float x, float y, float z){
   Elemento* act = list.inicio;
   act->setPos(x,y,z);
   act = act->sig;
   act->setPos(x,y-0.5,z);
   act = act->sig;
   act->setPos(x,y-1,z);
   act = act->sig;
   act->setPos(x,y-1.5,z);

}

class Bloque{
public:
   Bloque(float x,float y,float z,float a,float b,float c){
      this->x = x;
      this->y = y;
      this->z = z;
      this->a = a;
      this->b = b;
      this->c = c;
      p1 = new Pared (x,y,z,c,b,'z');
      p2 = new Pared (x+a,y,z,c,b,'z');
      p3 = new Pared (x,y,z,a,b,'x');
      p4 = new Pared (x,y,z+c,a,b,'x');
      pA = new Piso (x,y+b,z,a,c);
      pa = new Piso (x,y,z,a,c);
   }
   void setPos(float nx,float ny,float nz);
   void setBounds(float na,float nb,float nc);
   void getBounds(float &na,float &nb,float &nc);
   void getPos(float &nx,float &ny,float &nz);
   bool colition_test(Lista lprueba);
   bool colition_test(Elemento* e);
   bool compare_floor(Lista lprueba);
   bool compare_floor(Elemento* e);
   Piso* pA;
   Piso* pa;
   Pared* p1;
   Pared* p2;
   Pared* p3;
   Pared* p4;
private:
   float x,y,z;
   float a,b,c;
};

void Bloque::setBounds(float na,float nb,float nc){
   a = na;
   b = nb;
   c = nc;
}

void Bloque::getBounds(float &na,float &nb,float &nc){
   na = a;
   nb = b;
   nc = c;
}

void Bloque::setPos(float nx,float ny,float nz){
   this->x = nx;
   this->y = ny;
   this->z = nz;
}

void Bloque::getPos(float &nx,float &ny,float &nz){
   nx = x;
   ny = y;
   nz = z;
}

bool Bloque::colition_test(Lista lprueba){
   if(Pared::compare(*p1,lprueba))
      return true;
   else
      if(Pared::compare(*p2,lprueba))
         return true;
      else
         if(Pared::compare(*p3,lprueba))
            return true;
         else
            if(Pared::compare(*p4,lprueba))
               return true;
            else false;
}

bool Bloque::colition_test(Elemento* e){
   if(Pared::compare(*p1,e))
      return true;
   else
      if(Pared::compare(*p2,e))
         return true;
      else
         if(Pared::compare(*p3,e))
            return true;
         else
            if(Pared::compare(*p4,e))
               return true;
            else false;
}

bool Bloque::compare_floor(Lista lprueba){
   float x,y,z;
   Elemento* act = lprueba.inicio;
   for (int i = 0; i < lprueba.tam && act!=NULL; i++){
      if (Piso::compare(*pA,*act))
         return true;
      if(Piso::compare(*pa,*act))
         return true;
      act= act->sig;
   }
   return false;
}

bool Bloque::compare_floor(Elemento* e){
   if (Piso::compare(*pA, *e))
      return true;
   if(Piso::compare(*pa, *e))
      return true;
   return false;
}

class Bala{

public:
      Bala(float x,float y,float z,float v1,float v2,float v3){
      v[0] = v1;
      v[1] = v2;
      v[2] = v3;
      b = new Elemento(x,y,z,0.1);
      viva = false;
   }
   void getdir(float &vx,float &vy,float &vz);
   void setDir(float vx,float vy,float vz);

   bool viva;
   Elemento *b;
private:
   float v[3];
   float fin[3];
};

void Bala::setDir(float vx,float vy,float vz){
   v[0] = vx;
   v[1] = vy;
   v[2] = vz;
}

void Bala::getdir(float &vx,float &vy,float &vz){
   vx = v[0];
   vy = v[1];
   vz = v[2];
}





/*
void Bala::colition(){
   bool viva = true;
   float x,y,z;
   b->getPos(x,y,z);
   while (viva){


   }


}
Pared p1( 5,3,0,1,1,'z');
Pared p2( 6,3,0,1,1,'z');
Pared p3( 5,3,0,1,1,'x');
Pared p4( 5,3,1,1,1,'x');
Piso pisor(5,3,0,1,1);
Piso pisor2(5,4,0,1,1);


void gravedad(){
   if(test_gravity(lpersonaje,suelo)||test_gravity(lpersonaje,pisor)||test_gravity(lpersonaje,pisor2)){
      //toca el suelo
      v=0;
      t=0;
   }
   else{
      g_camera.setHeight(g_camera.GetY() +velocidad()*t-g*t*t/2);
   }

}

float velocidad (){
   return v = v - g*t;
}

int main2 (int argc, char **argv){
   Lista l1;
   Lista l2;
   Piso p(0,0,0,5,4);

   cout << "Escoja una de las opciones"<<endl;
   cout << "1.Agregar un elemento a la lista 1"<<endl;
   cout << "2.Agregar un elemento a la lista 2"<<endl;
   cout << "3.Mostrar elementos de la lista 1"<<endl;
   cout << "4.Mostrar elementos de la lista 2"<<endl;
   cout << "5.Verificar si existen colisiones entre las listas"<<endl;
   cout << "6.salir"<<endl;
   cout << "7. verificar si choca con el piso (0,0,0) (5,4)"<<endl;
   int op;
   cin >> op;
   float x,y,z,r;

   Elemento* act;

   while (true){
      switch (op){
         case 1:
            cout <<"Coloque las coordenadas y su radio"<<endl;
            cout <<"x: ";
            cin >> x;
            cout <<"y: ";
            cin >> y;
            cout <<"z: ";
            cin >> z;
            cout <<"r: ";
            cin >> r;
            cout << "agregando ( "<<x<<", "<<y<<", "<<z<<", "<<r<<")"<<endl;
            l1.agregar(x,y,z,r);
            break;
         case 2:
            cout <<"Coloque las coordenadas y su radio"<<endl;
            cout <<"x: ";
            cin >> x;
            cout <<"y: ";
            cin >> y;
            cout <<"z: ";
            cin >> z;
            cout <<"r: ";
            cin >> r;
            cout << "agregando ( "<<x<<", "<<y<<", "<<z<<", "<<r<<")"<<endl;
            l2.agregar(x,y,z,r);
            break;
         case 3:
            act = l1.inicio;
            cout<<"L1:"<<endl;
            for (int i = 0; i < l1.tam && act != NULL; i++){
               act->getPos(x,y,z);
               act->getR(r);
               cout <<"( "<<x<<", "<<y<<", "<<z<<") "<< r <<endl;
               act = act->sig;
            }
            break;
         case 4:
            act = l2.inicio;
            cout<<"L2:"<<endl;
            for (int i = 0; i < l2.tam && act != NULL; i++){
               act->getPos(x,y,z);
               act->getR(r);
               cout <<"( "<<x<<", "<<y<<", "<<z<<") "<< r <<endl;
               act = act->sig;
            }
            break;
         case 5:
            if(Lista::compare(l1,l2))
               cout<<"colisionan"<<endl;
            else
               cout<<"no colisionan"<<endl;
            break;
         case 6:
            return 0;
         case 7:
            if(Piso::compare(p,*l1.inicio))
               cout << "seps"<<endl;
            else
               cout << "nop"<<endl;
      }
      cout << "Escoja una de las opciones"<<endl;
      cout << "1.Agregar un elemento a la lista 1"<<endl;
      cout << "2.Agregar un elemento a la lista 2"<<endl;
      cout << "3.Mostrar elementos de la lista 1"<<endl;
      cout << "4.Mostrar elementos de la lista 2"<<endl;
      cout << "5.Verificar si existen colisiones entre las listas"<<endl;
      cout << "6.salir"<<endl;
      cin >> op;
   }
}
*/
