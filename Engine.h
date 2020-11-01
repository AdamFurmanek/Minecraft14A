#ifndef Engine_h
#define Engine_h

#include "Enums.h"
#include <iostream>
#include <stdlib.h>
#include <GL/glut.h>
#include "Map.h"

using namespace std;

class Engine
{
private:
	static Engine* engine;
	Engine();
	~Engine();

	// angle of rotation for the camera direction
	static float angle;
	// actual vector representing the camera's direction
	static float lx, lz, ly;
	// XZ position of the camera
	static float x, z, y;
	// the key states. These variables will be zero
	//when no key is being presses
	static float deltaAngle, deltaAngleY;
	static float deltaMove, deltaMoveSides;

	static float jump;
	//static bool pause, mouse;

	static void display();
	static void reshape(int w, int h);
	static void specialKeyboard(int key, int x, int y);
	static void mouse(int button, int state, int x, int y);
	static void Exception(string Error);
	static void pressKey(unsigned char key, int xx, int yy);
	static void releaseKey(unsigned char key, int x, int y);
	static void mouseMove(int x, int y);
	static void timer(int parameter);
	static Map* map;

public:

	static Engine* getInstance();
	static void init(int argc, char* argv[], Resolution res, bool fullscreen);


};

#endif