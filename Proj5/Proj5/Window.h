#ifndef _WINDOW_H_
#define _WINDOW_H_


class Window	  // OpenGL output window related routines
{
  public:
	  static int width, height, fkey; // window size, fkey signifies what F key was pressed
	

    static void idleCallback(void);
    static void reshapeCallback(int, int);
    static void displayCallback(void);
	static void processNormalKeys(unsigned char key, int x, int y);
	static void processSpecialKeys(int key, int x, int y);
};

#endif

