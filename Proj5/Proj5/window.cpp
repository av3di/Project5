#include "Header.h"

using namespace std;

int Window::width  = 512;   // set window width in pixels here
int Window::height = 512;   // set window height in pixels here

void LoadGLTextures();
double Window::time = -M_PI;

bool done_texture = false;
GLuint Window::texture[6];

Vector3 cp_0(-2, 0, 2);
Vector3 cp_1(-1, 0, 2);
Vector3 cp_2(1, 0, 2);
Vector3 cp_3(2, 0, 2);
Vector3 cp_4(-2, 0, 1);
Vector3 cp_5(-1, 0, 1);
Vector3 cp_6(1, 0, 1);
Vector3 cp_7(2, 0, 1);
Vector3 cp_8(-2, 0, -1);
Vector3 cp_9(-1, 0, -1);
Vector3 cp_10(1, 0, -1);
Vector3 cp_11(2, 0, -1);
Vector3 cp_12(-2, 0, -2);
Vector3 cp_13(-1, 0, -2);
Vector3 cp_14(1, 0, -2);
Vector3 cp_15(2, 0, -2);

//----------------------------------------------------------------------------
// Callback method called when system is idle.
void Window::idleCallback()
{
	displayCallback();         // call display routine to show the cube
}

//----------------------------------------------------------------------------
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
  gluLookAt(0, 1.5, -5, 0, 0, 0, 0, 0, 30);
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
	/* Code from https://sidvind.com/wiki/Skybox_tutorial */
	glMatrixMode(GL_MODELVIEW); // make sure we're in Modelview mode

	glPushMatrix();
	// Reset and transform the matrix.
	glLoadIdentity();
	// Enable/Disable features
	glPushAttrib(GL_ENABLE_BIT);
	glEnable(GL_TEXTURE_2D);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	glDisable(GL_BLEND);
	// Just in case we set all vertices to white.
	glColor4f(1, 1, 1, 1);
	Matrix4 bottom_origin;
	bottom_origin.makeTranslate(0, 2, 0);
	bottom_origin.makeScale(4, 4, 4);
	bottom_origin.transpose();
	glLoadMatrixd(bottom_origin.getPointer());

	// Render the front quad
	glBindTexture(GL_TEXTURE_2D, Window::texture[1]);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f(0.5f, -0.5f, -0.5f);
	glTexCoord2f(1, 0); glVertex3f(-0.5f, -0.5f, -0.5f);
	glTexCoord2f(1, 1); glVertex3f(-0.5f, 0.5f, -0.5f);
	glTexCoord2f(0, 1); glVertex3f(0.5f, 0.5f, -0.5f);
	glEnd();
	// Render the left quad
	glBindTexture(GL_TEXTURE_2D, Window::texture[2]);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f(0.5f, -0.5f, 0.5f);
	glTexCoord2f(1, 0); glVertex3f(0.5f, -0.5f, -0.5f);
	glTexCoord2f(1, 1); glVertex3f(0.5f, 0.5f, -0.5f);
	glTexCoord2f(0, 1); glVertex3f(0.5f, 0.5f, 0.5f);
	glEnd();
	// Render the back quad
	glBindTexture(GL_TEXTURE_2D, Window::texture[0]);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f(-0.5f, -0.5f, 0.5f);
	glTexCoord2f(1, 0); glVertex3f(0.5f, -0.5f, 0.5f);
	glTexCoord2f(1, 1); glVertex3f(0.5f, 0.5f, 0.5f);
	glTexCoord2f(0, 1); glVertex3f(-0.5f, 0.5f, 0.5f);
	glEnd();
	// Render the right quad
	glBindTexture(GL_TEXTURE_2D, Window::texture[3]);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f(-0.5f, -0.5f, -0.5f);
	glTexCoord2f(1, 0); glVertex3f(-0.5f, -0.5f, 0.5f);
	glTexCoord2f(1, 1); glVertex3f(-0.5f, 0.5f, 0.5f);
	glTexCoord2f(0, 1); glVertex3f(-0.5f, 0.5f, -0.5f);
	glEnd();
	// Render the top quad
	glBindTexture(GL_TEXTURE_2D, Window::texture[4]);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 1); glVertex3f(-0.5f, 0.5f, -0.5f);
	glTexCoord2f(0, 0); glVertex3f(-0.5f, 0.5f, 0.5f);
	glTexCoord2f(1, 0); glVertex3f(0.5f, 0.5f, 0.5f);
	glTexCoord2f(1, 1); glVertex3f(0.5f, 0.5f, -0.5f);
	glEnd();
	// Render the bottom quad
	glBindTexture(GL_TEXTURE_2D, Window::texture[5]);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f(-0.5f, -0.5f, -0.5f);
	glTexCoord2f(0, 1); glVertex3f(-0.5f, -0.5f, 0.5f);
	glTexCoord2f(1, 1); glVertex3f(0.5f, -0.5f, 0.5f);
	glTexCoord2f(1, 0); glVertex3f(0.5f, -0.5f, -0.5f);
	glEnd();
	// Restore enable bits and matrix
	glPopAttrib();
	glPopMatrix();
	glLoadIdentity();
	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK);
  glMatrixMode(GL_MODELVIEW);  // make sure we're in Modelview mode

  double amp = 0.25;
  cp_0.setY(amp * cos(time + (M_PI / 4)));
  cp_2.setY(amp * sin(time + (M_PI / 4)));
  cp_3.setY(amp * cos(time + (M_PI / 4)));
		 
  cp_6.setY(amp * cos(time + (3 * M_PI / 4)));
  cp_9.setY(amp * cos(time + (3 * M_PI / 4)));
  cp_11.setY(amp * sin(time + (3 * M_PI / 4)));

  cp_12.setY(amp * cos(time + (M_PI )));
  cp_13.setY(amp * sin(time + (M_PI )));
  cp_15.setY(amp * cos(time + (M_PI )));
  time += 0.2;
  if (time >= M_PI)
	  time = -M_PI;

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
  Vector4 u[404];
  std::vector<Vector4> v_vector;
  Vector4 C0;
  Vector4 C1;
  Vector4 C2;
  Vector4 C3;
  //Pick a time t
  int u_index = 0;
  for (double t = 0.0; t <= 1; t += 0.01) //u
  {
		  //Create a vector with our Bernstein coefficients
		  C0.setX(bernstizzlesCoeff(3, 0, t));
		  C0.setY(bernstizzlesCoeff(3, 1, t));
		  C0.setZ(bernstizzlesCoeff(3, 2, t));
		  C0.setW(bernstizzlesCoeff(3, 3, t));

		  //Calculate the final points q
		  u[u_index] = Mp0 * C0;
		  u[u_index + 1] = Mp1 * C0;
		  u[u_index + 2] = Mp2 * C0;
		  u[u_index + 3] = Mp3 * C0;

		  //And make sure q is a point by setting its w-component to 1
		  u[u_index].w = 1.0;
		  u[u_index + 1].w = 1.0;
		  u[u_index + 2].w = 1.0;
		  u[u_index + 3].w = 1.0;

          for (double v = 0; v <= 1.0; v += 0.01) 
		  {

			Vector4 p0(u[u_index].x, u[u_index].y, u[u_index].z, 1);
			Vector4 p1(u[u_index + 1].x, u[u_index + 1].y, u[u_index + 1].z, 1);
			Vector4 p2(u[u_index + 2].x, u[u_index + 2].y, u[u_index + 2].z, 1);
			Vector4 p3(u[u_index + 3].x, u[u_index + 3].y, u[u_index + 3].z, 1);
			Matrix4 Mpv;
			Mpv.setRow(0, p0.x, p1.x, p2.x, p3.x);
			Mpv.setRow(1, p0.y, p1.y, p2.y, p3.y);
			Mpv.setRow(2, p0.z, p1.z, p2.z, p3.z);
			Mpv.setRow(3, 0.0, 0.0, 0.0, 0.0);

			//Create a vector with our Bernstein coefficients
			Vector4 C(bernstizzlesCoeff(3, 0, v),
				bernstizzlesCoeff(3, 1, v),
				bernstizzlesCoeff(3, 2, v),
				bernstizzlesCoeff(3, 3, v));
			//Calculate the final point q
			Vector4 q = Mpv * C;
			q.w = 1.0;
			v_vector.push_back(q);
		}
	u_index += 4;
  }
  Vector3 normal;
  Vector3 dist_1;
  Vector3 dist_2;
  Vector4 tmp;
  glBegin(GL_QUADS);
  for (int i = 0; i < 99; i++) {
	  for (int j = 0; j < 99; j++) {
		  Vector4 pta = v_vector[(i * 100) + j];
		  Vector4 ptb = v_vector[(i * 100) + j + 1];
		  Vector4 ptc = v_vector[((i + 1) * 100) + j + 1];
		  Vector4 ptd = v_vector[((i + 1) * 100) + j];
		  
		  tmp = pta - ptb;
		  dist_1.setX(tmp.getX()); dist_1.setY(tmp.getY()); dist_1.setZ(tmp.getZ());
		  tmp = pta - ptd;
		  dist_2.setX(tmp.getX()); dist_2.setY(tmp.getY()); dist_2.setZ(tmp.getZ());
		  normal = dist_1.cross(dist_2);
		  normal.normalize();
		  if (normal.y < 0)
			  normal.y = normal.y * -1;

		  glColor3f(1, 1, 1);
		  glNormal3d(normal.x, normal.y, normal.z);
		  glVertex3f(pta.x, pta.y, pta.z);

		  tmp = pta - ptb;
		  dist_1.setX(tmp.getX()); dist_1.setY(tmp.getY()); dist_1.setZ(tmp.getZ());
		  tmp = ptb - ptc;
		  dist_2.setX(tmp.getX()); dist_2.setY(tmp.getY()); dist_2.setZ(tmp.getZ());
		  normal = dist_1.cross(dist_2);
		  normal.normalize();
		  if (normal.y < 0)
			  normal.y = normal.y * -1;

		  glColor3f(1, 1, 1);
		  glNormal3d(normal.x, normal.y, normal.z);
		  glVertex3f(ptb.x, ptb.y, ptb.z);

		  tmp = ptb - ptc;
		  dist_1.setX(tmp.getX()); dist_1.setY(tmp.getY()); dist_1.setZ(tmp.getZ());
		  tmp = ptc - ptd;
		  dist_2.setX(tmp.getX()); dist_2.setY(tmp.getY()); dist_2.setZ(tmp.getZ());
		  normal = dist_1.cross(dist_2);
		  normal.normalize();

		  if (normal.y < 0)
			  normal.y = normal.y * -1;
		  glColor3f(1, 1, 1);
		  glNormal3d(normal.x, normal.y, normal.z);
		  glVertex3f(ptc.x, ptc.y, ptc.z);

		  tmp = ptc - ptd;
		  dist_1.setX(tmp.getX()); dist_1.setY(tmp.getY()); dist_1.setZ(tmp.getZ());
		  tmp = ptd - pta;
		  dist_2.setX(tmp.getX()); dist_2.setY(tmp.getY()); dist_2.setZ(tmp.getZ());
		  normal = dist_1.cross(dist_2);
		  normal.normalize();

		  if (normal.y < 0)
			  normal.y = normal.y * -1;
		  glColor3f(1, 1, 1);
		  glNormal3d(normal.x, normal.y, normal.z);
		  glVertex3f(ptd.x, ptd.y, ptd.z);
	  }
  }
  glEnd();
  glFlush();
  glutSwapBuffers();
}

