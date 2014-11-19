#ifndef _MAIN_H_
#define _MAIN_H_

#include "Cube.h"
#include "Camera.h"
#include "House.h"
#include "Bunny.h"
#include "Dragon.h"
#include "Bear.h"
#include "Light.h"
#include "Sphere.h"

namespace Globals
{
    extern Cube cube;
	extern Camera cam1;
	extern Camera cam2;
	extern House h;
	extern Bunny hop;
	extern Dragon draco;
	extern Bear little_bear;

	extern Light point_light;
	extern Light spot_light;

	extern Sphere point;
	extern Sphere spot;

	extern double viewAngle;
	extern int camZ;
}

#endif