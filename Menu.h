#ifndef Menu_h
#define Menu_h

#include "Colors.h"
#include <GL/glut.h>
#include <iostream>
#include <GL/freeglut.h>


using namespace std;

class Menu
{
private:
	bool saves[8];
	void RenderRectangle(float a1, float b1, float a2, float b2, const float color[3]);
	void RenderText(string text, float x, float y, float scale, const float colorB[3], const float colorF[3]);
	void CheckSaves();
public:

	void InitMenu();
	void MenuDisplay();
	void MenuReshape(int w, int h);
	int MenuMouse(int x, int y);
	void MenuMouseMove(int x, int y);

	void SavingMenuDisplay();
	int SavingMenuMouse(int x, int y);
	int SavingMenuMouseChecked(int x, int y);
	void SavingMenuMouseMove(int x, int y);

};

#endif