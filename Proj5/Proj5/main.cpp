#include "Header.h"

using namespace std;

namespace Globals
{
  Light point_light(GL_LIGHT0, 180.0); // 180.0 dummy value - not going to be used
  double viewAngle = 60.0;
  int camZ = -20;
};

int main(int argc, char *argv[])
{
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
  
  glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
  glEnable(GL_NORMALIZE);



  // Install callback functions:
  glutDisplayFunc(Window::displayCallback);
  glutReshapeFunc(Window::reshapeCallback);
  glutIdleFunc(Window::idleCallback);

  Globals::point_light.setColor(0.0, 0.0, 0.25, 0.0, 0.0, 1.0, 1.0);
  Globals::point_light.setPosition(1.0, 1.0, 1.0, 1.0);
  Globals::point_light.on();

  // Process the keys pressed
  glutKeyboardFunc(Window::processNormalKeys);
  Window::LoadGLTextures();


  glutMainLoop();
}

