#ifndef _MAIN_H_
#define _MAIN_H_

//#include "GL\GLee.h"
#include "vector3.h"
#include "Vector4.h"
#include "Matrix4.h"
#include "Model.h"
#include "PointModel.h"
#include "cube.h"
#include "Camera.h"
#include "House.h"
#include "Bunny.h"
#include "Dragon.h"
#include "Bear.h"
#include "Light.h"
#include "Sphere.h"
#include "Material.h"
#include "Window.h"
#include "GL\glut.h"

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

	extern Material little_bear_material;
	extern Material draco_material;
	extern Material hop_material;

	extern double viewAngle;
	extern int camZ;
}

#endif