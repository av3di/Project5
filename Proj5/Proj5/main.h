#ifndef _MAIN_H_
#define _MAIN_H_

#include "Header.h"

namespace Globals
{
	extern Bunny hop;
	extern Dragon draco;
	extern Bear little_bear;

	extern Light point_light;
	extern Light spot_light;

	extern Sphere point;
	extern Sphere spot;

	extern Material little_bear_material;
	extern Material draco_material;
	extern Material hop_material;

	extern double viewAngle;
	extern int camZ;
}

#endif