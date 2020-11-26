#ifndef Interaction_h
#define Interaction_h

#include "Map.h"
#include "Player.h"
#include <stdlib.h>
#include <GL/glut.h>

class Interaction
{
private:
	static Map* map;
	static Player* player;

	float followedX, followedY, followedZ;
	int followedWall;
	int handID, handMax;

public:
	Interaction(Map* map, Player* player);
	void Mouse(int button, int state, int x, int y);
	void ComputeTracking(float x, float y, float z, float vector[3]);
	void Wall(float x1, float y1, float z1);
	void DrawCubeBorder();
};

#endif