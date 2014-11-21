#ifndef _LIGHT_H_
#define _LIGHT_H_

#include "Header.h"

class Light
{
public:
	int id;
	Light(int n_id);
	~Light();
	void setSpotLight(double deg_angle, double d_x, double d_y, double d_z);
	void setColor(double a_r, double a_g, double a_b, double r, double g, double b, double opacity);
	void setPosition(double x, double y, double z, double type);
	void on();
	void off();
};

#endif;