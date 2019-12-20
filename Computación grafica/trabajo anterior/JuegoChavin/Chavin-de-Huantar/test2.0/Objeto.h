#include "math.h"
class Objeto{
public:
	Objeto(float nx, float ny, float nz,float nr) { Init(nx,ny,nz,nr); }

	void Init(float nx,float ny,float nz,float nr);
	void SetPos(float x, float y, float z);
	void setR(float nr);
   void GetPos(float &x, float &y, float &z);

  	//verificar la colision con el objeto1
	static bool colision(Objeto ob1,Objeto ob2){
		if(sqrt( pow(ob1.x-ob2.x,2)+pow(ob1.y-ob2.y,2)+pow(ob1.z-ob2.z,2))<=ob1.r+ob2.r)
			return 1;
		else
			return 0;
	}
private:
	float x, y, z;   // Position
	float r; //radio
};

class Cubo{
public:
	Cubo(float x,float y,float z,float dx,float dy,float dz){};

	void SetPos(float x, float y, float z){
		this->x=x;
		this->y=y;
		this->z=z;
	}
	void GetPos(float &x, float &y, float &z){
		x=this->x;
		y=this->y;
		z=this->z;
	}
private:
	float x,y,z,dx,dy,dz;
}
