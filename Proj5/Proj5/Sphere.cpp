#include "Header.h"


Sphere::Sphere()
{
}


Sphere::~Sphere()
{
}

void Sphere::draw(double radius, int slices, int stacks, bool sphere)
{
	if (sphere)
		glutSolidSphere(radius, slices, stacks);
	else
		glutSolidCone(radius, 2, slices, stacks);
}