/* Code from http://nehe.gamedev.net/tutorial/lesson_06_texturing_update/47002/ */
void Window::LoadGLTextures() // Load Bitmaps And Convert To Textures
{
	if (done_texture)
		return;
	/* load an image file directly as a new OpenGL texture */
	texture[0] = SOIL_load_OGL_texture
		(
		"skybox_back.jpg",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y
		);
	if (texture[0] == 0) {
		return;
	}
	/* load an image file directly as a new OpenGL texture */
	texture[1] = SOIL_load_OGL_texture
		(
		"skybox_front.jpg",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y
		);
	if (texture[1] == 0) {
		return;
	}
	/* load an image file directly as a new OpenGL texture */
	texture[2] = SOIL_load_OGL_texture
		(
		"skybox_left.jpg",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y
		);
	if (texture[2] == 0) {
		return;
	}
	/* load an image file directly as a new OpenGL texture */
	texture[3] = SOIL_load_OGL_texture
		(
		"skybox_right.jpg",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y
		);
	if (texture[3] == 0) {
		return;
	}
	/* load an image file directly as a new OpenGL texture */
	texture[4] = SOIL_load_OGL_texture
		(
		"skybox_top.jpg",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y
		);
	if (texture[4] == 0) {
		return;
	}
	/* load an image file directly as a new OpenGL texture */
	texture[5] = SOIL_load_OGL_texture
		(
		"skybox_bottom.jpg",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y
		);
	if (texture[5] == 0) {
		return;
	}

	// Typical Texture Generation Using Data From The Bitmap
	glBindTexture(GL_TEXTURE_2D, texture[0]);

	// Make sure no bytes are padded:
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	// Select GL_MODULATE to mix texture with polygon color for shading:
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	// Use bilinear interpolation:
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	done_texture = true;
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

