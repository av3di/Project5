#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include <GL/glut.h>

#include "Window.h"
#include "Cube.h"
#include "Matrix4.h"
#include "main.h"
#include "vector3.h"
#include "Vector4.h"
#include "Camera.h"
#include "House.h"
#include "Bunny.h"
#include "Dragon.h"

using namespace std;

namespace Globals
{
  Cube cube;
  Camera cam1;
  Camera cam2;
  House h;
  Bunny hop;
  Dragon draco;
  double viewAngle = 60.0;
  int camZ = -20;
};

int main(int argc, char *argv[])
{
  float specular[]  = {1.0, 1.0, 1.0, 1.0};
  float shininess[] = {100.0};
  float position[]  = {0.0, 10.0, 1.0, 0.0};	// lightsource position
  
  glutInit(&argc, argv);      	      	      // initialize GLUT
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);   // open an OpenGL context with double buffering, RGB colors, and depth buffering
  glutInitWindowSize(Window::width, Window::height);      // set initial window size
  glutCreateWindow("OpenGL Cube");    	      // open window and set window title

  glEnable(GL_DEPTH_TEST);            	      // enable depth buffering
  glClear(GL_DEPTH_BUFFER_BIT);       	      // clear depth buffer
  glClearColor(0.0, 0.0, 0.0, 0.0);   	      // set clear color to black
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);  // set polygon drawing mode to fill front and back of each polygon
  glDisable(GL_CULL_FACE);     // disable backface culling to render both sides of polygons
  glShadeModel(GL_SMOOTH);             	      // set shading to smooth
  glMatrixMode(GL_PROJECTION); 
  
  // Generate material properties:
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
  glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
  glEnable(GL_COLOR_MATERIAL);
  
  // Generate light source:
  glLightfv(GL_LIGHT0, GL_POSITION, position);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  
  // Install callback functions:
  glutDisplayFunc(Window::displayCallback);
  glutReshapeFunc(Window::reshapeCallback);
  glutIdleFunc(Window::idleCallback);

  // Initialize all matrices:
  Globals::cube.getMatrix().identity();
  Globals::cam1.getMatrix().identity();
  Globals::cam2.getMatrix().identity();
  Globals::h.getMatrix().identity();
  Globals::hop.getMatrix().identity();
  Globals::draco.getMatrix().identity();

  // Parse the xyz files and store coords
  Globals::hop.parseFile("bunny.xyz");
  Globals::draco.parseFile("dragon.xyz");

  // Translate and scale the point models
  Globals::hop.moveToOrigin();
  Globals::hop.fitToWindow();

  Globals::draco.moveToOrigin();
  Globals::draco.fitToWindow();

  // Construct the F1 Camera
  Globals::cam1.sete(0, 10, 10);
  Globals::cam1.setd(0, 0, 0);
  Globals::cam1.setup(0, 1, 0);
  Globals::cam1.constructMatrix();
  Globals::cam1.inverse();

  // Construct the F2 Camera
  Globals::cam2.sete(-15, 5, 10);
  Globals::cam2.setd(-5, 0, 0);
  Globals::cam2.setup(0, 1, 0.5);

  Globals::cam2.constructMatrix();
  Globals::cam2.inverse();

  // Process the keys pressed
  glutKeyboardFunc(Window::processNormalKeys);
  glutSpecialFunc(Window::processSpecialKeys);

  glutMainLoop();
}

