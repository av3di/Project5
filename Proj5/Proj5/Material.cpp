#include "Header.h"

Material::Material()
{
}


Material::~Material()
{
}

void Material::setDiffandAmb(double r, double g, double b, double opacity)
{
	mat_amb_diff[0] = r; 
	mat_amb_diff[1] = g; 
	mat_amb_diff[2] = b; 
	mat_amb_diff[3] = opacity;

}

void Material::setSpec(double r, double g, double b, double opacity, double shininess)
{
	mat_specular[0] = r;
	mat_specular[1] = g;
	mat_specular[2] = b;
	mat_specular[3] = opacity;
	low_shininess[0] = shininess; // 0 to 128

}
void Material::on()
{

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, mat_amb_diff);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, low_shininess);
}
