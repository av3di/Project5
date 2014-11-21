#include "Header.h"

Light::Light(int n_id, double deg_angle) : id(n_id), angle_deg(deg_angle)
{
}


Light::~Light()
{
}

void Light::setSpotLight(double d_x, double d_y, double d_z)
{
	glLightf(id, GL_SPOT_CUTOFF, angle_deg);
	GLfloat spot_direction[] = { d_x, d_y, d_z };
	glLightfv(id, GL_SPOT_DIRECTION, spot_direction);
}

void Light::setSpotLightDirection(Vector3 &cp)
{
	GLfloat spot_direction[] = { cp.getX(), cp.getY(), cp.getZ() };
	glLightfv(id, GL_SPOT_DIRECTION, spot_direction);
}

void Light::changeOpeningAngle(double deg_angle)
{
	glLightf(id, GL_SPOT_CUTOFF, deg_angle + angle_deg);
	angle_deg = deg_angle + angle_deg;
}
void Light::setColor(double a_r, double a_g, double a_b, double r, double g, double b, double opacity)
{
	GLfloat light_ambient[] = { a_r, a_g, a_b, opacity};
	GLfloat light_diffuse[] = { r, g, b, opacity };
	GLfloat light_specular[] = { r, g, b, opacity };
	glLightfv(id, GL_AMBIENT, light_ambient);
	glLightfv(id, GL_DIFFUSE, light_diffuse);
	glLightfv(id, GL_SPECULAR, light_specular);
}

void Light::setPosition(double p_x, double p_y, double p_z, double type)
{

	GLfloat light_position[] = { p_x, p_y, p_z, type };
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_SMOOTH);
	glLightfv(id, GL_POSITION, light_position);
}

void Light::on()
{
	glEnable(GL_LIGHTING);
	glEnable(id);
}

void Light::off()
{
	glDisable(id);
	//glDisable(GL_LIGHTING);
}
