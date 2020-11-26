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
	float deltaMoveStraight, deltaMoveSides;
	int jump;
	float fallingSpeed;
	bool flashlight;
public:
	Player(Map* map);
	void PressKey(unsigned char key, int xx, int yy);
	void ReleaseKey(unsigned char key, int x, int y);
	void ComputeFall();
	void ComputeMove(float x1, float z1);
	bool Collision(float x, float y, float z);
	void Flashlight(float vector[]);

	float getX() {
		return x;
	}
	float getY() {
		return y;
	}
	float getZ() {
		return z;
	}
};

#endif