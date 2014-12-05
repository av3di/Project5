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

Vector3 cp_0(-2, 0, 1);
Vector3 cp_1(-2, 0, 2);
Vector3 cp_2(-1, 0, 1);
Vector3 cp_3(-1, 0, 2);
Vector3 cp_4(1, 0, 1);
Vector3 cp_5(1, 0, 2);
Vector3 cp_6(2, 0, 1);
Vector3 cp_7(2, 0, 2);
Vector3 cp_8(-2, 0, -1);
Vector3 cp_9(-2, 0, -2);
Vector3 cp_10(-1, 0, -1);
Vector3 cp_11(-1, 0, -2);
Vector3 cp_12(1, 0, -1);
Vector3 cp_13(1, 0, -2);
Vector3 cp_14(2, 0, -1);
Vector3 cp_15(2, 0, -2);

double control_points[] = { -2, 0, 1, -2, 0, 2, -1, 0, 1, -1, 0, 2, 1, 0, 1, 1, 0, 2, 2, 0, 1, 2, 0, 2, -2, 0, -1, -2, 0, -2, -1, 0, -1, -1, 0, -2, 1, 0, -1, 1, 0, -2, 2, 0, -1, 2, 0, -2 };

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
	switch (key) {/*
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
		break;*/
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
  //glTranslatef(0, 0, Globals::camZ);    // move camera back 20 units so that it looks at the origin (or else it's in the origin)
  gluLookAt(0, 30, 0, 0, 0, 0, 0, 0, 90);
  glMatrixMode(GL_MODELVIEW);
}

//----------------------------------------------------------------------------

double Window::bernstizzlesCoeff(long n, long i, double t)
{
	//long n: is the degree of our curve, in the case of a cubic curve it is 3
	//long i: the index of the Bernstein coefficient and the control point
	//double t: is the time we are evaluating at

	//Calculate the Bernstein coefficient
	return combo(n, i) * pow(1.0 - t, n - i) * pow(t, i);
}

long Window::combo(long n, long i)
{
	//C(n, i) = n! / ((n-1)! * i!)
	return factorial(n) / (factorial(n - i) * factorial(i));
}

long Window::factorial(long n)
{
	long result = 1;

	//If n is 0, by definition 0! is equal to 1
	if (n <= 0)
		return result;

	//Calculate the factorial, n * n-1 * n-2 * ... * 1
	for (long i = n; i > 0; --i)
	{
		result *= i;
	}

	return result;
}

