#include <stdio.h>
#include <math.h>
#include <GL/glut.h>
#include "Camera.h"

void Camera::Init()
{
	m_yaw = 0.0;
	m_pitch = 0.0;

	SetPos(0, 0, 0);
}

void Camera::Refresh3p()
{
	// Camera parameter according to Riegl's co-ordinate system
	// x/y for flat, z for height
	m_lx = cos(m_yaw) * cos(m_pitch);
	m_ly = sin(m_pitch);
	m_lz = sin(m_yaw) * cos(m_pitch);

	m_strafe_lx = cos(m_yaw - M_PI_2);
	m_strafe_lz = sin(m_yaw - M_PI_2);

	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0,1.0,0.1,500.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(m_x - 4*m_lx-m_strafe_lx, m_y - 4*m_ly, m_z - 4*m_lz-m_strafe_lz, m_x-0.5*m_strafe_lx, m_y, m_z-0.5*m_strafe_lz, 0.0,1.0,0.0);

	//printf("Camera: %f %f %f Direction vector: %f %f %f\n", m_x, m_y, m_z, m_lx, m_ly, m_lz);
}

void Camera::Refresh()
{
	// Camera parameter according to Riegl's co-ordinate system
	// x/y for flat, z for height
	m_lx = cos(m_yaw) * cos(m_pitch);
	m_ly = sin(m_pitch);
	m_lz = sin(m_yaw) * cos(m_pitch);

	m_strafe_lx = cos(m_yaw - M_PI_2);
	m_strafe_lz = sin(m_yaw - M_PI_2);

	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
 	glLoadIdentity();
	gluPerspective(60.0,1.0,0.1,500.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(m_x, m_y, m_z, m_x + m_lx, m_y + m_ly, m_z + m_lz, 0.0,1.0,0.0);

	//printf("Camera: %f %f %f Direction vector: %f %f %f\n", m_x, m_y, m_z, m_lx, m_ly, m_lz);
}

void Camera::SetPos(float x, float y, float z)
{
	m_x = x;
	m_y = y;
	m_z =z;

	Refresh();
}

void Camera::GetPos(float &x, float &y, float &z)
{
    x = m_x;
    y = m_y;
    z = m_z;
}
float Camera::GetY(){
	return m_y;
}

void Camera::GetDirectionVector(float &x, float &y, float &z)
{
    x = m_lx;
    y = m_ly;
    z = m_lz;
}

void Camera::setHeight(float h){
	m_y = h;
}
float Camera::GetYaw(){
	return m_yaw;
}

float Camera::GetPitch(){
	return m_pitch;
}

void Camera::Move(float incr)
{
    float lx = cos(m_yaw);//*cos(m_pitch);
    float ly = sin(m_pitch);
    float lz = sin(m_yaw);//*cos(m_pitch);

	m_x = m_x + incr*lx;
	//m_y = m_y + incr*ly;
	m_z = m_z + incr*lz;

	Refresh();
}

void Camera::getMove(float incr,float &nx,float &ny,float &nz){
	float lx = cos(m_yaw);//*cos(m_pitch);
	float lz = sin(m_yaw);//*cos(m_pitch);

  nx = m_x + incr*lx;
  nz = m_z + incr*lz;
  ny = m_y;
}

void Camera::Strafe(float incr)
{
	m_x = m_x + incr*m_strafe_lx;
	m_z = m_z + incr*m_strafe_lz;

	Refresh();
}
void Camera::getStrafe(float incr,float &nx,float &ny,float &nz)
{
	nx = m_x + incr*m_strafe_lx;
	nz = m_z + incr*m_strafe_lz;
	ny = m_y;
}

void Camera::Fly(float incr)
{
	m_y = m_y + incr;

	Refresh();
}

void Camera::RotateYaw(float angle)
{
	m_yaw += angle;

	Refresh();
}

void Camera::RotatePitch(float angle)
{
    const float limit = 89.0 * M_PI / 180.0;

	m_pitch += angle;

    if(m_pitch < -limit)
        m_pitch = -limit;

    if(m_pitch > limit)
        m_pitch = limit;

	Refresh();
}

void Camera::SetYaw(float angle)
{
	m_yaw = angle;

	Refresh();
}

void Camera::SetPitch(float angle)
{
    m_pitch = angle;

    Refresh();
}
