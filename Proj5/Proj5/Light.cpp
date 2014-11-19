#include "Light.h"
#include "GL\glut.h"

Light::Light(int n_id) : id(n_id)
{
}


Light::~Light()
{
}

void Light::setSpotLight(double deg_angle, double d_x, double d_y, double d_z)
{
	glLightf(id, GL_SPOT_CUTOFF, deg_angle);
	GLfloat spot_direction[] = { d_x, d_y, d_z };
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spot_direction);
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
	glDisable(GL_LIGHTING);
}
