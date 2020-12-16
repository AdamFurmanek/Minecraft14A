#ifndef Window_h
#define Window_h

#include <iostream>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>
#include "Game.h"
#include "Menu.h"

using namespace std;

class Window
{
private:

	static Window* engine;
	Window();
	~Window();

	static int state;

	static Game* game;
	static Menu* menu;

	static void Display();
	static void Reshape(int w, int h);
	static void Mouse(int button, int state1, int x, int y);
	static void PressKey(unsigned char key, int xx, int yy);
	static void ReleaseKey(unsigned char key, int x, int y);
	static void MouseMove(int x1, int y1);
	static void Timer(int parameter);

public:

	static Window* getInstance();
	static void Init(int argc, char* argv[]);


};

#endif