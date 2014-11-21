#include "Header.h"

using namespace std;

namespace Globals
{
  Bunny hop;
  Dragon draco;
  Bear little_bear;

  Light point_light(GL_LIGHT0, 180.0); // 180.0 dummy value - not going to be used
  Light spot_light(GL_LIGHT1, 35);

  Material hop_material;
  Material draco_material;
  Material little_bear_material;

  Sphere point;
  Sphere spot;

  double viewAngle = 60.0;
  int camZ = -20;
};

int main(int argc, char *argv[])
{
 /* float specular[]  = {1.0, 1.0, 1.0, 1.0};
  float shininess[] = {100.0};
  float position[]  = {0.0, 10.0, 1.0, 0.0};	// lightsource position
  */
  
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
  /*glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
  glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
  glEnable(GL_COLOR_MATERIAL);*/
  
  // Generate light source:
  /*glLightfv(GL_LIGHT0, GL_POSITION, position);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);*/
 
  glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
  glEnable(GL_NORMALIZE);

  // Install callback functions:
  glutDisplayFunc(Window::displayCallback);
  glutReshapeFunc(Window::reshapeCallback);
  glutIdleFunc(Window::idleCallback);


  // Calculate the near plane for mouse and spotlight \\\\\\\\\\\\\

  Vector3 p, l, u;
  p.setX(0); p.setY(0); p.setZ(20); 
  l.setX(0); l.setY(0); l.setZ(-1); 
  u.setX(0); u.setY(1); u.setZ(0); 

  Vector3 dir, nc, fc, X, Y, Z;
  Z = p - l;
  Z.normalize();

  X = u.cross(Z);
  X.normalize();

  Y = Z.cross(X);
  double nearD = 4.0;
  double nh, nw;
  Z.scale(nearD);
  nc = p - Z;

  double tang = tan(Globals::viewAngle * M_PI / 180 * 0.5);
  nh = nearD * tang;
  nw = nh * (Window::width / Window::height);

  Vector3 ntl, ntr, nbl, nbr;
  Y.scale(nh);
  X.scale(nw);
  ntl = nc + Y - X;
  ntr = nc + Y + X;
  nbl = nc - Y - X;
  nbr = nc - Y + X;
  ///////////////////////////////////////

  Globals::hop_material.setDiffandAmb(0.1, 0.0, 0.0, 1.0);
  Globals::hop_material.setSpec(1.0, 0.0, 0.0, 0.0, 20.0);

  Globals::draco_material.setDiffandAmb(0.3, 0.0, 0.3, 1.0);
  Globals::draco_material.setSpec(0.1, 0.0, 0.1, 0.1, 1.0);

  Globals::little_bear_material.setDiffandAmb(0.0, 0.5, 0.5, 1.0);
  Globals::little_bear_material.setSpec(0.0, 0.5, 0.5, 1.0, 10.0);


  Globals::point_light.setColor(0.25, 0.25, 0.25, 1.0, 1.0, 1.0, 1.0);
  Globals::point_light.setPosition(0.0, 7.0, 7.0, 1.0);
  Globals::point_light.on();


  Globals::spot_light.setSpotLight(0.0, 0.0, -1.0); // set direction x, y, z
  Globals::spot_light.setColor(0.25, 0.25, 0.25, 1.0, 1.0, 1.0, 1.0);
  Globals::spot_light.setPosition(8.0, 0.0, 7.0, 1.0);
  Globals::spot_light.on();

  // Initialize all matrices:
  Globals::hop.getMatrix().identity();
  Globals::draco.getMatrix().identity();
  Globals::little_bear.getMatrix().identity();

  Globals::point.getMatrix().identity();
  Globals::point.translate(0.0, 7.0, 7.0);

  Globals::spot.getMatrix().identity();
  Globals::spot.translate(8.0, 0.0, 7.0);

  // Parse the xyz files and store coords
  Globals::hop.parseFile("bunny.obj");
  Globals::draco.parseFile("dragon.obj");
  Globals::little_bear.parseFile("bear.obj");

  // Translate and scale the point models
  Globals::hop.moveToOrigin();
  Globals::hop.fitToWindow();

  Globals::draco.moveToOrigin();
  Globals::draco.fitToWindow();

  Globals::little_bear.moveToOrigin();
  Globals::little_bear.fitToWindow();

  // Process the keys pressed
  glutKeyboardFunc(Window::processNormalKeys);
  glutSpecialFunc(Window::processSpecialKeys);
  glutMouseFunc(Window::processMouse);
  glutMotionFunc(Window::processMotion);

  glutMainLoop();
}

