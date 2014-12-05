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

  Vector3 l, X, Y, Z; //usually d, look at point aka near plane normal
  double nh;

  double plane_distance = 0.0;
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

  using namespace Globals;
 /* Vector3 p, u;
  p.setX(0); p.setY(0); p.setZ(20);
  Globals::l.setX(0); Globals::l.setY(0); Globals::l.setZ(-1);
  u.setX(0); u.setY(1); u.setZ(0);

  Vector3 dir, nc, fc;
  Globals::Z = p - Globals::l;
  Globals::Z.normalize();

  Globals::X = u.cross(Z);
  Globals::X.normalize();

  Globals::Y = Globals::Z.cross(X);
  double nearD = -20.0;
  double nh, nw;
  Globals::Z.scale(nearD);
  nc = p - Globals::Z;*/

  /*double tang = tan(Globals::viewAngle * M_PI / 180 * 0.5);
  Globals::nh = nearD * tang;*/

  // double nw = Globals::nh * (Window::width / Window::height);

  //Vector3 ntl, ntr, nbl, nbr;
  // Globals::Y.scale(Globals::nh);
  // Globals::X.scale(nw);
  /*ntl = nc + Globals::Y - Globals::X;
  ntr = nc + Globals::Y + Globals::X;
  nbl = nc - Globals::Y - Globals::X;
  nbr = nc - Globals::Y + Globals::X;*/

  // Find distance of plane
  //Globals::plane_distance = (Globals::l.dot(nc)) * -1.0;
  ///////////////////////////////////////

  /*Globals::hop_material.setDiffandAmb(0.1, 0.0, 0.0, 1.0);
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
  */
  // Process the keys pressed
  glutKeyboardFunc(Window::processNormalKeys);
  glutSpecialFunc(Window::processSpecialKeys);
  glutMouseFunc(Window::processMouse);
  glutMotionFunc(Window::processMotion);

  glutMainLoop();
}

