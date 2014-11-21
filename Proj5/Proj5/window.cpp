#include "Header.h"

using namespace std;

int Window::width  = 512;   // set window width in pixels here
int Window::height = 512;   // set window height in pixels here

bool Window::left_button = false; // tells whether the user clicked the left or right mouse button
bool Window::trackball_model = true;

int Window::last_x = 0, Window::last_y = 0;

Model *currentM = &Globals::hop;
bool Window::per_pixel = false;
int Window::fkey = 1;  // If 1, show bunny, 2->show dragon, 3->show bear

//----------------------------------------------------------------------------
// Callback method called when system is idle.
void Window::idleCallback()
{
	displayCallback();         // call display routine to show the cube
}

//----------------------------------------------------------------------------

void Window::processSpecialKeys(int key, int x, int y)
{
	glMatrixMode(GL_MODELVIEW);  // make sure we're in Modelview mode
	switch (key) {
	case GLUT_KEY_F1:
		Window::fkey = 1;
		currentM = &Globals::hop;
		break;
	case GLUT_KEY_F2:
		Window::fkey = 2;
		currentM = &Globals::draco;
		break;
	case GLUT_KEY_F3:
		Window::fkey = 3;
		currentM = &Globals::little_bear;
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

  if (per_pixel)
	  Globals::point_light.off();
  else
	  Globals::point_light.on();

  glmatrix = Globals::point.getMatrix();
  glmatrix.transpose();
  glLoadMatrixd(glmatrix.getPointer());
  Globals::point.draw(1.0, 20, 20, true);

  glmatrix = Globals::spot.getMatrix();
  glmatrix.transpose();
  glLoadMatrixd(glmatrix.getPointer());
  Globals::point.draw(1.0, 20, 20, false);

  if (fkey == 1)
  {
	  glmatrix = Globals::hop.getMatrix();
	  glmatrix.transpose();

	  Globals::hop_material.on();
	  glLoadMatrixd(glmatrix.getPointer());

	  Globals::hop.draw();
  }
  else if (fkey == 2)
  {
	  glmatrix = Globals::draco.getMatrix();
	  glmatrix.transpose();

	  Globals::draco_material.on();
	  glLoadMatrixd(glmatrix.getPointer());
	  Globals::draco.draw();
  }
  else if (fkey == 3)
  {
	  glmatrix = Globals::little_bear.getMatrix();
	  glmatrix.transpose();

	  Globals::little_bear_material.on();
	  glLoadMatrixd(glmatrix.getPointer());
	  Globals::little_bear.draw();
  }
}

void Window::trackBallMapping(Vector3 &cp)
{
	Vector3 copy;
	double d_height = height;
	double d_width = width;
	double d;
	copy.setX(cp.getX()); copy.setY(cp.getY());  copy.setZ(cp.getZ());
	cp.setX(((2.0  * copy.getX()) - d_width)/d_width);
	cp.setY((d_height - (2.0 * copy.getY()))/d_height);
	cp.setZ(0.0);
	d = cp.length();
	d = (d < 1.0) ? d : 1.0;
	cp.setZ(sqrt(1.001 - d * d));
	cp.normalize();
}
void Window::processMouse(int button, int state, int x, int y)
{
	static Vector3 last_point;
	if (state == GLUT_DOWN)
	{
		if (button == GLUT_LEFT_BUTTON)
			left_button = true;
		else
			left_button = false;
		last_x = x;
		last_y = y;
		last_point.setX(last_x);
		last_point.setY(last_y);
		last_point.setZ(0);
	}
	else // mouse button released
	{
		if (button == GLUT_LEFT_BUTTON)
		{
			if (!trackball_model) // make spotlight point to where mouse is pointing
			{
				Vector3 current_point;
				current_point.setX(x - (Window::width/2));
				current_point.setY((y - Window::height / 2) * -1);
				current_point.setZ(-1.0);
				/*double distance_to_plane = (Globals::l.dot(current_point)) + Globals::plane_distance;
				Vector3 plane_normal;
				plane_normal.setX(Globals::l.getX());
				plane_normal.setY(Globals::l.getY());
				plane_normal.setZ(Globals::l.getZ());
				plane_normal.scale(distance_to_plane);
				Vector3 projected_near_pt = current_point - plane_normal;*/

				//projected_near_pt.setY(projected_near_pt.getY() * -1.0);
				//Globals::spot_light.setSpotLightDirection(projected_near_pt);
				//projected_near_pt.print("new point is");

				//double t = (-1 * ((current_point.dot(Globals::l)) + Globals::plane_distance)) / (current_point.dot(projected_near_pt));
				/*projected_near_pt.scale(t);
				projected_near_pt = current_point + projected_near_pt;*/
				//current_point.setZ(-1.0);
				Globals::spot_light.setSpotLightDirection(current_point);
				//current_point.print("new direction is");
			}
		}
	}
}

void Window::processMotion(int x, int y)
{
	Vector3 direction;
	Vector3 last_point;
	Vector3 current_point;

	last_point.setX(last_x);
	last_point.setY(last_y);
	last_point.setZ(0);

	current_point.setX(x);
	current_point.setY(y);
	current_point.setZ(0);

	trackBallMapping(last_point);
	trackBallMapping(current_point);

	if (left_button) // Rotation
	{
		if (trackball_model) // rotate model
		{
			direction = current_point - last_point;
			double velocity = direction.length();
			if (velocity > 0.0001)
			{
				Vector3 rotation_axis = last_point.cross(current_point);
				double rotation_angle = velocity * 90.0;

				rotation_axis.normalize();
				currentM->rotate(rotation_axis, rotation_angle);
			}
		}
	}
	else 
	{
		if (trackball_model) // Right mouse button for scale
		{
			double diff = current_point.getY() - last_point.getY();
			double zoom_factor = 1.0 + diff + 0.0008;
			currentM->scale(zoom_factor, zoom_factor, zoom_factor);
		}
		else // widen or narrow spotlight angle
		{
			double diff = current_point.getY() - last_point.getY();
			double zoom_factor = 1.0 + diff + 0.0008;
			if (diff < 0)
				zoom_factor = zoom_factor * -1.0; // narrow the spotlight, if mouse moved down
			Globals::spot_light.changeOpeningAngle(zoom_factor);
		}
	}
	last_x = x;
	last_y = y;
}

void Window::processNormalKeys(unsigned char key, int x, int y){
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
		currentM->rotateZ(10);
		break;
	case 'O':
		currentM->rotateZ(-10);
		break;
	case 'e':
		currentM->rotateY(10);
		break;
	case 'E':
		currentM->rotateY(-10);
		break;
	case 'r':
		currentM->getMatrix().makeRotateY(1.0);
		//currentM->reset();
		break;
	case 'p':
		if (per_pixel)
			per_pixel = false;
		else
			per_pixel = true;
		break;
	case 'm':
		trackball_model = true;
		break;
	case 'l':
		trackball_model = false;
		break;
	}
}