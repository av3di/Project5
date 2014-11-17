#include <stdio.h>
#include <iostream>
#include <GL/glut.h>

#include "Window.h"
#include "Cube.h"
#include "Matrix4.h"
#include "main.h"
#include "Camera.h"
#include "House.h"

using namespace std;

int Window::width  = 512;   // set window width in pixels here
int Window::height = 512;   // set window height in pixels here

int Window::fkey = 1;  // If 1, show cube, 2->show 1st cam, 3->show 2nd cam


//----------------------------------------------------------------------------
// Callback method called when system is idle.
void Window::idleCallback()
{
	Globals::cube.spin(0.1);   // rotate cube; if it spins too fast try smaller values and vice versa
	//Globals::hop.spin(0.5);
	//Globals::draco.spin(0.5);
	displayCallback();         // call display routine to show the cube
}

//----------------------------------------------------------------------------

void Window::processSpecialKeys(int key, int x, int y)
{
	glMatrixMode(GL_MODELVIEW);  // make sure we're in Modelview mode
	switch (key) {
	case GLUT_KEY_F1:
		Window::fkey = 1;
		break;
	case GLUT_KEY_F2:
		Window::fkey = 2;
		break;
	case GLUT_KEY_F3:
		Window::fkey = 3;
		break;
	case GLUT_KEY_F4:
		Window::fkey = 4;
		break;
	case GLUT_KEY_F5:
		Window::fkey = 5;
		break;
	}
}


// Callback method called by GLUT when graphics window is resized by the user
void Window::reshapeCallback(int w, int h)
{
  cerr << "Window::reshapeCallback called" << endl;
  width = w;
  height = h;
  glViewport(0, 0, w, h);  // set new viewport size
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(Globals::viewAngle, double(width)/(double)height, 1.0, 1000.0); // set perspective projection viewing frustum
  glTranslatef(0, 0, Globals::camZ);    // move camera back 20 units so that it looks at the origin (or else it's in the origin)
  glMatrixMode(GL_MODELVIEW);
}

//----------------------------------------------------------------------------
// Callback method called by GLUT when window readraw is necessary or when glutPostRedisplay() was called.
void Window::displayCallback()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // clear color and depth buffers
  glMatrixMode(GL_MODELVIEW);  // make sure we're in Modelview mode
  Matrix4 glmatrix;

  if (fkey == 1)
  {
	  glEnable(GL_LIGHTING);
	  glmatrix = Globals::cube.getMatrix();
	  glmatrix.transpose();
	  glLoadMatrixd(glmatrix.getPointer());
	  Globals::cube.draw();
  }
  else if (fkey == 2)
  {
	  glDisable(GL_LIGHTING);
	  glLoadMatrixd(Globals::cam1.getMatrix().getPointer());
	  Globals::h.draw();
  }
  else if (fkey == 3)
  {
	  glDisable(GL_LIGHTING);
	  glLoadMatrixd(Globals::cam2.getMatrix().getPointer());
	  Globals::h.draw();
  }
  else if (fkey == 4)
  {
	  glmatrix = Globals::hop.getMatrix();
	  glmatrix.transpose();
	  glLoadMatrixd(glmatrix.getPointer());

	  glDisable(GL_LIGHTING);
	  Globals::hop.draw();
  }
  else if (fkey == 5)
  {
	  glmatrix = Globals::draco.getMatrix();
	  glmatrix.transpose();
	  glLoadMatrixd(glmatrix.getPointer());
	  glDisable(GL_LIGHTING);
	  Globals::draco.draw();
  }
}

void Window::processNormalKeys(unsigned char key, int x, int y){
	Model *currentM;
	if (fkey == 1)
		currentM = &Globals::cube;
	else if (fkey == 2)
		currentM = &Globals::h;
	else if (fkey == 3)
		currentM = &Globals::h;
	else if (fkey == 4)
		currentM = &Globals::hop;
	else if (fkey == 5)
		currentM = &Globals::draco;
	switch (key){
	case 27:
		exit(0);
		break;
	case 't':
		currentM->changeCounter();
		break;
	case 'x':
		currentM->translate(-1.0, 0.0, 0.0);
		break;
	case 'X':
		currentM->translate(1.0, 0.0, 0.0);
		break;
	case 'Z':
		currentM->translate(0.0, 0.0, 1.0);
		break;
	case 'z':
		currentM->translate(0.0, 0.0, -1.0);
		break;
	case 'y':
		currentM->translate(0.0, -1.0, 0.0);
		break;
	case 'Y':
		currentM->translate(0.0, 1.0, 0.0);
		break;
	case 's':
		currentM->scale(0.5, 0.5, 0.5);
		break;
	case'S':
		currentM->scale(1.5, 1.5, 1.5);
		break;
	case 'o':
		currentM->rotate(10);
		break;
	case 'O':
		currentM->rotate(-10);
		break;
	case 'r':
		currentM->getMatrix().makeRotateY(1.0);
		//currentM->reset();
		break;
	}
}