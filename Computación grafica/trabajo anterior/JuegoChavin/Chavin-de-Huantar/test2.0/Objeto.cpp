#include "Objeto.h"
void Objeto::Init(float nx,float ny,float nz,float nr){
	x=nx;
	y=ny;
	z=nz;
	r=nr;
}
void Objeto::SetPos(float x, float y, float z){
	this->x=x;
	this->y=y;
	this->z=z;
}
void Objeto::setR(float nr){
	r = nr;
}
void Objeto::GetPos(float &x, float &y, float &z){
	x=this->x;
	y=this->y;
}
