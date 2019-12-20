class Camera{
public:
	Camera() { Init(); }
	~Camera(){}

	void Init();
	void Refresh();
	void Refresh3p();
	void SetPos(float x, float y, float z);
    void GetPos(float &x, float &y, float &z);
    void GetDirectionVector(float &x, float &y, float &z);
	void SetYaw(float angle);
	void SetPitch(float angle);
		float GetYaw();
		float GetPitch();
	void setHeight(float h);
		float GetY();
	// Navigation
	void Move(float incr);
	void Strafe(float incr);
	void Fly(float incr);
	void Move3p(float incr);
	void Strafe3p(float incr);
	void Fly3p(float incr);
	void RotateYaw(float angle);
	void RotatePitch(float angle);
	void RotateYaw3p(float angle);
	void RotatePitch3p(float angle);
	void getMove(float incr,float &nx,float &ny,float &nz);
	void getStrafe(float incr,float &nx,float &ny,float &nz);
private:
	float m_x, m_y, m_z;   // Position
    float m_lx, m_ly, m_lz; // Direction vector of where we are looking at
	float m_yaw, m_pitch; // Various rotation angles
	float m_strafe_lx, m_strafe_lz; // Always 90 degree to direction vector
};
