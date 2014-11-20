#ifndef _WINDOW_H_
#define _WINDOW_H_
#include "main.h"

class Window	  // OpenGL output window related routines
{
  public:
	  static int width, height, fkey; // window size, fkey signifies what F key was pressed
	  static bool per_pixel;
	

    static void idleCallback(void);
    static void reshapeCallback(int, int);
    static void displayCallback(void);
	static void trackBallMapping(Vector3&);
	static void processNormalKeys(unsigned char key, int x, int y);
	static void processSpecialKeys(int key, int x, int y);
	static void processMouse(int button, int state, int x, int y);
};

#endif

