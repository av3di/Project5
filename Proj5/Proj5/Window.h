#ifndef _WINDOW_H_
#define _WINDOW_H_

#include "Header.h"

class Window	  // OpenGL output window related routines
{
  public:
	static GLuint texture[6];
	static int width, height; // window size
	static double time;
	static double bernstizzlesCoeff(long n, long i, double t);
	static long combo(long n, long i);
	static long factorial(long n);
	static void Window::LoadGLTextures();
	static void idleCallback(void);
	static void reshapeCallback(int, int);
	static void displayCallback(void);
	static void processNormalKeys(unsigned char key, int x, int y);
};

#endif

