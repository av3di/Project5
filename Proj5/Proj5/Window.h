#ifndef _WINDOW_H_
#define _WINDOW_H_

#include "Header.h"

class Window	  // OpenGL output window related routines
{
  public:
	  static int width, height, fkey, last_x, last_y; // window size, fkey signifies what F key was pressed
	  static bool per_pixel, left_button, trackball_model;

    static void idleCallback(void);
    static void reshapeCallback(int, int);
    static void displayCallback(void);
	static void trackBallMapping(Vector3 &);
	static void processNormalKeys(unsigned char key, int x, int y);
	static void processSpecialKeys(int key, int x, int y);
	static void processMouse(int button, int state, int x, int y);
	static void processMotion(int x, int y);
};

#endif

