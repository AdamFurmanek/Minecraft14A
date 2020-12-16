#ifndef Player_h
#define Player_h

#include <iostream>
#include <stdlib.h>
#include <GL/glut.h>
#include "Map.h"

using namespace std;

class Player
{
private:
	static Map* map;
	float x, y, z;
	int jump;
	float fallingSpeed;
	bool flashlight;
	float viewField;

	float deltaMoveStraight, deltaMoveSides;
public:
	Player(Map* map, float x = 60.0f, float y = 20.0f, float z = 60.0f, int jump = 0, float fallingSpeed = 0.1f, bool flashlight = false, float viewField = 60.0);
	void PressKey(unsigned char key, int xx, int yy);
	void ReleaseKey(unsigned char key, int x, int y);
	void ComputeFall();
	void ComputeMove(float x1, float z1);
	bool Collision(float x, float y, float z);
	void Flashlight(float vector[]);
	void DrawCursor();

	float getX() {
		return x;
	}
	float getY() {
		return y;
	}
	float getZ() {
		return z;
	}
	int getJump() {
		return jump;
	}
	float getFallingSpeed() {
		return fallingSpeed;
	}
	bool getFlashlight() {
		return flashlight;
	}
	float getViewField() {
		return viewField;
	}
	void setViewField(float viewField) {
		this -> viewField = viewField;
	}
};

#endif