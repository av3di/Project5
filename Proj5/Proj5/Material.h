#ifndef _MATERIAL_H_
#define _MATERIAL_H_

#include "Header.h"

class Material
{
public:
	GLfloat mat_amb_diff[4];
	GLfloat mat_specular[4];
	GLfloat low_shininess[1]; // 0 to 128

	Material();
	~Material();
	void setDiffandAmb(double r, double g, double b, double opacity);
	void setSpec(double r, double g, double b, double opacity, double shininess);
	void on();
};

#endif
