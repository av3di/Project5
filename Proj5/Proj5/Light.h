#ifndef _LIGHT_H_
#define _LIGHT_H_

#include "Header.h"

class Light
{
public:
	int id;
	double angle_deg;
	Light(int n_id, double deg_angle);
	~Light();
	void setSpotLight(double d_x, double d_y, double d_z);
	void setSpotLightDirection(Vector3 &cp);
	void changeOpeningAngle(double deg_angle);
	void setColor(double a_r, double a_g, double a_b, double r, double g, double b, double opacity);
	void setPosition(double x, double y, double z, double type);
	void on();
	void off();
};

#endif;