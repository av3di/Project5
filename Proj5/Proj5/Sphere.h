#ifndef _SPHERE_H_
#define _SPHERE_H_

#include "Header.h"

class Sphere : public Model
{
public:
	Sphere();
	~Sphere();
	void draw(double radius, int slices, int stacks, bool sphere);
};

#endif