// Callback method called by GLUT when window readraw is necessary or when glutPostRedisplay() was called.
void Window::displayCallback()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // clear color and depth buffers
  glMatrixMode(GL_MODELVIEW);  // make sure we're in Modelview mode
  Matrix4 glmatrix;

  //Setup the control point matrix
  Matrix4 Mp0;
  Mp0.setRow(0, cp_0.x, cp_1.x, cp_2.x, cp_3.x);
  Mp0.setRow(1, cp_0.y, cp_1.y, cp_2.y, cp_3.y);
  Mp0.setRow(2, cp_0.z, cp_1.z, cp_2.z, cp_3.z);
  Mp0.setRow(3, 0.0, 0.0, 0.0, 0.0);

  //Setup the control point matrix
  Matrix4 Mp1;
  Mp1.setRow(0, cp_4.x, cp_5.x, cp_6.x, cp_7.x);
  Mp1.setRow(1, cp_4.y, cp_5.y, cp_6.y, cp_7.y);
  Mp1.setRow(2, cp_4.z, cp_5.z, cp_6.z, cp_7.z);
  Mp1.setRow(3, 0.0, 0.0, 0.0, 0.0);

  //Setup the control point matrix
  Matrix4 Mp2;
  Mp2.setRow(0, cp_8.x, cp_9.x, cp_10.x, cp_11.x);
  Mp2.setRow(1, cp_8.y, cp_9.y, cp_10.y, cp_11.y);
  Mp2.setRow(2, cp_8.z, cp_9.z, cp_10.z, cp_11.z);
  Mp2.setRow(3, 0.0, 0.0, 0.0, 0.0);

  //Setup the control point matrix
  Matrix4 Mp3;
  Mp3.setRow(0, cp_12.x, cp_13.x, cp_14.x, cp_15.x);
  Mp3.setRow(1, cp_12.y, cp_13.y, cp_14.y, cp_15.y);
  Mp3.setRow(2, cp_12.z, cp_13.z, cp_14.z, cp_15.z);
  Mp3.setRow(3, 0.0, 0.0, 0.0, 0.0);
  Vector4 q[404];
  Vector4 C0;
  Vector4 C1;
  Vector4 C2;
  Vector4 C3;
  //Pick a time t
  int q_index = 0;
  for (double t = 0.0; t <= 1; t += 0.01) //u
  {
	  //Create a vector with our Bernstein coefficients
	  C0.setX(bernstizzlesCoeff(3, 0, t));
	  C0.setY(bernstizzlesCoeff(3, 1, t));
	  C0.setZ(bernstizzlesCoeff(3, 2, t));
	  C0.setW(bernstizzlesCoeff(3, 3, t));

	  //C0.print("C0");
	  //getchar();
	  C1.setX(bernstizzlesCoeff(3, 4, t));
	  C1.setY(bernstizzlesCoeff(3, 5, t));
	  C1.setZ(bernstizzlesCoeff(3, 6, t));
	  C1.setW(bernstizzlesCoeff(3, 7, t));

	  C2.setX(bernstizzlesCoeff(3, 8, t));
	  C2.setY(bernstizzlesCoeff(3, 9, t));
	  C2.setZ(bernstizzlesCoeff(3, 10, t));
	  C2.setW(bernstizzlesCoeff(3, 11, t));

	  C3.setX(bernstizzlesCoeff(3, 12, t));
	  C3.setY(bernstizzlesCoeff(3, 13, t));
	  C3.setZ(bernstizzlesCoeff(3, 14, t));
	  C3.setW(bernstizzlesCoeff(3, 15, t));
	  Mp0.print("Mp0");
	  Mp1.print("Mp1");
	  Mp2.print("Mp2");
	  Mp3.print("Mp3");
	  //getchar();
	  //Calculate the final points q
	  q[q_index] = Mp0 * C0;
	  q[q_index + 1] = Mp1 * C1;
	  q[q_index + 2] = Mp2 * C2;
	  q[q_index + 3] = Mp3 * C3;

	  //And make sure q is a point by setting its w-component to 1
	  q[q_index].w = 1.0;
	  q[q_index + 1].w = 1.0;
	  q[q_index + 2].w = 1.0;
	  q[q_index + 3].w = 1.0;

	  q_index += 4;
  }

  for (int index = 0; index < 404; index++)
  {
	  q[index].print("");
  }
  getchar();
  Vector3 normal;
  glBegin(GL_POINTS);
  for (int index = 0;index < 404; index++)
  {
	  glColor3d(1, 1, 1);
	  glVertex3d(q[index].x, q[index].y, q[index].z);
  }
  glEnd();
  glFlush();
  glutSwapBuffers();



  /*if (per_pixel)
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
  }*/
}



void Window::trackBallMapping(Vector3 &cp)
{/*
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
	cp.normalize();*/
}
void Window::processMouse(int button, int state, int x, int y)
{/*
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
				current_point.setX(x - (Window::width / 2));
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
			/*	Globals::spot_light.setSpotLightDirection(current_point);
				//current_point.print("new direction is");
			}
		}
	}*/
}

void Window::processMotion(int x, int y)
{/*
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
	last_y = y;*/
}

void Window::processNormalKeys(unsigned char key, int x, int y){
	switch (key){
	case 27:
		exit(0);/*
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
		break;*/
	}
}

