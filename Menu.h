#ifndef Menu_h
#define Menu_h

#include <GL/glut.h>
#include <iostream>

using namespace std;

class Menu
{

public:
	int state;

	Menu();
	void MenuDisplay();
	void MenuReshape(int w, int h);
	int MenuMouse(int button, int state, int x, int y);
	void MenuMouseMove(int x, int y);
	void MenuTimer();
};

#endif